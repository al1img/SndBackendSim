#ifndef COMMANDINTERFACECONEVERTER_H
#define COMMANDINTERFACECONEVERTER_H

#include "CommandInterfaceProxy.h"

#include <audiomanager/audiomanagertypes.h>


class CommandInterfaceNotifications
{
public:
    virtual ~CommandInterfaceNotifications() {};

    virtual void OnNewMainConnection(const am::am_MainConnectionType_s& mainConnection) = 0;
    virtual void OnRemovedMainConnection(const am::am_mainConnectionID_t& mainConnectionId) = 0;
    virtual void OnSinkAdded(const am::am_SinkType_s& newSink) = 0;
    virtual void OnSinkRemoved(const am::am_sinkID_t& removedSinkID)  = 0;
    virtual void OnSourceAdded(const am::am_SourceType_s& newSource) = 0;
    virtual void OnSourceRemoved(const am::am_sourceID_t& removedSourceID) = 0;
    virtual void OnNumberOfSinkClassesChanged() = 0;
    virtual void OnNumberOfSourceClassesChanged() = 0;
    virtual void OnMainConnectionStateChanged(const am::am_mainConnectionID_t& connectionID, const am::am_ConnectionState_e& connectionState) = 0;
    virtual void OnMainSinkSoundPropertyChanged(const am::am_sinkID_t& sinkID, const am::am_MainSoundProperty_s& soundProperty) = 0;
    virtual void OnMainSourceSoundPropertyChanged(const am::am_sourceID_t& sourceID, const am::am_MainSoundProperty_s& soundProperty) = 0;
    virtual void OnSinkAvailabilityChanged(const am::am_sinkID_t& sinkID, const am::am_Availability_s& availability) = 0;
    virtual void OnSourceAvailabilityChanged(const am::am_sourceID_t& sourceID, const am::am_Availability_s& availability) = 0;
    virtual void OnVolumeChanged(const am::am_sinkID_t& sinkID, const am::am_mainVolume_t& volume) = 0;
    virtual void OnSinkMuteStateChanged(const am::am_sinkID_t& sinkID, const am::am_MuteState_e& muteState) = 0;
    virtual void OnSystemPropertyChanged(const am::am_SystemProperty_s& systemProperty) = 0;
    virtual void OnTimingInformationChanged(const am::am_mainConnectionID_t& mainConnection, const am::am_timeSync_t& time) = 0;
    virtual void OnSinkUpdated(const am::am_sinkID_t& sinkID, const uint16_t& sinkClassID, const std::vector<am::am_MainSoundProperty_s>& listMainSoundProperties) = 0;
    virtual void OnSourceUpdated(const am::am_sourceID_t& sourceID, const uint16_t& sourceClassID, const std::vector<am::am_MainSoundProperty_s>& listMainSoundProperties) = 0;
    virtual void OnSourceNotification(const am::am_sourceID_t& sourceID, const am::am_NotificationPayload_s& notificationPayload) = 0;
    virtual void OnSinkNotification(const am::am_sinkID_t& sinkID, const am::am_NotificationPayload_s& notificationPayload) = 0;
    virtual void OnSinkMainNotificationConfigurationChanged(const am::am_sinkID_t& sinkID, const am::am_NotificationConfiguration_s& mainNotificationConfiguration) = 0;
    virtual void OnSourceMainNotificationConfigurationChanged(const am::am_sourceID_t& sourceID, const am::am_NotificationConfiguration_s& mainNotificationConfiguration) = 0;
};

