/* 
 * File:   libAlmondHA_Private.h
 * Author: santosh
 *
 * Created on 26 July, 2013, 3:22 PM
 */

#ifndef LIBALMONDHA_PRIVATE_H
#define	LIBALMONDHA_PRIVATE_H

using namespace std;
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

void *receiver(void *); //receives packets from zigbee & ozw server.
void ConnectToServers(int which); //used for connecting to ozw & zigbee servers if connection fails program will die; which=0 means end, which=1 means cloud
void SendDataPacketToZigbeeServer(void);
void SendDataPacketToOZWServer(void);

typedef struct HASERVER_PACKET {
    int DevID;
    int LastNotificationIndex;
    char LastNotificationValue[25];
} haserver_packet;

typedef struct {
    int DevID;
    char command[180];
    char Data[180];
} SET_DATA;

SET_DATA set_data, receive_data;

/*    UnknownDeviceType = 0,
    BinarySwitch = 1,
    MultilevelSwitch = 2,
    BinarySensor,
    Sensor,
    DoorLock,
    Alarm,
    Thermostat,
    Gateway,
    SceneController,
    StandardCIE,
    MotionSensor,
    ContactSwitch,
    FireSensor,
    WaterSensor,
    GasSensor,
    PersonalEmergencyDevice,
    VibrationOrMovementSensor,
    RemoteControl,
    KeyFob,
    Keypad,
    StandardWarningDevice,
    ElectricalMeasurement,
    OccupancySensor,
    IlluminanceMeasurement,
    TemperatureMeasurement,
    WindowCovering,
    ColorControl,
    PressureMeasurement*/



DevType StrToDevType(char *str) {
    if (strcmp(str, "BinarySwitch") == 0)
        return BinarySwitch;
    else if (strcmp(str, "MultilevelSwitch") == 0)
        return MultilevelSwitch;
    else if (strcmp(str, "BinarySensor") == 0)
        return BinarySensor;
    else if (strcmp(str, "MultilevelSwitchOnOff") == 0)
        return MultilevelSwitchOnOff;
    else if (strcmp(str, "DoorLock") == 0)
        return DoorLock;
    else if (strcmp(str, "Alarm") == 0)
        return Alarm;
    else if (strcmp(str, "Thermostat") == 0)
        return Thermostat;
    else if (strcmp(str, "Gateway") == 0)
        return Gateway;
    else if (strcmp(str, "SceneController") == 0)
        return SceneController;
    else if (strcmp(str, "StandardCIE") == 0)
        return StandardCIE;
    else if (strcmp(str, "MotionSensor") == 0)
        return MotionSensor;
    else if (strcmp(str, "ContactSwitch") == 0){
        return ContactSwitch;
    }
    else if (strcmp(str, "FireSensor") == 0)
        return FireSensor;
    else if (strcmp(str, "WaterSensor") == 0)
        return WaterSensor;
    else if (strcmp(str, "GasSensor") == 0)
        return GasSensor;
    else if (strcmp(str, "PersonalEmergencyDevice") == 0)
        return PersonalEmergencyDevice;
    else if (strcmp(str, "VibrationOrMovementSensor") == 0)
        return VibrationOrMovementSensor;
    else if (strcmp(str, "RemoteControl") == 0)
        return RemoteControl;
    else if (strcmp(str, "KeyFob") == 0)
        return KeyFob;
    else if (strcmp(str, "Keypad") == 0)
        return Keypad;
    else if (strcmp(str, "StandardWarningDevice") == 0)
        return StandardWarningDevice;
    else if (strcmp(str, "SmartACSwitch") == 0)
        return SmartACSwitch;
    else if (strcmp(str, "SmartDCSwitch") == 0)
        return SmartDCSwitch;
    else if (strcmp(str, "OccupancySensor") == 0)
        return OccupancySensor;
    else if (strcmp(str, "LightSensor") == 0)
        return LightSensor;
    else if (strcmp(str, "TemperatureSensor") == 0)
        return TemperatureSensor;
    else if (strcmp(str, "WindowCovering") == 0)
        return WindowCovering;
    else if (strcmp(str, "ColorControl") == 0)
        return ColorControl;
    else if (strcmp(str, "PressureSensor") == 0)
        return PressureSensor;
    else if (strcmp(str, "FlowSensor") == 0)
        return FlowSensor;
    else if (strcmp(str, "ColorDimmableLight") == 0)
        return ColorDimmableLight;
    else if (strcmp(str, "HAPump") == 0)
        return HAPump;
    else if (strcmp(str, "Shade") == 0)
        return Shade;
    else
        return UnknownDeviceType;

    return UnknownDeviceType;
}

#endif	/* LIBALMONDHA_PRIVATE_H */

