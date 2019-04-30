//
// Created by Angel Zaprianov on 2019-04-30.
//

#ifndef SMART_CHARGER_CHARGE_MODE_H
#define SMART_CHARGER_CHARGE_MODE_H

#include <Arduino.h>

struct chargeMode {
    uint8_t maxTime = 0;
    uint8_t setVolt = 0;
    uint8_t setLoad = 0;
    uint8_t maxVolt = 0;
    uint8_t maxLoad = 0;
    uint8_t pgmName = 0; // index of PROGMEM name
};

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
