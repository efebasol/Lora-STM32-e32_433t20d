
# 📡 EBYTE E32-433T20D LoRa Configuration Library for STM32

A lightweight and modular C library for configuring the **EBYTE E32-433T20D LoRa module** using STM32 and HAL-based UART communication. This library provides full control over LoRa module settings such as address, channel, baud rate, air data rate, I/O mode, wake-up time, FEC, and transmission power.

---

## 🚀 Features

- 🔌 UART-based configuration using STM32 HAL (`UART_HandleTypeDef`)
- 📦 All parameters packed into a single struct (`LoraConfig_t`)
- ✅ Clear and type-safe enums for better readability
- 🛠️ Easy to integrate and use in embedded projects
- 💡 Supports both runtime and one-time configuration modes

---

## 📁 File Structure

```
├── lora_stm32.h     // Header file: Enums, struct, and function prototype
├── lora_stm32.c     // Source file: Implementation of applyConfig function
├── README.md        // This file
```

---

## 📐 LoraConfig_t Struct

```c
typedef struct {
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
```

All LoRa settings are wrapped inside this structure and sent to the module via `Lora_applyConfig()`.

---

## 📚 Example Usage

```c
#include "lora_stm32.h"

LoraConfig_t config = {
    .ADDH = 0x00,
    .ADDL = 0x01,
    .CHAN = 0x17,

    .serialPortMode = serialPortMode_8N1,
    .baudRate = baudRate_9600,
    .airRate = airRate_24K,

    .transmissionMode = transmissionMode_Transparent,
    .IODriveMode = IODriveMode_OpenCircuit,
    .wakeUpTime = wakeUpTime_250ms,
    .FECswitch = FECswitch_on,
    .transmitPower = transmitPower_20dBm
};

Lora_applyConfig(&huart3, &config);  // Send configuration to LoRa module
```

> 🔧 Ensure the module is in programming mode (M0 = HIGH, M1 = HIGH) before sending the configuration.

---

## 🔧 API Reference

### `void Lora_applyConfig(UART_HandleTypeDef *huart, LoraConfig_t *config);`

- **@param** `huart`: Pointer to a configured UART handle
- **@param** `config`: Pointer to a `LoraConfig_t` structure containing all desired parameters
- **@brief** Sends the 6-byte configuration array to the LoRa module using `HAL_UART_Transmit`

---

## 🧱 Enum Definitions

The following enums are used to define configuration options cleanly:

- `serialPortMode_t`: UART data format (8N1, 801, 8E1)
- `baudRate_t`: UART baud rate (1200 – 115200)
- `airRate_t`: LoRa air data rate (0.3K – 192Kbps)
- `transmissionMode_t`: Transparent or Fixed-point mode
- `IODriveMode_t`: Push-pull or open-collector I/O
- `wakeUpTime_t`: Wake-up delay (250ms – 2000ms)
- `FECswitch_t`: Forward error correction (on/off)
- `transmitPower_t`: Output power level (10 – 20 dBm)

---

## ✅ To-Do / Future Plans

- Add GPIO control for M0/M1 mode selection
- Support configuration reading (readback)
- Add compatibility for E22 or SPI-based LoRa modules

---

## 🛠 Requirements

- STM32 with HAL library enabled
- UART interface connected to LoRa module
- LoRa module placed in programming mode before applying config
- Optional: GPIO access for M0 and M1 control

---

## 📃 License

MIT License. Free to use, modify, and distribute.

---

## ✨ Credits

Developed by **Efe BASOL**  
Inspired by the EBYTE documentation and STM32 HAL UART usage.
