/* Automatically generated nanopb constant definitions */
/* Generated by nanopb-0.3.1 at Tue Dec 30 12:04:06 2014. */

#include "morpheus_ble.pb.h"

#if PB_PROTO_HEADER_VERSION != 30
#error Regenerate this file with the current version of nanopb generator.
#endif



const pb_field_t wifi_endpoint_fields[5] = {
    PB_FIELD(  1, STRING  , REQUIRED, CALLBACK, FIRST, wifi_endpoint, ssid, ssid, 0),
    PB_FIELD(  2, BYTES   , OPTIONAL, CALLBACK, OTHER, wifi_endpoint, bssid, ssid, 0),
    PB_FIELD(  4, INT32   , REQUIRED, STATIC  , OTHER, wifi_endpoint, rssi, bssid, 0),
    PB_FIELD(  5, ENUM    , REQUIRED, STATIC  , OTHER, wifi_endpoint, security_type, rssi, 0),
    PB_LAST_FIELD
};

const pb_field_t pill_data_fields[7] = {
    PB_FIELD(  1, STRING  , REQUIRED, STATIC  , FIRST, pill_data, device_id, device_id, 0),
    PB_FIELD(  2, INT32   , OPTIONAL, STATIC  , OTHER, pill_data, battery_level, device_id, 0),
    PB_FIELD(  3, INT32   , OPTIONAL, STATIC  , OTHER, pill_data, uptime, battery_level, 0),
    PB_FIELD(  4, BYTES   , OPTIONAL, STATIC  , OTHER, pill_data, motion_data_entrypted, uptime, 0),
    PB_FIELD(  5, INT32   , OPTIONAL, STATIC  , OTHER, pill_data, firmware_version, motion_data_entrypted, 0),
    PB_FIELD(  6, UINT64  , REQUIRED, STATIC  , OTHER, pill_data, timestamp, firmware_version, 0),
    PB_LAST_FIELD
};

const pb_field_t MorpheusCommand_fields[16] = {
    PB_FIELD(  1, INT32   , REQUIRED, STATIC  , FIRST, MorpheusCommand, version, version, 0),
    PB_FIELD(  2, ENUM    , REQUIRED, STATIC  , OTHER, MorpheusCommand, type, version, 0),
    PB_FIELD(  3, STRING  , OPTIONAL, CALLBACK, OTHER, MorpheusCommand, deviceId, type, 0),
    PB_FIELD(  4, STRING  , OPTIONAL, CALLBACK, OTHER, MorpheusCommand, accountId, deviceId, 0),
    PB_FIELD(  5, ENUM    , OPTIONAL, STATIC  , OTHER, MorpheusCommand, error, accountId, 0),
    PB_FIELD(  6, STRING  , OPTIONAL, CALLBACK, OTHER, MorpheusCommand, wifiName, error, 0),
    PB_FIELD(  7, STRING  , OPTIONAL, CALLBACK, OTHER, MorpheusCommand, wifiSSID, wifiName, 0),
    PB_FIELD(  8, STRING  , OPTIONAL, CALLBACK, OTHER, MorpheusCommand, wifiPassword, wifiSSID, 0),
    PB_FIELD(  9, INT32   , OPTIONAL, STATIC  , OTHER, MorpheusCommand, batteryLevel, wifiPassword, 0),
    PB_FIELD( 10, INT32   , OPTIONAL, STATIC  , OTHER, MorpheusCommand, uptime, batteryLevel, 0),
    PB_FIELD( 13, INT32   , OPTIONAL, STATIC  , OTHER, MorpheusCommand, firmwareVersion, uptime, 0),
    PB_FIELD( 14, MESSAGE , REPEATED, CALLBACK, OTHER, MorpheusCommand, wifi_scan_result, firmwareVersion, &wifi_endpoint_fields),
    PB_FIELD( 15, ENUM    , OPTIONAL, STATIC  , OTHER, MorpheusCommand, security_type, wifi_scan_result, 0),
    PB_FIELD( 16, MESSAGE , OPTIONAL, STATIC  , OTHER, MorpheusCommand, pill_data, security_type, &pill_data_fields),
    PB_FIELD( 17, ENUM    , OPTIONAL, STATIC  , OTHER, MorpheusCommand, wifi_connection_state, pill_data, 0),
    PB_LAST_FIELD
};

const pb_field_t batched_pill_data_fields[3] = {
    PB_FIELD(  1, MESSAGE , REPEATED, CALLBACK, FIRST, batched_pill_data, pills, pills, &pill_data_fields),
    PB_FIELD(  2, STRING  , REQUIRED, CALLBACK, OTHER, batched_pill_data, device_id, pills, 0),
    PB_LAST_FIELD
};


/* Check that field information fits in pb_field_t */
#if !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_32BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in 8 or 16 bit
 * field descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(MorpheusCommand, wifi_scan_result) < 65536 && pb_membersize(MorpheusCommand, pill_data) < 65536 && pb_membersize(batched_pill_data, pills) < 65536), YOU_MUST_DEFINE_PB_FIELD_32BIT_FOR_MESSAGES_wifi_endpoint_pill_data_MorpheusCommand_batched_pill_data)
#endif

#if !defined(PB_FIELD_16BIT) && !defined(PB_FIELD_32BIT)
/* If you get an error here, it means that you need to define PB_FIELD_16BIT
 * compile-time option. You can do that in pb.h or on compiler command line.
 * 
 * The reason you need to do this is that some of your messages contain tag
 * numbers or field sizes that are larger than what can fit in the default
 * 8 bit descriptors.
 */
PB_STATIC_ASSERT((pb_membersize(MorpheusCommand, wifi_scan_result) < 256 && pb_membersize(MorpheusCommand, pill_data) < 256 && pb_membersize(batched_pill_data, pills) < 256), YOU_MUST_DEFINE_PB_FIELD_16BIT_FOR_MESSAGES_wifi_endpoint_pill_data_MorpheusCommand_batched_pill_data)
#endif


