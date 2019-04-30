//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SmartCharger_h
#define SmartCharger_h

#include <Arduino.h>


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
    volatile uint8_t offsetFor = 0;
    unsigned long readContainerVlt, readContainerAmp;
    uiData data;
    chargeMode mode;


public:

    void SmartCharger() {

    }

    void begin() {
        pinMode(PIN_PSV_PWM, OUTPUT);
        pinMode(PIN_GND_PWM, OUTPUT);

        pinMode(PIN_LOAD, INPUT_PULLUP);
        pinMode(PIN_VOLT, INPUT_PULLUP);
    }

/**
 *
 * @param mode
 */
    void setMode(chargeMode mode) {
        this->mode = mode;
    }


    void calculate(uint16_t offset) {

        uint16_t volt = uint16_t(readContainerVlt / offset);
        uint16_t voltage = (uint16_t) map(volt, 3, 720, 260, 1600);

        uint16_t load = uint16_t(readContainerAmp / offset);
        uint16_t amperage = (uint16_t) map(load, 70, 250, 700, 1250);



        //  debug info
        Serial.print(F(" VRD: "));
        Serial.print(volt);

        Serial.print(F(" VLT: "));
        Serial.print(voltage);

        Serial.print(F("  LDS: "));
        Serial.print(load);

        Serial.print(F("  AMP: "));
        Serial.println(amperage);

        data = {voltage * 0.01, amperage * 0.001, 0};
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

};

#endif //SmartCharger_h