class CommandInterfaceConverter : public org::genivi::audiomanager::commandinterface_proxy,
                                  public DBus::ObjectProxy
{
public:
    CommandInterfaceConverter(DBus::Connection& connection, CommandInterfaceNotifications& notifications);

/*******************************************************************************
 * Commands
 ******************************************************************************/

    am::am_Error_e Connect(const am::am_sourceID_t& sourceID, const am::am_sinkID_t& sinkID, am::am_mainConnectionID_t& mainConnectionID);
    am::am_Error_e Disconnect(const am::am_mainConnectionID_t& mainConnectionID);
    am::am_Error_e SetVolume(const am::am_sinkID_t& sinkID, const am::am_mainVolume_t& volume);
    am::am_Error_e VolumeStep(const am::am_sinkID_t& sinkID, const int16_t& volumeStep);
    am::am_Error_e SetSinkMuteState(const am::am_sinkID_t& sinkID, const am::am_MuteState_e& muteState);
    am::am_Error_e SetMainSinkSoundProperty(const am::am_sinkID_t& sinkID, const am::am_MainSoundProperty_s& soundProperty);
    am::am_Error_e SetMainSourceSoundProperty(const am::am_sourceID_t& sourceID, const am::am_MainSoundProperty_s& soundProperty);
    am::am_Error_e SetSystemProperty(am::am_SystemProperty_s& property);
    am::am_Error_e GetListMainConnections(std::vector<am::am_MainConnectionType_s>& listConnections);
    am::am_Error_e GetListMainSinks(std::vector<am::am_SinkType_s>& listMainSinks);
    am::am_Error_e GetListMainSources(std::vector<am::am_SourceType_s>& listMainSources);
    am::am_Error_e GetListMainSinkSoundProperties(const am::am_sinkID_t& sinkID, std::vector<am::am_MainSoundProperty_s>& listSoundProperties);
    am::am_Error_e GetListMainSourceSoundProperties(const am::am_sourceID_t& sourceID, std::vector<am::am_MainSoundProperty_s>& listSoundProperties);
    am::am_Error_e GetListSinkClasses(std::vector<am::am_SinkClass_s>& listSinkClasses);
    am::am_Error_e GetListSourceClasses(std::vector<am::am_SourceClass_s>& listSourceClasses);
    am::am_Error_e GetListSystemProperties(std::vector<am::am_SystemProperty_s>& listSystemProperties);
    am::am_Error_e GetTimingInformation(const am::am_mainConnectionID_t& mainConnectionID, am::am_timeSync_t& delay);
    am::am_Error_e GetListSinkMainNotificationConfigurations(const am::am_sinkID_t& sinkID, std::vector<am::am_NotificationConfiguration_s>& listMainNotificationConfigurations);
    am::am_Error_e GetListSourceMainNotificationConfigurations(const am::am_sourceID_t& sourceID, std::vector<am::am_NotificationConfiguration_s>& listMainNotificationConfigurations);
    am::am_Error_e setMainSinkNotificationConfiguration(const am::am_sinkID_t& sinkID, const am::am_NotificationConfiguration_s& mainNotificationConfiguration);
    am::am_Error_e setMainSourceNotificationConfiguration(const am::am_sourceID_t& sourceID, const am::am_NotificationConfiguration_s& mainNotificationConfiguration);

private:

    CommandInterfaceNotifications& mNotifications;

/*******************************************************************************
 * Notifications
 ******************************************************************************/

    void NewMainConnection(const ::DBus::Struct< uint16_t, uint16_t, uint16_t, int16_t, int16_t >& mainConnection) override;
    void RemovedMainConnection(const uint16_t& mainConnectionId) override;
    void SinkAdded(const ::DBus::Struct< uint16_t, std::string, ::DBus::Struct< int16_t, int16_t >, int16_t, int16_t, uint16_t >& newSink) override;
    void SinkRemoved(const uint16_t& removedSinkID)  override;
    void SourceAdded(const ::DBus::Struct< uint16_t, std::string, ::DBus::Struct< int16_t, int16_t >, uint16_t >& newSource) override;
    void SourceRemoved(const uint16_t& removedSourceID) override;
    void NumberOfSinkClassesChanged() override;
    void NumberOfSourceClassesChanged() override;
    void MainConnectionStateChanged(const uint16_t& connectionID, const int16_t& connectionState) override;
    void MainSinkSoundPropertyChanged(const uint16_t& sinkID, const ::DBus::Struct< int16_t, int16_t >& SoundProperty) override;
    void MainSourceSoundPropertyChanged(const uint16_t& sourceID, const ::DBus::Struct< int16_t, int16_t >& SoundProperty) override;
    void SinkAvailabilityChanged(const uint16_t& sinkID, const ::DBus::Struct< int16_t, int16_t >& availability) override;
    void SourceAvailabilityChanged(const uint16_t& sourceID, const ::DBus::Struct< int16_t, int16_t >& availability) override;
    void VolumeChanged(const uint16_t& sinkID, const int16_t& volume) override;
    void SinkMuteStateChanged(const uint16_t& sinkID, const int16_t& muteState) override;
    void SystemPropertyChanged(const ::DBus::Struct< int16_t, int16_t >& SystemProperty) override;
    void TimingInformationChanged(const uint16_t& mainConnection, const int16_t& time) override;
    void SinkUpdated(const uint16_t& sinkID, const uint16_t& sinkClassID, const std::vector< ::DBus::Struct< int16_t, int16_t > >& listMainSinkProperties) override;
    void SourceUpdated(const uint16_t& sourceID, const uint16_t& sourceClassID, const std::vector< ::DBus::Struct< int16_t, int16_t > >& listMainSinkProperties) override;
    void SinkNotification(const uint16_t& sinkID, const ::DBus::Struct< int16_t, int16_t >& notificationPayload) override;
    void SourceNotification(const uint16_t& sourceID, const ::DBus::Struct< int16_t, int16_t >& notificationPayload) override;
    void SinkMainNotificationConfigurationChanged(const uint16_t& sinkID, const ::DBus::Struct< int16_t, int16_t, int16_t >& mainNotificationConfiguration) override;
    void SourceMainNotificationConfigurationChanged(const uint16_t& sourceID, const ::DBus::Struct< int16_t, int16_t, int16_t >& mainNotificationConfiguration) override;

/*******************************************************************************
 * Converters
 ******************************************************************************/

    am::am_SinkType_s ConvertSinkType(const ::DBus::Struct< uint16_t, std::string, ::DBus::Struct< int16_t, int16_t >, int16_t, int16_t, uint16_t >& sinkIn);
    am::am_SourceType_s ConvertSourceType(const ::DBus::Struct< uint16_t, std::string, ::DBus::Struct< int16_t, int16_t >, uint16_t >& sourceIn);
    am::am_Availability_s ConvertAvailability(const ::DBus::Struct< int16_t, int16_t >& availabilityIn);
    am::am_MainConnectionType_s ConvertMainConnection(const ::DBus::Struct< uint16_t, uint16_t, uint16_t, int16_t, int16_t >& mainConnectionIn);
    ::DBus::Struct< int16_t, int16_t > ConvertMainSoundProperty(const am::am_MainSoundProperty_s& mainSoundPropertyIn);
    am::am_MainSoundProperty_s ConvertMainSoundProperty(const ::DBus::Struct< int16_t, int16_t >& mainSoundPropertyIn);
    ::DBus::Struct< int16_t, int16_t > ConvertSystemProperty(const am::am_SystemProperty_s& mainSoundPropertyIn);
    am::am_SystemProperty_s ConvertSystemProperty(const ::DBus::Struct< int16_t, int16_t >& mainSoundPropertyIn);
    am::am_SourceClass_s ConvertSourceClass(const ::DBus::Struct< uint16_t, std::string, std::vector< ::DBus::Struct< int16_t, int16_t > > >& sourceClassIn);
    am::am_SinkClass_s ConvertSinkClass(const ::DBus::Struct< uint16_t, std::string, std::vector< ::DBus::Struct< int16_t, int16_t > > >& sourceClassIn);
    am::am_ClassProperty_s ConvertClassProperty(const ::DBus::Struct< int16_t, int16_t >& classPropertyIn);
    am::am_NotificationConfiguration_s ConvertNotificationConfiguration(const ::DBus::Struct< int16_t, int16_t, int16_t >& notificationConfigurationIn);
    ::DBus::Struct< int16_t, int16_t, int16_t > ConvertNotificationConfiguration(const am::am_NotificationConfiguration_s& notificationConfigurationIn);
    am::am_NotificationPayload_s ConvertNotificationPayload(const ::DBus::Struct< int16_t, int16_t >& notificationPayloadIn);
};

#endif // COMMANDINTERFACECONEVERTER_H
