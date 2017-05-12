#include "AudioManager.h"

#include <QDebug>

using namespace am;
using namespace std;

/*******************************************************************************
 * AudioManager
 ******************************************************************************/

AudioManager::AudioManager() :
    mBus(DBus::Connection::SessionBus()),
    mCommandInterface(mBus, *this)
{
    init();
}

/*******************************************************************************
 * Public
 ******************************************************************************/

am_mainConnectionID_t AudioManager::connect(am::am_sourceID_t sourceID)
{
    unique_lock<mutex> lock(mMutex);

    am_SourceType_s source;
    am_SinkType_s sink;

    if (!getSourceByID(sourceID, source))
    {
        qCritical() << "Source ID:" << sourceID << "not found";
    }

    if (!getSinkByClassID(source.sourceClassID, sink))
    {
        qCritical() << "Sink for source ID:" << sourceID << "not found";
    }

    am_mainConnectionID_t connectionID = 0;

    if (mCommandInterface.Connect(source.sourceID, sink.sinkID, connectionID) != E_OK)
    {
        qCritical() << "Can't connect sourceID:" << source.sourceID
                    << "and sinkID:" << sink.sinkID;
    }

    // wait for connecting state
    if (!mCondVar.wait_for(lock, chrono::milliseconds(1000), [&connectionID, this]
                           {   auto state = getConnectionState(connectionID);
                               return state == CS_CONNECTING || state == CS_CONNECTED; }))
    {
        qCritical() << "Waiting connecting state timeout";
    }

    qDebug() << "Connect sourceID:" << source.sourceID
             << "with sinkID:" << sink.sinkID
             << "connectionID:" << connectionID;

    return connectionID;
}

void AudioManager::disconnect(am::am_mainConnectionID_t connectionID)
{
    if (mCommandInterface.Disconnect(connectionID) != E_OK)
    {
        qCritical() << "Can't disconnect connectionID:" << connectionID;
    }
}

/*******************************************************************************
 * Private
 ******************************************************************************/

void AudioManager::init()
{
    mCommandInterface.GetListMainSinks(mListSinks);

    qDebug() << "Main sinks:";

    for(auto sink : mListSinks)
    {
        qDebug() << "    ID:" << sink.sinkID << "name:" << sink.name.c_str()
                 << "volume:" << sink.volume << "mute:" << sink.muteState
                 << "classID:" << sink.sinkClassID;
    }

    mCommandInterface.GetListMainSources(mListSources);

    qDebug() << "Main sources:";

    for(auto source : mListSources)
    {
        qDebug() << "    ID:" << source.sourceID << "name:" << source.name.c_str()
                 << "classID:" << source.sourceClassID;
    }

    mCommandInterface.GetListMainConnections(mListConnections);

    qDebug() << "Main connnections:";

    for(auto connection : mListConnections)
    {
        qDebug() << "    ID:" << connection.mainConnectionID
                 << "sourceID:" << connection.sourceID
                 << "sinkID:" << connection.sinkID
                 << "state:" << connection.connectionState;
    }
}

bool AudioManager::getSourceByID(am_sourceID_t sourceID, am_SourceType_s& source)
{
    auto result = find_if(mListSources.begin(), mListSources.end(),
                          [&sourceID](const am_SourceType_s& source)
                          {return source.sourceID == sourceID;});

    if (result == mListSources.end())
    {
        return false;
    }

    source = *result;

    return true;
}

bool AudioManager::getSinkByClassID(am_sinkClass_t classID, am_SinkType_s& sink)
{
    auto result = find_if(mListSinks.begin(), mListSinks.end(),
                          [&classID](const am_SinkType_s& sink)
                          {return sink.sinkClassID == classID;});

    if (result == mListSinks.end())
    {
        return false;
    }

    sink = *result;

    return true;
}

void AudioManager::updateConnection(const am_MainConnectionType_s& connection)
{
    auto result = getConnectionIt(connection.mainConnectionID);

    if (result == mListConnections.end())
    {
        mListConnections.push_back(connection);
    }
    else
    {
        *result = connection;
    }
}

