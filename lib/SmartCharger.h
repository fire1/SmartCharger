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

typedef void (*charging)(chargeMode);


class SmartCharger {
private:
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



        //  debug info
//        Serial.print(F(" VRD: "));
//        Serial.print(volt);
//
//        Serial.print(F(" VLT: "));
//        Serial.print(voltage);
//
//        Serial.print(F("  LDS: "));
//        Serial.print(load);
//
//        Serial.print(F("  AMP: "));
//        Serial.println(amperage);

        data->volt = voltage * 0.01;
        data->load = amperage * 0.001;

    }


    void control() {
        if (mode) {
            if (mode->maxVolt < volt) {

            }

            if (mode->maxLoad < load) {

            }

            data->step++;
        }
    }

public:

    SmartCharger() {

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

    }

    void start(){

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
