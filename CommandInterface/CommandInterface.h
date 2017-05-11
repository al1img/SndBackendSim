#ifndef COMMANDINTERFACE_H
#define COMMANDINTERFACE_H

#include "CommandInterfaceConverter.h"

#include <QObject>

class CommandInterface : public QObject, public CommandInterfaceConverter
{
    Q_OBJECT

signals:
    void newMediaConnection(const am::am_MainConnectionType_s& mainConnection);
    void removedMainConnection(const am::am_mainConnectionID_t& mainConnectionId);
    void sinkAdded(const am::am_SinkType_s& newSink);
    void sinkRemoved(const am::am_sinkID_t& removedSinkID) ;
    void sourceAdded(const am::am_SourceType_s& newSource);
    void sourceRemoved(const am::am_sourceID_t& removedSourceID);
    void numberOfSinkClassesChanged();
    void numberOfSourceClassesChanged();
    void mainConnectionStateChanged(const am::am_mainConnectionID_t& connectionID, const am::am_ConnectionState_e& connectionState);
    void mainSinkSoundPropertyChanged(const am::am_sinkID_t& sinkID, const am::am_MainSoundProperty_s& soundProperty);
    void mainSourceSoundPropertyChanged(const am::am_sourceID_t& sourceID, const am::am_MainSoundProperty_s& soundProperty);
    void sinkAvailabilityChanged(const am::am_sinkID_t& sinkID, const am::am_Availability_s& availability);
    void sourceAvailabilityChanged(const am::am_sourceID_t& sourceID, const am::am_Availability_s& availability);
    void volumeChanged(const am::am_sinkID_t& sinkID, const am::am_mainVolume_t& volume);
    void sinkMuteStateChanged(const am::am_sinkID_t& sinkID, const am::am_MuteState_e& muteState);
    void systemPropertyChanged(const am::am_SystemProperty_s& SystemProperty);
    void timingInformationChanged(const am::am_mainConnectionID_t& mainConnection, const am::am_timeSync_t& time);
    void sinkUpdated(const am::am_sinkID_t& sinkID, const uint16_t& sinkClassID, const std::vector<am::am_MainSoundProperty_s>& listMainSoundProperties);
    void sourceUpdated(const am::am_sourceID_t& sourceID, const uint16_t& sourceClassID, const std::vector<am::am_MainSoundProperty_s>& listMainSoundProperties);
    void sourceNotification(const am::am_sourceID_t& sourceID, const am::am_NotificationPayload_s& notificationPayload);
    void sinkNotification(const am::am_sinkID_t& sinkID, const am::am_NotificationPayload_s& notificationPayload);
    void sinkMainNotificationConfigurationChanged(const am::am_sinkID_t& sinkID, const am::am_NotificationConfiguration_s& mainNotificationConfiguration);
    void sourceMainNotificationConfigurationChanged(const am::am_sourceID_t& sourceID, const am::am_NotificationConfiguration_s& mainNotificationConfiguration);

public:
    using CommandInterfaceConverter::CommandInterfaceConverter;

private:
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

};

#endif // COMMANDINTERFACE_H
