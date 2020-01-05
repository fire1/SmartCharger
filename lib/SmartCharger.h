//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SmartCharger_h
#define SmartCharger_h

#include <Arduino.h>

#include "../ChargeMode.h"

#ifndef PIN_INP_AMP
#define  PIN_INP_AMP A0
#endif
#ifndef PIN_INP_VLT
#define PIN_INP_VLT A1
#endif

#ifndef PIN_PSV_PWM
#define PIN_PSV_PWM 9
#endif

#ifndef PIN_GND_PWM
#define  PIN_GND_PWM 10
#endif

#define PIN_VOLT A2
#define PIN_LOAD A0


struct uiData {
    float volt;
    float load;
    uint8_t step;
    uint8_t error;
};


class SmartCharger {
private:
    boolean started = false;
    const uint8_t readsPinsNum = 4;
    volatile uint8_t offsetFor = 0;
    uint16_t inVolt, inLoad;
    uint8_t setVolt, setLoad;
    unsigned long readContainerVlt, readContainerAmp;
    unsigned long vltInputRead = 0, ampInputRead = 0;
    uiData *data;
    chargeMode *mode;

/**
 *
 */
    void timers() {
        TCCR2B = TCCR2B & B11111000 | B00000001; // D3 for PWM frequency of 31372.55 Hz
//    TCCR1B = TCCR1B & B11111000 | B00000001; // D9 & D10: set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz
//    TCCR1B = TCCR1B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz
        TCCR2B = TCCR2B & B11111000 | B00000011; // for PWM frequency of 980.39 Hz
//    TCCR2B = TCCR2B & B11111000 | B00000100; // for PWM frequency of 490.20 Hz (The DEFAULT)
//    TCCR2B = TCCR2B & B11111000 | B00000101; // for PWM frequency of 245.10 Hz
//    TCCR2B = TCCR2B & B11111000 | B00000110; // for PWM frequency of 122.55 Hz
//    TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz
    }


    void control() {
        if (mode && started || true) {
//            double gap;
//            gap = abs(VoltPoint - VoltInput);
//
//            if (gap < 10) {
//                piv.SetTunings(consKp, consKi, consKd);
//            } else {
//                piv.SetTunings(aggKp, aggKi, aggKd);
//            }
//
//            gap = abs(LoadPoint - LoadInput);
//            if (gap < 10) {
//                pil.SetTunings(consKp, consKi, consKd);
//            } else {
//                pil.SetTunings(aggKp, aggKi, aggKd);
//            }

            if (mode->maxVolt < inVolt) {

            }
            if (mode->maxLoad < inLoad) {

            }

//            data->step++;




            analogWrite(PIN_PSV_PWM, setVolt);
            analogWrite(PIN_GND_PWM, 255);
        }
    }


public:

    SmartCharger() {

    }

    // Start charging
    void start() {
        if (mode) {
            started = true;
            setVolt = mode->setVolt;
            setLoad = mode->setLoad;
        }
    }


    void begin() {
        timers();
        pinMode(PIN_PSV_PWM, OUTPUT);
        pinMode(PIN_GND_PWM, OUTPUT);

        pinMode(PIN_LOAD, INPUT_PULLUP);
        pinMode(PIN_VOLT, INPUT_PULLUP);

        digitalWrite(PIN_LOAD, HIGH);
    }

/**
 *
 * @param mode
 */
    void setMode(uint8_t mode) {
        this->mode = loadChargeMode(1);

    }


    void charge(uint16_t readCount) {
        inVolt = uint16_t(this->readContainerVlt / readCount);
        uint16_t voltage = (uint16_t) map(inVolt, 225, 1094, 320, 1440);

        inLoad = uint16_t(this->readContainerAmp / readCount);
        uint16_t amperage = (uint16_t) map(inLoad, 70, 250, 700, 1250);
        this->readContainerVlt = 0;
        this->readContainerAmp = 0;

        data->volt = voltage * 0.01;
        data->load = amperage * 0.001;


#ifdef DEBUG

        Serial.print(F(" i: "));
        Serial.print(readCount);
        Serial.print(F(" / V rd: "));
        Serial.print(inVolt);
        Serial.print(F(" V: "));
        Serial.print(data->volt);
        Serial.print(F(" PWM: "));
        Serial.print(setVolt);
        Serial.print(F(" /  A rd: "));
        Serial.print(inLoad);
        Serial.print(F("  A: "));
        Serial.print(data->load);
        Serial.print(F(" PWM: "));
        Serial.print(setLoad);
        Serial.println();

#endif

        control();

    }

    void measure() {

        if (Serial.available()) {
            int val = Serial.parseInt(); //read int or parseFloat for ..float...
            if (val > 0) {
                setVolt = uint8_t(val);
                setLoad = 255;
                Serial.print(F("VoltOutput is "));
                Serial.println(val);
            }
        }

        vltInputRead = 0, ampInputRead = 0;
        for (offsetFor = 0; offsetFor < readsPinsNum; ++offsetFor) {
            vltInputRead += analogRead(PIN_VOLT);
            ampInputRead += analogRead(PIN_LOAD);
        }

        this->readContainerVlt = vltInputRead / (readsPinsNum - 1) + this->readContainerVlt;
        this->readContainerAmp = ampInputRead / (readsPinsNum - 1) + this->readContainerAmp;
    }

    uiData *getData() {
        return data;
    }


};

#endif //SmartCharger_h
