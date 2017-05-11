#include "CommandInterfaceConverter.h"

#define DBUS_SERVICE "org.genivi.audiomanager"
#define DBUS_PATH "/org/genivi/audiomanager/commandinterface"

using namespace org::genivi::audiomanager;
using namespace am;
using namespace std;

CommandInterfaceConverter::CommandInterfaceConverter(DBus::Connection& connection) :
    DBus::ObjectProxy(connection, DBUS_PATH, DBUS_SERVICE)
{

}

/*******************************************************************************
 * Commands
 ******************************************************************************/

am_Error_e CommandInterfaceConverter::Connect(const am_sourceID_t& sourceID, const am_sinkID_t& sinkID, am_mainConnectionID_t& mainConnectionID)
{
    int16_t lResult;

    commandinterface_proxy::Connect(sourceID, sinkID, lResult, mainConnectionID);

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::Disconnect(const am_mainConnectionID_t& mainConnectionID)
{
    return static_cast<am_Error_e>(commandinterface_proxy::Disconnect(mainConnectionID));
}

am_Error_e CommandInterfaceConverter::SetVolume(const am_sinkID_t& sinkID, const am_volume_t& volume)
{
    return static_cast<am_Error_e>(commandinterface_proxy::SetVolume(sinkID, volume));
}

am_Error_e CommandInterfaceConverter::VolumeStep(const am_sinkID_t& sinkID, const int16_t& volumeStep)
{
    return static_cast<am_Error_e>(commandinterface_proxy::VolumeStep(sinkID, volumeStep));
}

am_Error_e CommandInterfaceConverter::SetSinkMuteState(const am_sinkID_t& sinkID, const am_MuteState_e& muteState)
{
    return static_cast<am_Error_e>(commandinterface_proxy::SetSinkMuteState(sinkID, muteState));
}

am_Error_e CommandInterfaceConverter::SetMainSinkSoundProperty(const am_sinkID_t& sinkID, const am_MainSoundProperty_s& soundProperty)
{
    return static_cast<am_Error_e>(commandinterface_proxy::SetMainSinkSoundProperty(sinkID, ConvertMainSoundProperty(soundProperty)));
}

am_Error_e CommandInterfaceConverter::SetMainSourceSoundProperty(const am_sourceID_t& sourceID, const am_MainSoundProperty_s& soundProperty)
{
    return static_cast<am_Error_e>(commandinterface_proxy::SetMainSourceSoundProperty(sourceID, ConvertMainSoundProperty(soundProperty)));
}

am_Error_e CommandInterfaceConverter::SetSystemProperty(am_SystemProperty_s& property)
{
    return static_cast<am_Error_e>(commandinterface_proxy::SetSystemProperty(ConvertSystemProperty(property)));
}

am_Error_e CommandInterfaceConverter::GetListMainConnections(vector<am_MainConnectionType_s>& listConnections)
{
    int16_t lResult;
    vector< ::DBus::Struct< uint16_t, uint16_t, uint16_t, int16_t, int16_t > > lListMainConnections;

    commandinterface_proxy::GetListMainConnections(lResult, lListMainConnections);

    for(auto connection : lListMainConnections)
    {
        listConnections.push_back(ConvertMainConnection(connection));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e  CommandInterfaceConverter::GetListMainSinks(vector<am_SinkType_s>& listMainSinks)
{
    int16_t lResult;
    vector< ::DBus::Struct< uint16_t, string, ::DBus::Struct< int16_t, int16_t >, int16_t, int16_t, uint16_t > > lListMainSinks;

    commandinterface_proxy::GetListMainSinks(lResult, lListMainSinks);

    for(auto sink : lListMainSinks)
    {
        listMainSinks.push_back(ConvertSinkType(sink));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetListMainSources(vector<am_SourceType_s>& listMainSources)
{
    int16_t lResult;
    vector< ::DBus::Struct< uint16_t, string, ::DBus::Struct< int16_t, int16_t >, uint16_t > > lListMainSources;

    commandinterface_proxy::GetListMainSources(lResult, lListMainSources);

    for(auto source : lListMainSources)
    {
        listMainSources.push_back(ConvertSourceType(source));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetListMainSinkSoundProperties(const am_sinkID_t& sinkID, vector<am_MainSoundProperty_s>& listSoundProperties)
{
    int16_t lResult;
    vector< ::DBus::Struct< int16_t, int16_t > > lListSoundProperties;

    commandinterface_proxy::GetListMainSinkSoundProperties(sinkID, lResult, lListSoundProperties);

    for(auto property : lListSoundProperties)
    {
        listSoundProperties.push_back(ConvertMainSoundProperty(property));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetListMainSourceSoundProperties(const am_sourceID_t& sourceID, vector<am_MainSoundProperty_s>& listSoundProperties)
{
    int16_t lResult;
    vector< ::DBus::Struct< int16_t, int16_t > > lListSoundProperties;

    commandinterface_proxy::GetListMainSourceSoundProperties(sourceID, lResult, lListSoundProperties);

    for(auto property : lListSoundProperties)
    {
        listSoundProperties.push_back(ConvertMainSoundProperty(property));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetListSinkClasses(vector<am_SinkClass_s>& listSinkClasses)
{
    int16_t lResult;
    vector< ::DBus::Struct< uint16_t, string, vector< ::DBus::Struct< int16_t, int16_t > > > > lListSinkClasses;

    commandinterface_proxy::GetListSinkClasses(lResult, lListSinkClasses);

    for(auto sinkClass : lListSinkClasses)
    {
        listSinkClasses.push_back(ConvertSinkClass(sinkClass));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetListSourceClasses(vector<am_SourceClass_s>& listSourceClasses)
{
    int16_t lResult;
    vector< ::DBus::Struct< uint16_t, string, vector< ::DBus::Struct< int16_t, int16_t > > > > lListSourceClasses;

    commandinterface_proxy::GetListSourceClasses(lResult, lListSourceClasses);

    for(auto sourceClass : lListSourceClasses)
    {
        listSourceClasses.push_back(ConvertSourceClass(sourceClass));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetListSystemProperties(vector<am_SystemProperty_s>& listSystemProperties)
{
    int16_t lResult;
    vector< ::DBus::Struct< int16_t, int16_t > > lListSystemProperties;

    commandinterface_proxy::GetListSystemProperties(lResult, lListSystemProperties);

    for(auto property : lListSystemProperties)
    {
        listSystemProperties.push_back(ConvertSystemProperty(property));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetTimingInformation(const am_mainConnectionID_t& mainConnectionID, am_timeSync_t& delay)
{
    int16_t lResult;

    commandinterface_proxy::GetTimingInformation(mainConnectionID, lResult, delay);

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetListSinkMainNotificationConfigurations(const am_sinkID_t& sinkID, vector<am_NotificationConfiguration_s>& listMainNotificationConfigurations)
{
    int16_t lResult;
    vector< ::DBus::Struct< int16_t, int16_t, int16_t > > lListMainNotificationConfigurations;

    commandinterface_proxy::GetListSinkMainNotificationConfigurations(sinkID, lResult, lListMainNotificationConfigurations);

    for(auto notificationConfiguration : lListMainNotificationConfigurations)
    {
        listMainNotificationConfigurations.push_back(ConvertNotificationConfiguration(notificationConfiguration));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::GetListSourceMainNotificationConfigurations(const am_sourceID_t& sourceID, vector<am_NotificationConfiguration_s>& listMainNotificationConfigurations)
{
    int16_t lResult;
    vector< ::DBus::Struct< int16_t, int16_t, int16_t > > lListMainNotificationConfigurations;

    commandinterface_proxy::GetListSourceMainNotificationConfigurations(sourceID, lResult, lListMainNotificationConfigurations);

    for(auto notificationConfiguration : lListMainNotificationConfigurations)
    {
        listMainNotificationConfigurations.push_back(ConvertNotificationConfiguration(notificationConfiguration));
    }

    return static_cast<am_Error_e>(lResult);
}

am_Error_e CommandInterfaceConverter::setMainSinkNotificationConfiguration(const am_sinkID_t& sinkID, const am_NotificationConfiguration_s& mainNotificationConfiguration)
{
    return static_cast<am_Error_e>(commandinterface_proxy::setMainSinkNotificationConfiguration(sinkID, ConvertNotificationConfiguration(mainNotificationConfiguration)));
}

am_Error_e CommandInterfaceConverter::setMainSourceNotificationConfiguration(const am_sourceID_t& sourceID, const am_NotificationConfiguration_s& mainNotificationConfiguration)
{
    return static_cast<am_Error_e>(commandinterface_proxy::setMainSourceNotificationConfiguration(sourceID, ConvertNotificationConfiguration(mainNotificationConfiguration)));
}

/*******************************************************************************
 * Notifications
 ******************************************************************************/

void CommandInterfaceConverter::NewMainConnection(const ::DBus::Struct< uint16_t, uint16_t, uint16_t, int16_t, int16_t >& mainConnection)
{
    OnNewMainConnection(ConvertMainConnection(mainConnection));
}

void CommandInterfaceConverter::RemovedMainConnection(const uint16_t& mainConnectionId)
{
    OnRemovedMainConnection(mainConnectionId);
}

void CommandInterfaceConverter::SinkAdded(const ::DBus::Struct< uint16_t, string, ::DBus::Struct< int16_t, int16_t >, int16_t, int16_t, uint16_t >& newSink)
{
    OnSinkAdded(ConvertSinkType(newSink));
}

void CommandInterfaceConverter::SinkRemoved(const uint16_t& removedSinkID)
{
    OnSinkRemoved(removedSinkID);
}

void CommandInterfaceConverter::SourceAdded(const ::DBus::Struct< uint16_t, string, ::DBus::Struct< int16_t, int16_t >, uint16_t >& newSource)
{
    OnSourceAdded(ConvertSourceType(newSource));
}

void CommandInterfaceConverter::SourceRemoved(const uint16_t& removedSourceID)
{
    OnSourceRemoved(removedSourceID);
}

void CommandInterfaceConverter::NumberOfSinkClassesChanged()
{
    OnNumberOfSinkClassesChanged();
}

void CommandInterfaceConverter::NumberOfSourceClassesChanged()
{
    OnNumberOfSourceClassesChanged();
}

void CommandInterfaceConverter::MainConnectionStateChanged(const uint16_t& connectionID, const int16_t& connectionState)
{
    OnMainConnectionStateChanged(connectionID, static_cast<am_ConnectionState_e>(connectionState));
}

void CommandInterfaceConverter::MainSinkSoundPropertyChanged(const uint16_t& sinkID, const ::DBus::Struct< int16_t, int16_t >& SoundProperty)
{
    OnMainSinkSoundPropertyChanged(sinkID, ConvertMainSoundProperty(SoundProperty));
}

void CommandInterfaceConverter::MainSourceSoundPropertyChanged(const uint16_t& sourceID, const ::DBus::Struct< int16_t, int16_t >& SoundProperty)
{
    OnMainSourceSoundPropertyChanged(sourceID, ConvertMainSoundProperty(SoundProperty));
}

void CommandInterfaceConverter::SinkAvailabilityChanged(const uint16_t& sinkID, const ::DBus::Struct< int16_t, int16_t >& availability)
{
    OnSinkAvailabilityChanged(sinkID, ConvertAvailability(availability));
}

void CommandInterfaceConverter::SourceAvailabilityChanged(const uint16_t& sourceID, const ::DBus::Struct< int16_t, int16_t >& availability)
{
    OnSourceAvailabilityChanged(sourceID, ConvertAvailability(availability));
}

void CommandInterfaceConverter::VolumeChanged(const uint16_t& sinkID, const int16_t& volume)
{
    OnVolumeChanged(sinkID, volume);
}

void CommandInterfaceConverter::SinkMuteStateChanged(const uint16_t& sinkID, const int16_t& muteState)
{
    OnSinkMuteStateChanged(sinkID, static_cast<am_MuteState_e>(muteState));
}

void CommandInterfaceConverter::SystemPropertyChanged(const ::DBus::Struct< int16_t, int16_t >& SystemProperty)
{
    OnSystemPropertyChanged(ConvertSystemProperty(SystemProperty));
}

void CommandInterfaceConverter::TimingInformationChanged(const uint16_t& mainConnection, const int16_t& time)
{
    OnTimingInformationChanged(mainConnection, time);
}

void CommandInterfaceConverter::SinkUpdated(const uint16_t& sinkID, const uint16_t& sinkClassID, const vector< ::DBus::Struct< int16_t, int16_t > >& listMainSinkProperties)
{
    vector<am_MainSoundProperty_s> lListMainSoundProperties;

    for(auto soundProperty : listMainSinkProperties)
    {
        lListMainSoundProperties.push_back(ConvertMainSoundProperty(soundProperty));
    }

    OnSinkUpdated(sinkID, sinkClassID, lListMainSoundProperties);
}

void CommandInterfaceConverter::SourceUpdated(const uint16_t& sourceID, const uint16_t& sourceClassID, const vector< ::DBus::Struct< int16_t, int16_t > >& listMainSinkProperties)
{
    vector<am_MainSoundProperty_s> lListMainSoundProperties;

    for(auto soundProperty : listMainSinkProperties)
    {
        lListMainSoundProperties.push_back(ConvertMainSoundProperty(soundProperty));
    }

    OnSourceUpdated(sourceID, sourceClassID, lListMainSoundProperties);
}

void CommandInterfaceConverter::SinkNotification(const uint16_t& sinkID, const ::DBus::Struct< int16_t, int16_t >& notificationPayload)
{
    OnSinkNotification(sinkID, ConvertNotificationPayload(notificationPayload));
}

void CommandInterfaceConverter::SourceNotification(const uint16_t& sourceID, const ::DBus::Struct< int16_t, int16_t >& notificationPayload)
{
    OnSourceNotification(sourceID, ConvertNotificationPayload(notificationPayload));
}

void CommandInterfaceConverter::SinkMainNotificationConfigurationChanged(const uint16_t& sinkID, const ::DBus::Struct< int16_t, int16_t, int16_t >& mainNotificationConfiguration)
{
    OnSinkMainNotificationConfigurationChanged(sinkID, ConvertNotificationConfiguration(mainNotificationConfiguration));
}

void CommandInterfaceConverter::SourceMainNotificationConfigurationChanged(const uint16_t& sourceID, const ::DBus::Struct< int16_t, int16_t, int16_t >& mainNotificationConfiguration)
{
    OnSourceMainNotificationConfigurationChanged(sourceID, ConvertNotificationConfiguration(mainNotificationConfiguration));
}

/*******************************************************************************
 * Converters
 ******************************************************************************/

am_Availability_s CommandInterfaceConverter::ConvertAvailability(const ::DBus::Struct< int16_t, int16_t >& availabilityIn)
{
    am_Availability_s availabilityOut;

    availabilityOut.availability = static_cast<am_Availability_e>(availabilityIn._1);
    availabilityOut.availabilityReason = availabilityIn._2;

    return availabilityOut;
}

am_SinkType_s CommandInterfaceConverter::ConvertSinkType(const ::DBus::Struct< uint16_t, string, ::DBus::Struct< int16_t, int16_t >, int16_t, int16_t, uint16_t >& sinkIn)
{
    am_SinkType_s sinkOut;

    sinkOut.sinkID = sinkIn._1;
    sinkOut.name = sinkIn._2;
    sinkOut.availability = ConvertAvailability(sinkIn._3);
    sinkOut.volume = sinkIn._4;
    sinkOut.muteState = static_cast<am_MuteState_e>(sinkIn._5);
    sinkOut.sinkClassID = sinkIn._6;

    return sinkOut;
}

am_SourceType_s CommandInterfaceConverter::ConvertSourceType(const ::DBus::Struct< uint16_t, string, ::DBus::Struct< int16_t, int16_t >, uint16_t >& sourceIn)
{
    am_SourceType_s sourceOut;

    sourceOut.sourceID = sourceIn._1;
    sourceOut.name = sourceIn._2;
    sourceOut.availability = ConvertAvailability(sourceIn._3);
    sourceOut.sourceClassID = sourceIn._4;

    return sourceOut;
}

am_MainConnectionType_s CommandInterfaceConverter::ConvertMainConnection(const ::DBus::Struct< uint16_t, uint16_t, uint16_t, int16_t, int16_t >& mainConnectionIn)
{
    am_MainConnectionType_s mainConnectionOut;

    mainConnectionOut.mainConnectionID = mainConnectionIn._1;
    mainConnectionOut.sourceID = mainConnectionIn._2;
    mainConnectionOut.sinkID = mainConnectionIn._3;
    mainConnectionOut.delay = mainConnectionIn._4;
    mainConnectionOut.connectionState = static_cast<am_ConnectionState_e>(mainConnectionIn._5);

    return mainConnectionOut;
}

::DBus::Struct< int16_t, int16_t > CommandInterfaceConverter::ConvertMainSoundProperty(const am_MainSoundProperty_s& mainSoundPropertyIn)
{
    ::DBus::Struct< int16_t, int16_t > mainSoundPropertyOut;

    mainSoundPropertyOut._1 = mainSoundPropertyIn.type;
    mainSoundPropertyOut._2 = mainSoundPropertyIn.value;

    return mainSoundPropertyOut;
}

am_MainSoundProperty_s CommandInterfaceConverter::ConvertMainSoundProperty(const ::DBus::Struct< int16_t, int16_t >& mainSoundPropertyIn)
{
    am_MainSoundProperty_s mainSoundPropertyOut;

    mainSoundPropertyOut.type = mainSoundPropertyIn._1;
    mainSoundPropertyOut.value = mainSoundPropertyIn._2;

    return mainSoundPropertyOut;
}

::DBus::Struct< int16_t, int16_t > CommandInterfaceConverter::ConvertSystemProperty(const am_SystemProperty_s& systemPropertyIn)
{
    ::DBus::Struct< int16_t, int16_t > systemPropertyOut;

    systemPropertyOut._1 = systemPropertyIn.type;
    systemPropertyOut._2 = systemPropertyIn.value;

    return systemPropertyOut;
}

am_SystemProperty_s CommandInterfaceConverter::ConvertSystemProperty(const ::DBus::Struct< int16_t, int16_t >& systemPropertyIn)
{
    am_SystemProperty_s systemPropertyOut;

    systemPropertyOut.type = systemPropertyIn._1;
    systemPropertyOut.value = systemPropertyIn._2;

    return systemPropertyOut;
}

am_SourceClass_s CommandInterfaceConverter::ConvertSourceClass(const ::DBus::Struct< uint16_t, string, vector< ::DBus::Struct< int16_t, int16_t > > >& sourceClassIn)
{
    am_SourceClass_s sourceClassOut;

    sourceClassOut.sourceClassID = sourceClassIn._1;
    sourceClassOut.name = sourceClassIn._2;

    for(auto classProperty : sourceClassIn._3)
    {
        sourceClassOut.listClassProperties.push_back(ConvertClassProperty(classProperty));
    }

    return sourceClassOut;
}

am_SinkClass_s CommandInterfaceConverter::ConvertSinkClass(const ::DBus::Struct< uint16_t, string, vector< ::DBus::Struct< int16_t, int16_t > > >& sinkClassIn)
{
    am_SinkClass_s sinkClassOut;

    sinkClassOut.sinkClassID = sinkClassIn._1;
    sinkClassOut.name = sinkClassIn._2;

    for(auto classProperty : sinkClassIn._3)
    {
        sinkClassOut.listClassProperties.push_back(ConvertClassProperty(classProperty));
    }

    return sinkClassOut;
}

am_ClassProperty_s CommandInterfaceConverter::ConvertClassProperty(const ::DBus::Struct< int16_t, int16_t >& classPropertyIn)
{
    am_ClassProperty_s classPropertyOut;

    classPropertyOut.classProperty = classPropertyIn._1;
    classPropertyOut.value = classPropertyIn._2;

    return classPropertyOut;
}

am_NotificationConfiguration_s CommandInterfaceConverter::ConvertNotificationConfiguration(const ::DBus::Struct< int16_t, int16_t, int16_t >& notificationConfigurationIn)
{
    am_NotificationConfiguration_s notificationConfigurationOut;

    notificationConfigurationOut.type = notificationConfigurationIn._1;
    notificationConfigurationOut.status = static_cast<am_NotificationStatus_e>(notificationConfigurationIn._2);
    notificationConfigurationOut.parameter = notificationConfigurationIn._3;

    return notificationConfigurationOut;
}

::DBus::Struct< int16_t, int16_t, int16_t > CommandInterfaceConverter::ConvertNotificationConfiguration(const am_NotificationConfiguration_s& notificationConfigurationIn)
{
    ::DBus::Struct< int16_t, int16_t, int16_t > notificationConfigurationOut;

    notificationConfigurationOut._1 = notificationConfigurationIn.type;
    notificationConfigurationOut._2 = notificationConfigurationIn.status;
    notificationConfigurationOut._3 = notificationConfigurationIn.parameter;

    return notificationConfigurationOut;
}

am_NotificationPayload_s CommandInterfaceConverter::ConvertNotificationPayload(const ::DBus::Struct< int16_t, int16_t >& notificationPayloadIn)
{
    am_NotificationPayload_s notificationPayloadOut;

    notificationPayloadOut.type = notificationPayloadIn._1;
    notificationPayloadOut.value = notificationPayloadIn._2;

    return notificationPayloadOut;
}
