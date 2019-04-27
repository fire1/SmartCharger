//
// Created by Angel Zaprianov on 14.2.2017 г..
//

#ifndef ARDUINO_MID_MENU_BTN_H
#define ARDUINO_MID_MENU_BTN_H

#include <Arduino.h>"

//#define BUTTONS_DEBUG

#ifndef BTN_MAX
#define BTN_MAX 9
#endif

#ifndef BTN_TOGETHER_MAX
#define BTN_TOGETHER_MAX 1
#endif


#ifndef BTN_BOUNCE_TIME
#define BTN_BOUNCE_TIME 350
#endif


struct Button {
    uint8_t pin; // Pin to listen
    uint8_t state; // State to listen
    uint16_t time; // Time pressed in m
};

typedef void (*btn_press)(Button);

class ButtonsDriver {
private:
    boolean isPressed;
    volatile uint8_t offset;
    uint8_t btnLen = 0, lastPressed;
    unsigned long *triggerTime;
    unsigned long lastInteraction = 0;
    Button container[BTN_MAX], pressed[BTN_TOGETHER_MAX];

    boolean isPress(uint16_t time, uint8_t index) {
        if (triggerTime[index] == 0) {
            triggerTime[index] = millis();
        }
        unsigned long timer = millis() - triggerTime[index];
        return timer > time ? true : false;

    }


public:

    ButtonsDriver() {
    }

    void set(Button btn) {
        this->container[btnLen++] = btn;
        pinMode(btn.pin, INPUT);
        digitalWrite(btn.pin, btn.state == HIGH ? LOW : HIGH);
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
            if (this->pressed[offset].pin == btn.pin && lastPressed != btn.pin) {
                lastPressed = btn.pin;
                return true;
            }
        }
        return false;
    }


    void listen(void) {
        uint8_t prsOff = 0;
        if (millis() > lastInteraction + BTN_BOUNCE_TIME) {
            lastPressed = '\0';
            lastInteraction = millis();
        }
        for (offset = 0; offset < btnLen; ++offset) {
            this->pressed[offset] = {};
            if (digitalRead(container[offset].pin) == container[offset].state) {
                if (isPress(container[offset].time, prsOff)) {
                    this->isPressed = true;
                    pressed[prsOff] = container[offset];
                    lastInteraction = millis();
                }
                prsOff++;
            }

            //
            // Stops when reach limit
            if (prsOff > BTN_TOGETHER_MAX) {
                return;
            }
        }
    }

    void begin() {

    }


};


#endif //ARDUINOMID_BUTTONS_H
