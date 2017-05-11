#include "CommandInterface.h"

using namespace am;
using namespace std;

void CommandInterface::OnNewMainConnection(const am_MainConnectionType_s& mainConnection)
{
    emit newMediaConnection(mainConnection);
}

void CommandInterface::OnRemovedMainConnection(const am_mainConnectionID_t& mainConnectionId)
{
    emit removedMainConnection(mainConnectionId);
}

void CommandInterface::OnSinkAdded(const am_SinkType_s& newSink)
{
    emit sinkAdded(newSink);
}

void CommandInterface::OnSinkRemoved(const am_sinkID_t& removedSinkID)
{
    emit sinkRemoved(removedSinkID);
}

void CommandInterface::OnSourceAdded(const am_SourceType_s& newSource)
{
    emit sourceAdded(newSource);
}

void CommandInterface::OnSourceRemoved(const am_sourceID_t& removedSourceID)
{
    emit sourceRemoved(removedSourceID);
}

void CommandInterface::OnNumberOfSinkClassesChanged()
{
    emit numberOfSinkClassesChanged();
}

void CommandInterface::OnNumberOfSourceClassesChanged()
{
    emit numberOfSourceClassesChanged();
}

void CommandInterface::OnMainConnectionStateChanged(const am_mainConnectionID_t& connectionID, const am_ConnectionState_e& connectionState)
{
    emit mainConnectionStateChanged(connectionID, connectionState);
}

void CommandInterface::OnMainSinkSoundPropertyChanged(const am_sinkID_t& sinkID, const am_MainSoundProperty_s& soundProperty)
{
    emit mainSinkSoundPropertyChanged(sinkID, soundProperty);
}

void CommandInterface::OnMainSourceSoundPropertyChanged(const am_sourceID_t& sourceID, const am_MainSoundProperty_s& soundProperty)
{
    emit mainSourceSoundPropertyChanged(sourceID, soundProperty);
}

void CommandInterface::OnSinkAvailabilityChanged(const am_sinkID_t& sinkID, const am_Availability_s& availability)
{
    emit sinkAvailabilityChanged(sinkID, availability);
}

void CommandInterface::OnSourceAvailabilityChanged(const am_sourceID_t& sourceID, const am_Availability_s& availability)
{
    emit sourceAvailabilityChanged(sourceID, availability);
}

void CommandInterface::OnVolumeChanged(const am_sinkID_t& sinkID, const am_mainVolume_t& volume)
{
    emit volumeChanged(sinkID, volume);
}

void CommandInterface::OnSinkMuteStateChanged(const am_sinkID_t& sinkID, const am_MuteState_e& muteState)
{
    emit sinkMuteStateChanged(sinkID, muteState);
}

void CommandInterface::OnSystemPropertyChanged(const am_SystemProperty_s& systemProperty)
{
    emit systemPropertyChanged(systemProperty);
}

void CommandInterface::OnTimingInformationChanged(const am_mainConnectionID_t& mainConnection, const am_timeSync_t& time)
{
    emit timingInformationChanged(mainConnection, time);
}

void CommandInterface::OnSinkUpdated(const am_sinkID_t& sinkID, const uint16_t& sinkClassID, const vector<am_MainSoundProperty_s>& listMainSoundProperties)
{
    emit sinkUpdated(sinkID, sinkClassID, listMainSoundProperties);
}

void CommandInterface::OnSourceUpdated(const am_sourceID_t& sourceID, const uint16_t& sourceClassID, const vector<am_MainSoundProperty_s>& listMainSoundProperties)
{
    emit sourceUpdated(sourceID, sourceClassID, listMainSoundProperties);
}

void CommandInterface::OnSourceNotification(const am_sourceID_t& sourceID, const am_NotificationPayload_s& notificationPayload)
{
    emit sourceNotification(sourceID, notificationPayload);
}

void CommandInterface::OnSinkNotification(const am_sinkID_t& sinkID, const am_NotificationPayload_s& notificationPayload)
{
    emit sinkNotification(sinkID, notificationPayload);
}

void CommandInterface::OnSinkMainNotificationConfigurationChanged(const am_sinkID_t& sinkID, const am_NotificationConfiguration_s& mainNotificationConfiguration)
{
    emit sinkMainNotificationConfigurationChanged(sinkID, mainNotificationConfiguration);
}

void CommandInterface::OnSourceMainNotificationConfigurationChanged(const am_sourceID_t& sourceID, const am_NotificationConfiguration_s& mainNotificationConfiguration)
{
    emit sourceMainNotificationConfigurationChanged(sourceID, mainNotificationConfiguration);
}
