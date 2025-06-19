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

    HAL_StatusTypeDef result = HAL_UART_Transmit(huart, mainParameter, sizeof(mainParameter), HAL_MAX_DELAY);
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

    HAL_StatusTypeDef result = HAL_UART_Transmit(huart, buffer, totalSize, HAL_MAX_DELAY);
    HAL_Delay(100);
    return result;
}

uint8_t* Lora_receivePacket(UART_HandleTypeDef *huart,
                            uint8_t *addh, uint8_t *addl, uint8_t *chan,
                            uint8_t *externalBuffer, uint16_t payloadSize,
                            uint8_t isFixedMode)
{
    if (isFixedMode)
    {
        uint8_t buffer[256];

        if ((3 + payloadSize) > sizeof(buffer))
            return NULL;

        if (HAL_UART_Receive(huart, buffer, 3 + payloadSize, HAL_MAX_DELAY) != HAL_OK)
            return NULL;

        if (addh) *addh = buffer[0];
        if (addl) *addl = buffer[1];
        if (chan) *chan = buffer[2];

        memcpy(externalBuffer, &buffer[3], payloadSize);
    }
    else
    {
        if (HAL_UART_Receive(huart, externalBuffer, payloadSize, HAL_MAX_DELAY) != HAL_OK)
            return NULL;

        if (addh) *addh = 0;
        if (addl) *addl = 0;
        if (chan) *chan = 0;
    }

    return externalBuffer;
}
