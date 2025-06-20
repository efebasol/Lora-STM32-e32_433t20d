#include "lora.h"

static uint8_t mainParameter[6] = {0};

HAL_StatusTypeDef Lora_applyConfig(UART_HandleTypeDef *huart, LoraConfig_t *config)
{
    mainParameter[0] = 0xC0;
    mainParameter[1] = config->ADDH;
    mainParameter[2] = config->ADDL;
    mainParameter[3] = config->serialPortMode | config->baudRate | config->airRate;
    mainParameter[4] = config->CHAN;
    mainParameter[5] = config->transmissionMode | config->IODriveMode | config->wakeUpTime | config->FECswitch | config->transmitPower;

    HAL_StatusTypeDef result = HAL_UART_Transmit(huart, mainParameter, sizeof(mainParameter), 100);
    HAL_Delay(100);
    return result;
}

HAL_StatusTypeDef Lora_sendPacket(UART_HandleTypeDef *huart, uint8_t addh, uint8_t addl, uint8_t chan, const void *payload, uint16_t payloadSize)
{
    uint16_t totalSize = 3 + payloadSize;
    uint8_t buffer[256]; // max size
    if (totalSize > sizeof(buffer))
        return HAL_ERROR;

    buffer[0] = addh;
    buffer[1] = addl;
    buffer[2] = chan;

    memcpy(&buffer[3], payload, payloadSize);

    HAL_StatusTypeDef result = HAL_UART_Transmit(huart, buffer, totalSize, 100);
    HAL_Delay(100);
    return result;
}

void Lora_onUartReceiveITComplete(void)
{
    loraRxComplete = 1;
}

void Lora_onUartReceiveIT(SensorData_t *data)
{
    // Örnek işlem: sıcaklık belli aralıkta mı?
    if (data->temperature > 30.0f)
    {
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_SET); // LED2 yak
    }
    else
    {
        HAL_GPIO_WritePin(LD2_GPIO_Port, LD2_Pin, GPIO_PIN_RESET);
    }

    // Debug için UART'tan veri yazdırmak da mümkündür
    // Örn: sprintf() ile huart3 üzerinden değer yazdırılabilir
}