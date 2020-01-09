//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef PowerControl_h
#define PowerControl_h

#include <Arduino.h>
#include "ChargeMode.h"
#include "../SmartCharger.h"

class PowerControl {
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
        // Pin 9/10 timer setup
        TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
    }


    void control() {
        if (mode && started || true) {


            if (mode->maxVolt < inVolt) {

            }
            if (mode->maxLoad < inLoad) {

            }

//            data->step++;




            analogWrite(pinPwmVolt, setVolt);
        }
    }


public:

    PowerControl() {

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
        // Pin 9/10 timer setup
        TCCR1B = TCCR1B & B11111000 | B00000010;    // set timer 1 divisor to     8 for PWM frequency of  3921.16 Hz
        pinMode(pinPwmVolt, OUTPUT);
        pinMode(pinInpAmps, INPUT_PULLUP);
        pinMode(pinInpVolt, INPUT_PULLUP);

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
        uint16_t voltage = (uint16_t) map(inVolt, 0, 1024, 0, 20000);

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
            vltInputRead += analogRead(pinInpVolt);
            ampInputRead += analogRead(pinInpAmps);
        }

        this->readContainerVlt = vltInputRead / (readsPinsNum - 1) + this->readContainerVlt;
        this->readContainerAmp = ampInputRead / (readsPinsNum - 1) + this->readContainerAmp;
    }

    uiData *getData() {
        return data;
    }


};

#endif //SmartCharger_h
