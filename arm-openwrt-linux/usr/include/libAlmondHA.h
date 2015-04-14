/* 
 * File:   libAlmondHA.h
 * Author: santosh
 *
 * Created on 9 July, 2013, 3:10 PM
 */

#ifndef LIBALMONDHA_H
#define	LIBALMONDHA_H
#include <list>
using namespace std;
#ifndef TRUE
#define TRUE 1
#define FALSE 0
#endif

/**
 * DevType enum
 * A detailed list of all the supported device types available via the libAlmondHA library in the Almond SDK
 */

enum DevType {
    UnknownDeviceType = 0, /**< The default device type, in the case of Z-Wave this kind of device will provide only the "Basic Get", "Basic Set" and "Basic Report" command classes*/ 
    BinarySwitch , /**< A simple on/off switch. This kind of device provides only binary on/off operation. For Z-Wave it will use the COMMAND_CLASS_SWITCH_BINARY, for Zigbee it uses the ZigBeeHA 1.2 ON/OFF-CLUSTER. */
    MultilevelSwitch, /**< A Multilevel switch which has binary on/off operation as well as level control fuctionality. For Z-Wave it will use the COMMAND_CLASS_SWITCH_MULTILEVEL and for ZigBee it will use ON/OFF-CLUSTER and LEVEL-CONTROL-CLUSTER*/
    BinarySensor , /**< A basic sensor which returns a true or false state. For Z-Wave it uses the COMMAND_CLASS_SENSOR_BINARY and for ZigBee it uses the IAS Zone Cluster*/
    MultilevelSwitchOnOff, /**< Same as MultilevelSwitch*/
    DoorLock , /**< A Connected Door Lock, uses the Z-Wave COMMAND_CLASS_SECURITY and COMMAND_CLASS_DOOR_LOCK, ZigBee Door Lock Cluster*/
    Alarm , /**< A connected Siren or Security Alarm, uses the Z-Wave COMMAND_CLASS_SECURITY and COMMAND_CLASS_ALARM, ZigBee Alarm Cluster*/
    Thermostat, /**< A connected thermostat, uses the Z-Wave COMMAND_CLASS_THERMOSTAT_MODE, COMMAND_CLASS_THERMOSTAT_FAN_MODE, COMMAND_CLASS_THERMOSTAT_FAN_STATE, COMMAND_CLASS_THERMOSTAT_OPERATING_STATE, COMMAND_CLASS_THERMOSTAT_SETBACK, COMMAND_CLASS_THERMOSTAT_SETPOINT and COMMAND_CLASS_SENSOR_MULTILEVEL and for ZigBee it will use Thermostat Cluster */
    Gateway, /**< A Z-Wave device defined as a Primary or Secondary Controller. Uses the Z-Wave COMMAND_CLASS_VERSION, COMMAND_CLASS_BASIC and COMMAND_CLASS_MANUFACTURER_SPECIFIC */
    SceneController , /**< A Z-Wave Scene Controller device. Uses Z-Wave COMMAND_CLASS_SCENE_ACTIVATION and COMMAND_CLASS_CONTROLLER_CONF*/
    StandardCIE , /**< A ZigBee device CIE (Control and Indicating Equipment). Uses ZigBee IAS Zone Cluster*/
    MotionSensor, /**< A connected Motion Sensor. Uses Z-Wave COMMAND_CLASS_SENSOR_BINARY and ZigBee IAS Zone Cluster */
    ContactSwitch, /**< A connected Contact Switch (Door/Window Sensor). Uses Z-Wave COMMAND_CLASS_SENSOR_BINARY and ZigBee IAS Zone Cluster*/
    FireSensor , /**< A connected Fire Sensor (or Smoke Alarm). Uses Z-Wave COMMAND_CLASS_SENSOR_BINARY and ZigBee IAS Zone Cluster*/
    WaterSensor , /**< A connected Water Sensor (Flood Sensor). Uses Z-Wave COMMAND_CLASS_SENSOR_BINARY and ZigBee IAS Zone Cluster*/
    GasSensor , /**< A connected Gas Sensor. Uses Z-Wave COMMAND_CLASS_SENSOR_BINARY and ZigBee IAS Zone Cluster*/
    PersonalEmergencyDevice, /**< */
    VibrationOrMovementSensor, /**< A connected Vibration or Movement Sensor. Uses Z-Wave COMMAND_CLASS_SENSOR_BINARY and ZigBee IAS Zone Cluster*/
    RemoteControl , /**< Same as Gateway*/
    KeyFob , /**< A connected Keyfob or Presence Sensor. Uses Z-Wave COMMAND_CLASS_CONFIGURATION and ZigBee IAS Zone Cluster*/
    Keypad , /**< */
    StandardWarningDevice , /**< See Alarm*/
    SmartACSwitch , /**< A ZigBee switch with intigerated AC Electrical Measurment. Uses ZigBee On/Off Cluster and Electrical Measurement Cluster*/
    SmartDCSwitch , /**< A ZigBee switch with intigerated AC Electrical Measurment. Uses ZigBee On/Off Cluster and Electrical Measurement Cluster*/
    OccupancySensor , /**< A connected Occupancy Sensor. Uses Z-Wave COMMAND_CLASS_SENSOR_BINARY and ZigBee Occupancy Sensing Cluster*/
    LightSensor , /**< A connected Light Sensor. Uses Z-Wave COMMAND_CLASS_SENSOR_BINARY and ZigBee Illuminance Measurement Cluster and Illuminance Level Sensing Cluster*/
    WindowCovering , /**< A connected Window Cover Actuator. Uses Z-Wave COMMAND_CLASS_MULTILEVEL and COMMAND_CLASS_BASIC_WINDOW_COVERING and ZigBee Window Covering Cluster*/
    TemperatureSensor, /**< A connected Temperature Sensor. Uses Z-Wave COMMAND_CLASS_SENSOR_MULTILEVEL and ZigBee IAS Zone Cluster*/
    SimpleMetering, /**< */
    ColorControl, /**< */
    PressureSensor, /**< */
    FlowSensor, /**< */
    ColorDimmableLight, /**< */
    HAPump, /**< */
    Shade /**< */

};

