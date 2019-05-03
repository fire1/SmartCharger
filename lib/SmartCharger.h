//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SmartCharger_h
#define SmartCharger_h

#include <Arduino.h>
#include <PID_v1.h>

#ifndef PID_v1_h

#include "../../libraries/PID/PID_v1.h"

#endif

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

//Define Variables we'll be connecting to
double VoltPoint, VoltInput, VoltOutput,
        LoadInput, LoadOutput, LoadPoint;
//Define the aggressive and conservative Tuning Parameters
double aggKp = 4, aggKi = 0.2, aggKd = 1;
double consKp = 1, consKi = 0.05, consKd = 0.25;
PID piv(&VoltInput, &VoltOutput, &VoltPoint, consKp, consKi, consKd, DIRECT);
PID pil(&LoadInput, &LoadOutput, &LoadPoint, consKp, consKi, consKd, DIRECT);


struct uiData {
    float volt;
    float load;
    uint8_t step;
    uint8_t error;
};


class SmartCharger {
private:
    boolean started = false;
    volatile uint8_t offsetFor = 0;
    uint16_t volt, load;
    unsigned long readContainerVlt, readContainerAmp;
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


    void measure() {

        const uint8_t reads = 4;
        unsigned long vlt = 0, amp = 0;
        for (offsetFor = 0; offsetFor < reads; ++offsetFor) {
            vlt += analogRead(PIN_VOLT);
            amp += analogRead(PIN_LOAD);
        }

        readContainerVlt = vlt / (reads - 1) + readContainerVlt;
        readContainerAmp = amp / (reads - 1) + readContainerAmp;
    }


    void calculate(uint16_t offset) {

        uint16_t volt = uint16_t(readContainerVlt / offset);
        uint16_t voltage = (uint16_t) map(volt, 3, 720, 260, 1600);

        uint16_t load = uint16_t(readContainerAmp / offset);
        uint16_t amperage = (uint16_t) map(load, 70, 250, 700, 1250);
//
        VoltInput = volt;
        LoadInput = load;

#ifdef DEBUG
        Serial.print(F(" VRD: "));
        Serial.print(volt);

        Serial.print(F(" VLT: "));
        Serial.print(voltage);

        Serial.print(F("  LDS: "));
        Serial.print(load);

        Serial.print(F("  AMP: "));
        Serial.println(amperage);
#endif

        data->volt = voltage * 0.01;
        data->load = amperage * 0.001;

    }


    void control() {
        if (mode && started) {
            double gap;
            gap = abs(VoltPoint - VoltInput);

            if (gap < 10) {
                piv.SetTunings(consKp, consKi, consKd);
            } else {
                piv.SetTunings(aggKp, aggKi, aggKd);
            }

            gap = abs(LoadPoint - LoadInput);
            if (gap < 10) {
                pil.SetTunings(consKp, consKi, consKd);
            } else {
                pil.SetTunings(aggKp, aggKi, aggKd);
            }

            if (mode->maxVolt < volt) {

            }
            if (mode->maxLoad < load) {

            }

            data->step++;

            piv.Compute();
            analogWrite(PIN_PSV_PWM, VoltOutput);


            pil.Compute();
            analogWrite(PIN_GND_PWM, LoadOutput);
        }
    }

public:

    SmartCharger() {

    }

    // Start charging
    void start() {
        if (mode) {
            started = true;
            VoltPoint = mode->setVolt;
            LoadPoint = mode->setLoad;
        }
    }


    void begin() {
        timers();
        pinMode(PIN_PSV_PWM, OUTPUT);
        pinMode(PIN_GND_PWM, OUTPUT);

        pinMode(PIN_LOAD, INPUT_PULLUP);
        pinMode(PIN_VOLT, INPUT_PULLUP);

        digitalWrite(PIN_LOAD, HIGH);

        piv.SetMode(AUTOMATIC);
        piv.SetSampleTime(300);

        pil.SetMode(AUTOMATIC);
        pil.SetSampleTime(300);
    }

/**
 *
 * @param mode
 */
    void setMode(uint8_t mode) {
        this->mode = loadChargeMode(1);
#ifdef DEBUG
        Serial.print(F("Mode: "));
        Serial.print(mode);
        Serial.print(F(" mT:"));
        Serial.print(this->mode->maxTime);
        Serial.print(F(" sV:"));
        Serial.print(this->mode->setVolt);
        Serial.print(F(" sA:"));
        Serial.print(this->mode->setLoad);
        Serial.print(F(" mV:"));
        Serial.print(this->mode->maxVolt);
        Serial.print(F(" mA:"));
        Serial.print(this->mode->maxLoad);
        Serial.print(F(" Nm:"));
        Serial.print(this->mode->pgmName);
        Serial.println();
        delay(300);
#endif

    }


    void charge(uint16_t offset) {
        calculate(offset);
        control();
        measure();
    }

    uiData *getData() {
        return data;
    }


};

#endif //SmartCharger_h
