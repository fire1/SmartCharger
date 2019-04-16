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


struct ChargeMode {
    uint8_t time = 0;
    uint8_t voltage;
    uint8_t mode = 0;
};

class SmartCharger {


public:

    void SmartCharger() {

    }

};

#endif //SmartCharger_h
