# 📡 EBYTE E32-433T20D LoRa Configuration Library for STM32

A lightweight and modular C library for configuring and communicating with the **EBYTE E32-433T20D LoRa module** using STM32 HAL-based UART.  
The library provides:

- Full runtime configuration of the module.
- Send/receive any **user-defined struct** with optional addressing support.

---

## 🚀 Features

- ✅ Fully configurable via `LoraConfig_t`
- 📤 Supports sending any `struct` as payload
- 📥 Interrupt-driven receive helper example
- 🧩 Easily integratable with STM32CubeMX HAL projects
- 🔒 Type-safe enum-based configuration

---

## 📁 File Structure

```
├── lora_stm32.h     # Header file with enums, structs, and function prototypes
├── lora_stm32.c     # Source file: full implementation
├── README.md        # This file
```

---

## 🧱 Configuration Struct

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

Set all LoRa module parameters with this struct using:

```c
Lora_applyConfig(&huartX, &yourConfig);
```

---

## 🔁 Packet Transfer API

### Send Packet

```c
HAL_StatusTypeDef Lora_sendPacket(UART_HandleTypeDef *huart,
                                  uint8_t addh, uint8_t addl, uint8_t chan,
                                  const void *payload, uint16_t payloadSize);
```

Prepends 3-byte header (`ADDH`, `ADDL`, `CHAN`) before sending your `payload`.
---
## 💡 Example Usage

### Define your own payload struct

```c
typedef struct {
    uint8_t id;
    float temperature;
    uint16_t voltage;
} SensorData_t;
```

### Send data

```c
SensorData_t myData = { .id = 1, .temperature = 23.5f, .voltage = 3300 };
Lora_sendPacket(&huart3, 0x00, 0x01, 0x17, &myData, sizeof(myData));
```


### Receive data (UART interrupt)

```c
volatile uint8_t loraRxComplete = 0;
SensorData_t received = {0};

HAL_UART_Receive_IT(&huart6, (uint8_t*)&received, sizeof(received));

void HAL_UART_RxCpltCallback(UART_HandleTypeDef *huart)
{
    Lora_onUartReceiveITComplete();
}

while (1)
{
    if (loraRxComplete)
    {
        loraRxComplete = 0;
        Lora_onUartReceiveIT(&received);
        HAL_UART_Receive_IT(&huart6, (uint8_t*)&received, sizeof(received));
    }
}
```

---


## 🛠 Requirements

- STM32 HAL Library
- UART connected to LoRa module (E32-433T20D)
- LoRa module in correct mode (Programming for config, Normal for use)
- Optional: GPIO control for M0/M1

---

## 📃 License

MIT License — Free to use, modify, and distribute.

---

## ✨ Author

Developed by **Efe BASOL**  
Based on EBYTE official documentation and HAL practice.
