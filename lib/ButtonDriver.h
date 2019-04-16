//
// Created by Angel Zaprianov on 14.2.2017 г..
//

#ifndef ARDUINO_MID_MENU_BTN_H
#define ARDUINO_MID_MENU_BTN_H

#include <Arduino.h>


//#define BUTTONS_DEBUG

#ifndef BTN_MAX
#define BTN_MAX 9
#endif

#ifndef BTN_TOGETHER_MAX
#define BTN_TOGETHER_MAX 1
#endif


struct Button {
    const uint8_t pin; // Pin to listen
    const uint8_t state; // State to listen
    const uint16_t time; // Time pressed in m
};

typedef void (*btn_press)(Button);

class ButtonDriver {
private:
    boolean isPressed;
    volatile uint8_t offset;
    uint8_t btnLen = 0;
    unsigned long triggerTime[BTN_TOGETHER_MAX];
    Button container[BTN_MAX], pressed[BTN_TOGETHER_MAX];

    boolean isPress(uint16_t time, uint8_t index) {
        if (triggerTime[index] == 0) {
            triggerTime[index] = millis();
        }
        return (millis() - triggerTime[index]) > time ? true : false;

    }


public:

    ButtonDriver() {
    }

    void set(Button btn) {
        this->container[btnLen++] = btn;
    }

    boolean click() {
        boolean state = this->isPressed;
        isPressed = false;
        return state;
    }

    boolean click(Button btn) {
        if (this->isPressed) {
            isPressed = false;
            return this->is(btn);
        }
        return false;
    }

    boolean is(Button btn) {
        for (offset = 0; offset < BTN_TOGETHER_MAX; ++offset) {
            if (this->pressed[offset].pin == btn.pin) {
                return true;
            }
        }
        return false;
    }


    void listen(void) {
        uint8_t timeIndex = 0;
        for (offset = 0; offset < btnLen; ++offset) {
            if (digitalRead(container[offset].pin) == container[offset].state) {
                if (isPress(container[offset].time, timeIndex++)) {
                    this->isPressed = true;
                    pressed[timeIndex] = container[offset];
                }
            }

            //
            // Stops when reach limit
            if (timeIndex > BTN_TOGETHER_MAX) {
                return;
            }
        }
    }

    void begin() {

    }


};


#endif //ARDUINOMID_BUTTONS_H
