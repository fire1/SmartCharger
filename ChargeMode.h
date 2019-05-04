//
// Created by Angel Zaprianov on 2019-04-30.
//

#ifndef SMART_CHARGER_CHARGE_MODE_H
#define SMART_CHARGER_CHARGE_MODE_H

#include <Arduino.h>
#include "lib/ProgramMem.h"

struct chargeMode {
    uint8_t maxTime;
    uint8_t setVolt;
    uint8_t setLoad;
    uint8_t maxVolt;
    uint8_t maxLoad;
    uint8_t pgmName; // index of PROGMEM name
    uint16_t uiV[4];
    uint16_t uiA[4];
};

//
// Configuration table for charging modes
const chargeMode chargeModeTable[] PROGMEM = {
        {1, 50, 255, 50, 200, 15, {402, 438, 370, 422}, {70, 250, 700, 1250},},  // lis1
        {1, 36, 255, 36, 200, 16, {225, 1094, 320, 1440}, {70, 250, 700, 1250}}, // lis2
        {1, 36, 255, 36, 200, 17,}, // lis3
        {1, 36, 255, 36, 200, 18,}, // lis4
        {1, 36, 255, 36, 200, 19,}, // nis2
        {1, 36, 255, 36, 200, 20,}, // nis4
        {1, 36, 255, 36, 200, 21,}, // nis8
        {1, 36, 255, 36, 200, 22,},
        {1, 36, 255, 36, 200, 23,}, // aci6
};


chargeMode chargeModeBuffer;

/**
 *  Load charge mode form flash memory
 * @param index
 * @return
 */
chargeMode *loadChargeMode(uint8_t index) {
    PROGMEM_readAnything((chargeMode *) ((&chargeModeTable[index])), chargeModeBuffer);
    return &chargeModeBuffer;
}


#endif //SMARTCHARGER_CHARGEMODE_H
