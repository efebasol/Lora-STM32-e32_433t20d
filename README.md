# 📡 EBYTE E32-433T20D LoRa Configuration Library for STM32

A lightweight and modular C library for configuring and communicating with the **EBYTE E32-433T20D LoRa module** using STM32 HAL-based UART.  
The library provides:

- Full runtime configuration of the module.
- Send/receive any **user-defined struct** with optional addressing support.
- Flexible **Fixed/Transparent Mode** communication.

---

## 🚀 Features

- ✅ Fully configurable via `LoraConfig_t`
- 📤 Supports sending any `struct` as payload
- 📥 Flexible receive function with address header handling
- 🧩 Easily integratable with STM32CubeMX HAL projects
- ⚙️ Fixed Mode or Transparent Mode support
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

### Receive Packet

```c
uint8_t* Lora_receivePacket(UART_HandleTypeDef *huart,
                            uint8_t *addh, uint8_t *addl, uint8_t *chan,
                            uint8_t *externalBuffer, uint16_t payloadSize,
                            uint8_t isFixedMode);
```

- In **Fixed Mode**: reads 3-byte header + payload, fills `addh`, `addl`, `chan`.
- In **Transparent Mode**: only receives `payload`, sets `addh`, `addl`, `chan` to 0.

Returns pointer to payload buffer (`externalBuffer`) or `NULL` on error.

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

### Receive data

```c
SensorData_t received;
uint8_t srcAddh, srcAddl, srcChan;

uint8_t *result = Lora_receivePacket(&huart3, &srcAddh, &srcAddl, &srcChan,
                                     (uint8_t*)&received, sizeof(received), 1);
if (result != NULL) {
    // Process received
}
```

---

## 🧰 Mode Tips

| Mode           | Header Used | Use Case                    |
|----------------|-------------|-----------------------------|
| Transparent    | ❌ No        | Simple peer-to-peer         |
| Fixed          | ✅ Yes       | Broadcast or multi-node     |

Set using:

```c
.transmissionMode = transmissionMode_Transparent // or transmissionMode_Fixed
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