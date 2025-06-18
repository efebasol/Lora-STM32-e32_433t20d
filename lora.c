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

    HAL_UART_Transmit(huart, mainParameter, sizeof(mainParameter), HAL_MAX_DELAY);
    HAL_Delay(100);
}