void AudioManager::removeConnection(am_mainConnectionID_t connectionID)
{
    auto result = getConnectionIt(connectionID);

    if (result != mListConnections.end())
    {
        mListConnections.erase(result);
    }
}

void AudioManager::setConnectionState(am_mainConnectionID_t connectionID, am_ConnectionState_e state)
{
    auto result = getConnectionIt(connectionID);

    if (result == mListConnections.end())
    {
        // TODO: Maybe warning here?
        qWarning() << "Can't find connection ID:" << connectionID;
    }

    result->connectionState = state;
}

am_ConnectionState_e AudioManager::getConnectionState(am_mainConnectionID_t connectionID)
{
    auto result = getConnectionIt(connectionID);

    if (result != mListConnections.end())
    {
        return result->connectionState;
    }

    return CS_UNKNOWN;
}

/*******************************************************************************
 * Notifications
 ******************************************************************************/

void AudioManager::OnNewMainConnection(const am_MainConnectionType_s& mainConnection)
{
    qDebug() << "New main connection ID:" << mainConnection.mainConnectionID;

    updateConnection(mainConnection);
}

void AudioManager::OnRemovedMainConnection(const am_mainConnectionID_t& mainConnectionID)
{
    qDebug() << "Removed main connection ID:" << mainConnectionID;

    removeConnection(mainConnectionID);
}

void AudioManager::OnSinkAdded(const am_SinkType_s& newSink)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSinkRemoved(const am_sinkID_t& removedSinkID)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSourceAdded(const am_SourceType_s& newSource)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSourceRemoved(const am_sourceID_t& removedSourceID)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnNumberOfSinkClassesChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnNumberOfSourceClassesChanged()
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnMainConnectionStateChanged(const am_mainConnectionID_t& connectionID, const am_ConnectionState_e& connectionState)
{
    unique_lock<mutex> lock(mMutex);

    qDebug() << "Main connection state changed ID:" << connectionID
             << "stat:" << connectionState;

    setConnectionState(connectionID, connectionState);

    mCondVar.notify_one();
}

void AudioManager::OnMainSinkSoundPropertyChanged(const am_sinkID_t& sinkID, const am_MainSoundProperty_s& soundProperty)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnMainSourceSoundPropertyChanged(const am_sourceID_t& sourceID, const am_MainSoundProperty_s& soundProperty)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSinkAvailabilityChanged(const am_sinkID_t& sinkID, const am_Availability_s& availability)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSourceAvailabilityChanged(const am_sourceID_t& sourceID, const am_Availability_s& availability)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnVolumeChanged(const am_sinkID_t& sinkID, const am_mainVolume_t& volume)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSinkMuteStateChanged(const am_sinkID_t& sinkID, const am_MuteState_e& muteState)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSystemPropertyChanged(const am_SystemProperty_s& SystemProperty)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnTimingInformationChanged(const am_mainConnectionID_t& mainConnection, const am_timeSync_t& time)
{
    qDebug() << "Timing information changed ID" << mainConnection
             << "time:" << time;
}

void AudioManager::OnSinkUpdated(const am_sinkID_t& sinkID, const uint16_t& sinkClassID, const vector<am_MainSoundProperty_s>& listMainSoundProperties)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSourceUpdated(const am_sourceID_t& sourceID, const uint16_t& sourceClassID, const vector<am_MainSoundProperty_s>& listMainSoundProperties)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSourceNotification(const am_sourceID_t& sourceID, const am_NotificationPayload_s& notificationPayload)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSinkNotification(const am_sinkID_t& sinkID, const am_NotificationPayload_s& notificationPayload)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSinkMainNotificationConfigurationChanged(const am_sinkID_t& sinkID, const am_NotificationConfiguration_s& mainNotificationConfiguration)
{
    qDebug() << Q_FUNC_INFO;
}

void AudioManager::OnSourceMainNotificationConfigurationChanged(const am_sourceID_t& sourceID, const am_NotificationConfiguration_s& mainNotificationConfiguration)
{
    qDebug() << Q_FUNC_INFO;
}
