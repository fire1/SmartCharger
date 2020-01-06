//
// Created by Angel on 2020-01-06.
//

#ifndef SmartCharger_h
#define SmartCharger_h

#include <Arduino.h>

struct uiData {
    float volt;
    float load;
    uint8_t step;
    uint8_t error;
};

const uint8_t pinInpVolt = A2;
const uint8_t pinInpAmps = A3;
const uint8_t pinPwmVolt = 9;
const uint8_t pinEncoderA = 2;
const uint8_t pinEncoderB = 3;
const uint8_t pinEncoderC = 2;
const uint8_t pinTone = 11;

#endif //SMARTCHARGER_SMARTCHARGE_H_H
