/**
 * @file mtdef.h
 * @brief Definitions for XSens MT device communication
 *
 * Contains definitions and enumerations for the XSens MT device protocol
 */

#ifndef MTDEF_H
#define MTDEF_H

#include <stdint.h>

/**
 * @brief Message IDs for MT device communication
 */
typedef enum {
    MID_WakeUp = 0x3E,
    MID_WakeUpAck = 0x3F,
    MID_GoToConfig = 0x30,
    MID_GoToConfigAck = 0x31,
    MID_GoToMeasurement = 0x10,
    MID_GoToMeasurementAck = 0x11,
    MID_Reset = 0x40,
    MID_ResetAck = 0x41,
    MID_ReqDID = 0x00,
    MID_ReqDIDAck = 0x01,
    MID_ReqProductCode = 0x1C,
    MID_ReqProductCodeAck = 0x1D,
    MID_ReqHardwareVersion = 0x1E,
    MID_ReqHardwareVersionAck = 0x1F,
    MID_ReqFWRev = 0x12,
    MID_ReqFWRevAck = 0x13,
    MID_RunSelfTest = 0x24,
    MID_RunSelfTestAck = 0x25,
    MID_SetBaudrate = 0x18,
    MID_SetBaudrateAck = 0x19,
    MID_SetErrorMode = 0xDA,
    MID_SetErrorModeAck = 0xDB,
    MID_SetOptionFlags = 0x48,
    MID_SetOptionFlagsAck = 0x49,
    MID_SetLocationID = 0x84,
    MID_SetLocationIDAck = 0x85,
    MID_Error = 0x42,
    MID_MTData = 0x32,
    MID_MTDataAck = 0x33
} MTMessageID;

/**
 * @brief Device states
 */
typedef enum {
    MT_STATE_INIT,
    MT_STATE_CONFIG,
    MT_STATE_MEASUREMENT
} MTDeviceState;

/**
 * @brief Output mode settings
 */
typedef enum {
    OUTPUTMODE_TEMP = 0x0001,
    OUTPUTMODE_CALIB = 0x0002,
    OUTPUTMODE_ORIENT = 0x0004,
    OUTPUTMODE_AUXILIARY = 0x0008,
    OUTPUTMODE_POSITION = 0x0010,
    OUTPUTMODE_VELOCITY = 0x0020,
    OUTPUTMODE_STATUS = 0x0800
} MTOutputMode;

/**
 * @brief Output settings
 */
typedef enum {
    OUTPUTSETTINGS_TIMESTAMP_NONE = 0x00000000,
    OUTPUTSETTINGS_TIMESTAMP_SAMPLECNT = 0x00000001,
    OUTPUTSETTINGS_ORIENTMODE_QUATERNION = 0x00000000,
    OUTPUTSETTINGS_ORIENTMODE_EULER = 0x00000080,
    OUTPUTSETTINGS_ORIENTMODE_MATRIX = 0x00000100,
    OUTPUTSETTINGS_CALIBMODE_ACCGYRMAG = 0x00000000,
    OUTPUTSETTINGS_CALIBMODE_ACC = 0x00000010,
    OUTPUTSETTINGS_CALIBMODE_GYR = 0x00000020,
    OUTPUTSETTINGS_CALIBMODE_MAG = 0x00000040,
    OUTPUTSETTINGS_CALIBMODE_ACCGYR = 0x00000030,
    OUTPUTSETTINGS_CALIBMODE_ACCMAG = 0x00000050
} MTOutputSettings;

/**
 * @brief Baudrate values
 */
typedef enum {
    BAUDRATE_4800 = 0x0B,
    BAUDRATE_9600 = 0x09,
    BAUDRATE_14400 = 0x08,
    BAUDRATE_19200 = 0x07,
    BAUDRATE_28800 = 0x06,
    BAUDRATE_38400 = 0x05,
    BAUDRATE_57600 = 0x04,
    BAUDRATE_76800 = 0x03,
    BAUDRATE_115200 = 0x02,
    BAUDRATE_230400 = 0x01,
    BAUDRATE_460800 = 0x00,
    BAUDRATE_921600 = 0x80
} MTBaudrates;

/**
 * @brief Error messages
 */
typedef enum {
    ERROR_NONE = 0,
    ERROR_INVALID_MESSAGE = 0x04,
    ERROR_OPERATION_FAILED = 0x08,
    ERROR_TIMEOUT = 0x0C,
    ERROR_INVALID_BAUDRATE = 0x20,
    ERROR_INVALID_PARAMETER = 0x28,
    ERROR_PROCESSING_FAILED = 0x2C
} MTErrorCode;

/**
 * @brief Get name of message ID
 *
 * @param mid Message ID
 * @return const char* Name of the message ID
 */
const char* getMIDName(uint8_t mid);

#endif /* MTDEF_H */