enum DevTech {
    UnknownTechnology = 0,
    ZigBeeTechnology = 1,
    ZWaveTechnology = 2
};

struct DeviceValuePair {
    int index;
    char name[30];
    char value[25];
    int CommandClassID;
    int CommandIndex;
    int EndPoint;
};

class Device {
public:
    Device();
    Device(int DevID);
    ~Device();
    int getID(void);
    char* getValue(int index);
    char* getValue(char* name);
    char* getValueName(int index);

    void setValue(char*, char*);
    void setValue(int, char*);
    DevType getDeviceType(void);
    DevTech getDeviceTechnology(void);
    int getOZWNode(void);
    int getShortID(void);
    char * getZigBeeEUI64(void);
    char * getDeviceName(void);
    char * getDeviceLocation(void);
    char * getFriendlyDeviceType(void);
    bool getAllowNotificiation(void);
    int getValueCount(void);
    void setAllowNotification(bool);
    void fromDeviceID(int DevID);
    void setSwitchLevel(int level);
    void setSwitchOn(bool val);
    void setSwitchAll(bool val);
    void setSwitchToggle(void);
    void setThermostatHeatingTemp(int temp);
    void setThermostatCoolingTemp(int temp);
    void setThermostatFanMode(char *mode);
    void setThermostatMode(char* mode);
    void setDoorLock(int val);
    void setDoorLockConf(int val);
    void setBasic(int val);
    void getBasic(void);
    void wakeUpDevice(void);
    void startAlarm(bool val);
    ///void kickDeviceFromNetwork(void);
    void startWindowCovering(bool val);
    void stopWindowCovering(bool val);
    void setSceneControllerConf(int val);
    void startDimming(bool val);
    void startBrightning(bool val);
    int getBatterLevel(void);
    int getLastNotificationIndex(void);
    char* getLastNotificationIndexName(void);
    char* getLastNotificationIndexValue(void);
    void RefreshDevice(void);
    void setLocation(char* data);
    void setName(char* data);
    void clearTamper(void);
    char* getTamper(void);
    char* getRemovedeviceid(void);
    void testserver(void);

private:

    int getEndPoint(int index);
    int getCommandClassID(int index);
    int getCommandIndex(int index);
    int DeviceId;
    char Name[180];
    char Location[180];
    int OZWNode;
    int ZigBeeShortID;
    char ZigBeeEUI64[25];
    DevTech DeviceTechnology;
    char AssociationTimeStamp[32];
    DevType Type;
    char DeviceType[32];
    char FriendlyDeviceType[32];
    bool AllowNotification;
    int LastNotificationIndex;
    char LastNotificationValue[25];
    int ValueCount;
    list <DeviceValuePair> dvPairs;
};

class DeviceList {
public:
    DeviceList();
    void Populate(void);
    void PopulateByType(DevType type);
    void PopulateByScene(int sceneID);
    void PopulateByGroup(int groupID);
    list <Device> devices;
private:
    void addDevice(int DevID);
};

class Group {
public:
    Group();
    //Group(&Group);
    ~Group();
    int getID(void);
    int getState(void);
    void activate(void);
    void deactivate(void);
    void addDeviceToGroup(int);
    void removeDevice(int);
    DeviceList* getDevice(void);
};

class Scene {
public:
    Scene();
    //    Scene(&Scene);
    ~Scene();
    int getID(void);
    int lastActivated(void);
    void Activate(void);
    void addDVpairToScene(int, int, char*);
    void removeDevice(int);
    DeviceList* getDevices(void);

};

class Rule {
public:
    Rule();

};

class Association {
public:
    Association();
};

class HADevices {
public:
    HADevices();
    static void initialize(void);
    static void CloudInitialize(void);
    static void luaInitialize(void);
    static Device* getDeviceByID(int ID);
    static DeviceList* getDeviceList(void);
    static DeviceList* getDeviceByType(DevType);
    static DeviceList* getDeviceByHop(int);
    static Group* getGroupByID(int);
    static Scene* getSceneByID(int);
    static Rule* getRuleByID(int);
    static void genericCallback(void (*callback)(Device *));
    static void deviceCallback(int DevID, void (*callback)(Device *));
private:
    static int deviceID;

};


#endif	/* LIBALMONDHA_H */

