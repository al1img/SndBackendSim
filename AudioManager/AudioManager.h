#ifndef AUDIOMANAGER_H
#define AUDIOMANAGER_H

#include <algorithm>
#include <condition_variable>
#include <mutex>

#include "CommandInterface.h"

class AudioManager : public CommandInterfaceNotifications
{
public:
    AudioManager();

    am::am_mainConnectionID_t connect(am::am_sourceID_t sourceID);
    void disconnect(am::am_mainConnectionID_t connectionID);

private:
    DBus::Connection mBus;
    CommandInterface mCommandInterface;

    std::mutex mMutex;
    std::condition_variable mCondVar;

    std::vector<am::am_SinkType_s> mListSinks;
    std::vector<am::am_SourceType_s> mListSources;
    std::vector<am::am_MainConnectionType_s> mListConnections;

    void OnNewMainConnection(const am::am_MainConnectionType_s& mainConnection) override;
    void OnRemovedMainConnection(const am::am_mainConnectionID_t& mainConnectionId) override;
    void OnSinkAdded(const am::am_SinkType_s& newSink) override;
    void OnSinkRemoved(const am::am_sinkID_t& removedSinkID)  override;
    void OnSourceAdded(const am::am_SourceType_s& newSource) override;
    void OnSourceRemoved(const am::am_sourceID_t& removedSourceID) override;
    void OnNumberOfSinkClassesChanged() override;
    void OnNumberOfSourceClassesChanged() override;
    void OnMainConnectionStateChanged(const am::am_mainConnectionID_t& connectionID, const am::am_ConnectionState_e& connectionState) override;
    void OnMainSinkSoundPropertyChanged(const am::am_sinkID_t& sinkID, const am::am_MainSoundProperty_s& soundProperty) override;
    void OnMainSourceSoundPropertyChanged(const am::am_sourceID_t& sourceID, const am::am_MainSoundProperty_s& soundProperty) override;
    void OnSinkAvailabilityChanged(const am::am_sinkID_t& sinkID, const am::am_Availability_s& availability) override;
    void OnSourceAvailabilityChanged(const am::am_sourceID_t& sourceID, const am::am_Availability_s& availability) override;
    void OnVolumeChanged(const am::am_sinkID_t& sinkID, const am::am_mainVolume_t& volume) override;
    void OnSinkMuteStateChanged(const am::am_sinkID_t& sinkID, const am::am_MuteState_e& muteState) override;
    void OnSystemPropertyChanged(const am::am_SystemProperty_s& systemProperty) override;
    void OnTimingInformationChanged(const am::am_mainConnectionID_t& mainConnection, const am::am_timeSync_t& time) override;
    void OnSinkUpdated(const am::am_sinkID_t& sinkID, const uint16_t& sinkClassID, const std::vector<am::am_MainSoundProperty_s>& listMainSoundProperties) override;
    void OnSourceUpdated(const am::am_sourceID_t& sourceID, const uint16_t& sourceClassID, const std::vector<am::am_MainSoundProperty_s>& listMainSoundProperties) override;
    void OnSourceNotification(const am::am_sourceID_t& sourceID, const am::am_NotificationPayload_s& notificationPayload) override;
    void OnSinkNotification(const am::am_sinkID_t& sinkID, const am::am_NotificationPayload_s& notificationPayload) override;
    void OnSinkMainNotificationConfigurationChanged(const am::am_sinkID_t& sinkID, const am::am_NotificationConfiguration_s& mainNotificationConfiguration) override;
    void OnSourceMainNotificationConfigurationChanged(const am::am_sourceID_t& sourceID, const am::am_NotificationConfiguration_s& mainNotificationConfiguration) override;

    void init();

    bool getSourceByID(am::am_sourceID_t sourceID, am::am_SourceType_s& source);
    bool getSinkByClassID(am::am_sinkClass_t classID, am::am_SinkType_s& sink);

    std::vector<am::am_MainConnectionType_s>::iterator
    getConnectionIt(am::am_mainConnectionID_t connectionID)
    {
        return std::find_if(mListConnections.begin(), mListConnections.end(),
                           [&connectionID](const am::am_MainConnectionType_s& connection)
                           {return connectionID == connection.mainConnectionID;});
    }

    void updateConnection(const am::am_MainConnectionType_s& connection);
    void removeConnection(am::am_mainConnectionID_t connectionID);
    void setConnectionState(am::am_mainConnectionID_t connectionID, am::am_ConnectionState_e state);
    am::am_ConnectionState_e getConnectionState(am::am_mainConnectionID_t connectionID);
};

#endif // AUDIOMANAGER_H
