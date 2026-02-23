#pragma once 
#include "IORegister_types.h"

// Codes for remote inputs
const uint8_t REMOTE_CODE_0 = 22; 
const uint8_t REMOTE_CODE_1 = 12;
const uint8_t REMOTE_CODE_2 = 24;
const uint8_t REMOTE_CODE_3 = 94;
const uint8_t REMOTE_CODE_4 = 8;
const uint8_t REMOTE_CODE_5 = 28;
const uint8_t REMOTE_CODE_6 = 90;
const uint8_t REMOTE_CODE_7 = 66;
const uint8_t REMOTE_CODE_8 = 82;
const uint8_t REMOTE_CODE_9 = 74;
const uint8_t REMOTE_CODE_VOL_UP = 82;
const uint8_t REMOTE_CODE_VOL_DOWN = 21;
const uint8_t REMOTE_CODE_PLAY_PAUSE = 64;
const uint8_t REMOTE_CODE_POWER = 69;

#ifdef __cplusplus
extern "C" {
#endif 

uint16_t waitForLevel(uint8_t level);
uint32_t decodeRemoteCode();

#ifdef __cplusplus
} // extern "C"
#endif 
