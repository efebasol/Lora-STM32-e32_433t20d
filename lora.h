#ifndef INC_LORA_STM32_H_
#define INC_LORA_STM32_H_

#include "stm32f4xx_hal.h"

// Serial check digit
typedef enum
{
    // Default
    serialPortMode_8N1 = (0x00 << 0x06),
    serialPortMode_801 = (0x01 << 0x06),
    serialPortMode_8E1 = (0x02 << 0x06)
} serialPortMode_t;

// TTL serial port rate (bps)
typedef enum
{
    baudRate_1200 = (0x00 << 0x03),
    baudRate_2400 = (0x01 << 0x03),
    baudRate_4800 = (0x02 << 0x03),
    // Default
    baudRate_9600 = (0x03 << 0x03),
    baudRate_19200 = (0x04 << 0x03),
    baudRate_38400 = (0x05 << 0x03),
    baudRate_57600 = (0x06 << 0x03),
    baudRate_115200 = (0x07 << 0x03)
} baudRate_t;

// Common Wireless Air Rate (bps)
typedef enum
{
    airRate_03K = (0x00 << 0x00),
    airRate_12K = (0x01 << 0x00),
    // Default
    airRate_24K = (0x02 << 0x00),
    airRate_48K = (0x03 << 0x00),
    airRate_96K = (0x04 << 0x00),
    airRate_192K = (0x05 << 0x00)
} airRate_t;

// Fixed-point transmit enable bit (like MODBUS)
typedef enum
{
    transmissionMode_Transparent = (0x00 << 0x07),
    transmissionMode_Fixed = (0x01 << 0x07)
} transmissionMode_t;

// IO drive mode
typedef enum
{
    IODriveMode_PushPull = (0x00 << 0x06),
    // Default
    IODriveMode_OpenCircuit = (0x01 << 0x06)
} IODriveMode_t;

// Wireless wake-up time
typedef enum
{
    // Default
    wakeUpTime_250ms = (0x00 << 0x03),
    wakeUpTime_500ms = (0x01 << 0x03),
    wakeUpTime_750ms = (0x02 << 0x03),
    wakeUpTime_1000ms = (0x03 << 0x03),
    wakeUpTime_1250ms = (0x04 << 0x03),
    wakeUpTime_1500ms = (0x05 << 0x03),
    wakeUpTime_1750ms = (0x06 << 0x03),
    wakeUpTime_2000ms = (0x07 << 0x03)
} wakeUpTime_t;

// FEC switch
typedef enum
{
    FECswitch_off = (0x00 << 0x02),
    // Default
    FECswitch_on = (0x01 << 0x02)
} FECswitch_t;

// Transmit power
typedef enum
{
    // Default
    transmitPower_20dBm = (0x00 << 0x00),
    transmitPower_17dBm = (0x01 << 0x00),
    transmitPower_14dBm = (0x02 << 0x00),
    transmitPower_10dBm = (0x04 << 0x00)
} transmitPower_t;

typedef struct
{
    uint8_t ADDH;
    uint8_t ADDL;
    uint8_t CHAN;

    serialPortMode_t serialPortMode;
    baudRate_t baudRate;
    airRate_t airRate;

    transmissionMode_t transmissionMode;
    IODriveMode_t IODriveMode;
    wakeUpTime_t wakeUpTime;
    FECswitch_t FECswitch;
    transmitPower_t transmitPower;

} LoraConfig_t;

/**
 * @brief  Configuration library for the EBYTE E32-433T20D LoRa module
 * @note   Provides a structured interface to configure the LoRa module via UART.
 *         All parameters (address, channel, baud rate, air data rate, etc.) are set using LoraConfig_t.
 * @usage  LoraConfig_t config = { ... };
 *         Lora_applyConfig(&huartX, &config);
 */

HAL_StatusTypeDef Lora_applyConfig(UART_HandleTypeDef *huart, LoraConfig_t *config);
HAL_StatusTypeDef Lora_sendPacket(UART_HandleTypeDef *huart, uint8_t addh, uint8_t addl, uint8_t chan, const void *payload, uint16_t payloadSize);
void Lora_onUartReceiveITComplete(void);
void Lora_onUartReceiveIT(SensorData_t *data);

#endif /* INC_LORA_STM32_H_ */