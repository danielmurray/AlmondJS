/* 
 * File:   cluster-id.h
 * Author: santosh
 *
 * Created on 23 July, 2013, 2:58 PM
 */

#ifndef CLUSTER_ID_H
#define	CLUSTER_ID_H

// Cluster domain specification levels:
//   * General: zcl-1.0-07-5123-03
//   * Closures: zcl-1.0-07-5123-03
//   * HVAC: zcl-1.0-07-5123-03
//   * Lighting: zcl-1.0-07-5123-03
//   * Measurement & Sensing: zcl-1.0-07-5123-03
//   * Security & Safety: zcl-1.0-07-5123-03
//   * HA: ha-1.2-11-5474-19
//   * Home Automation: UNKNOWN
//   * CBA: cba-1.0-05-3516-12
//   * SE: se-1.1.1-07-5356-17
//   * ZLL: zll-1.0-11-0037-10
//   * Ember: UNKNOWN
//   * HC: hc-1.0-07-5360-15
#define ZCL_BASIC_CLUSTER_ID                         0x0000
#define ZCL_POWER_CONFIG_CLUSTER_ID                  0x0001
#define ZCL_DEVICE_TEMP_CLUSTER_ID                   0x0002
#define ZCL_IDENTIFY_CLUSTER_ID                      0x0003
#define ZCL_GROUPS_CLUSTER_ID                        0x0004
#define ZCL_SCENES_CLUSTER_ID                        0x0005
#define ZCL_ON_OFF_CLUSTER_ID                        0x0006
#define ZCL_ON_OFF_SWITCH_CONFIG_CLUSTER_ID          0x0007
#define ZCL_LEVEL_CONTROL_CLUSTER_ID                 0x0008
#define ZCL_ALARM_CLUSTER_ID                         0x0009
#define ZCL_TIME_CLUSTER_ID                          0x000A
#define ZCL_RSSI_LOCATION_CLUSTER_ID                 0x000B
#define ZCL_BINARY_INPUT_BASIC_CLUSTER_ID            0x000F
#define ZCL_COMMISSIONING_CLUSTER_ID                 0x0015
#define ZCL_SHADE_CONFIG_CLUSTER_ID                  0x0100
#define ZCL_PUMP_CONFIG_CONTROL_CLUSTER_ID           0x0200
#define ZCL_THERMOSTAT_CLUSTER_ID                    0x0201
#define ZCL_FAN_CONTROL_CLUSTER_ID                   0x0202
#define ZCL_DEHUMID_CONTROL_CLUSTER_ID               0x0203
#define ZCL_THERMOSTAT_UI_CONFIG_CLUSTER_ID          0x0204
#define ZCL_COLOR_CONTROL_CLUSTER_ID                 0x0300
#define ZCL_BALLAST_CONFIGURATION_CLUSTER_ID         0x0301
#define ZCL_ILLUM_MEASUREMENT_CLUSTER_ID             0x0400
#define ZCL_ILLUM_LEVEL_SENSING_CLUSTER_ID           0x0401
#define ZCL_TEMP_MEASUREMENT_CLUSTER_ID              0x0402
#define ZCL_PRESSURE_MEASUREMENT_CLUSTER_ID          0x0403
#define ZCL_FLOW_MEASUREMENT_CLUSTER_ID              0x0404
#define ZCL_RELATIVE_HUMIDITY_MEASUREMENT_CLUSTER_ID 0x0405
#define ZCL_OCCUPANCY_SENSING_CLUSTER_ID             0x0406
#define ZCL_IAS_ZONE_CLUSTER_ID                      0x0500
#define ZCL_IAS_ACE_CLUSTER_ID                       0x0501
#define ZCL_IAS_WD_CLUSTER_ID                        0x0502
#define ZCL_DOOR_LOCK_CLUSTER_ID                     0x0101
#define ZCL_WINDOW_COVERING_CLUSTER_ID               0x0102
#define ZCL_POWER_PROFILE_CLUSTER_ID                 0x001A
#define ZCL_APPLIANCE_CONTROL_CLUSTER_ID             0x001B
#define ZCL_POLL_CONTROL_CLUSTER_ID                  0x0020
#define ZCL_APPLIANCE_IDENTIFICATION_CLUSTER_ID      0x0B00
#define ZCL_METER_IDENTIFICATION_CLUSTER_ID          0x0B01
#define ZCL_APPLIANCE_EVENTS_AND_ALERT_CLUSTER_ID    0x0B02
#define ZCL_ELECTRICAL_MEASUREMENT_CLUSTER_ID        0x0B04
#define ZCL_DIAGNOSTICS_CLUSTER_ID                   0x0B05
#define ZCL_GENERIC_TUNNEL_CLUSTER_ID                0x0600
#define ZCL_BACNET_PROTOCOL_TUNNEL_CLUSTER_ID        0x0601
#define ZCL_OTA_BOOTLOAD_CLUSTER_ID                  0x0019
#define ZCL_DEMAND_RESPONSE_LOAD_CONTROL_CLUSTER_ID  0x0701
#define ZCL_SIMPLE_METERING_CLUSTER_ID               0x0702
#define ZCL_PRICE_CLUSTER_ID                         0x0700
#define ZCL_MESSAGING_CLUSTER_ID                     0x0703
#define ZCL_TUNNELING_CLUSTER_ID                     0x0704
#define ZCL_KEY_ESTABLISHMENT_CLUSTER_ID             0x0800
#define ZCL_ZLL_COMMISSIONING_CLUSTER_ID             0x1000
#define ZCL_SAMPLE_MFG_SPECIFIC_CLUSTER_ID           0xFC00
#define ZCL_11073_PROTOCOL_TUNNEL_CLUSTER_ID         0x0614


#endif	/* CLUSTER_ID_H */

