#include "lora.h"

static uint8_t mainParameter[5] = {0};

HAL_StatusTypeDef Lora_applyConfig(UART_HandleTypeDef *huart, LoraConfig_t *config)
{
    mainParameter[0] = config->ADDH;
    mainParameter[1] = config->ADDL;
    mainParameter[2] = config->serialPortMode | config->baudRate | config->airRate;
    mainParameter[3] = config->CHAN;
    mainParameter[4] = config->transmissionMode | config->IODriveMode | config->wakeUpTime | config->FECswitch | config->transmitPower;

    HAL_UART_Transmit(huart, mainParameter, sizeof(mainParameter), HAL_MAX_DELAY);
    HAL_Delay(100);
}
