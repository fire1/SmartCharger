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
};


const chargeMode Lis1 PROGMEM = {1, 36, 255, 36, 200, 15,};
const chargeMode lis2 PROGMEM = {1, 36, 255, 36, 200, 16,};
const chargeMode lis3 PROGMEM = {1, 36, 255, 36, 200, 17,};
const chargeMode lis4 PROGMEM = {1, 36, 255, 36, 200, 18,};
const chargeMode nis2 PROGMEM = {1, 36, 255, 36, 200, 19,};
const chargeMode nis4 PROGMEM = {1, 36, 255, 36, 200, 20,};
const chargeMode nis8 PROGMEM = {1, 36, 255, 36, 200, 21,};
const chargeMode aci6 PROGMEM = {1, 36, 255, 36, 200, 23,};


const uint8_t chargeModeLen = 8;

const chargeMode modeTable[] PROGMEM = {
        // LiIon
        Lis1, lis2, lis3, lis4,
        // NiMH
        nis2, nis4, nis8,
        // Acid
        aci6


};

chargeMode thisModeItem;
chargeMode *getMode(uint8_t i) {
    PROGMEM_readAnything(&modeTable[i], thisModeItem);
    return &thisModeItem;
}


/*

 //    strcpy_P(&_buffMode, (char *) pgm_read_word(&(modeTable[i])));
//    memcpy_P(&_buffMode, (char *) pgm_read_word(&(modeTable[i])));

 * */

/*uint8_t *__bufMode = new uint8_t[lenMode];

uint8_t *getMode(bt_mode *mode) {
    memcpy_P(__bufMode, mode, lenMode);
    return __bufMode;
}*/

//bt_mode *msg(uint8_t i) {
//    memccpy_P(__bufMode,(uint8_t *) pgm_read_word(&(modeTable[i])));
////    strcpy_P(__bufMode, (uint8_t *) pgm_read_byte(&(modeTable[i])));
//    return __bufMode;
//}



//const struct  chargeMode ch_mode  PROGMEM = {maxTime:1, setVolt:36, setLoad: 255, maxVolt: 36, maxLoad:  200, pgmName: 15};


//chargeMode ch_mode[];



//= {maxTime:1, setVolt:36, setLoad: 255, maxVolt: 36, maxLoad:  200, pgmName: 0};
//
//// Li Ion
//        {maxTime:1, setVolt:36, setLoad: 255, maxVolt: 36, maxLoad:  200, pgmName: 15}, // 1s 4.2V
//        {maxTime:1, setVolt:36, setLoad: 255, maxVolt: 36, maxLoad:  200, pgmName: 15},
//
////        {0, 72,  255, 72,  200, 16}, // 2s 8.4V
////        {0, 36,  255, 36,  200, 17}, // 3s 12.6V
////        {0, 255, 255, 252, 200, 18}, // 4s 14.8V
////
////// NiMH
////        {0, 2,   255, 2,   200, 15}, // 1s 4.2V
////        {0, 72,  255, 36,  200, 16}, // 2s 8.4V
////        {0, 36,  255, 36,  200, 17}, // 3s 12.6V
////
////// Acid
////        {0, 245, 255, 2,   200, 15} // 6s 12.6V
//} ;
//*/

#endif //SMARTCHARGER_CHARGEMODE_H
