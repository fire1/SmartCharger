//
// Created by Angel Zaprianov on 14.2.2017 г..
//

#ifndef BTN_DRIVER_H
#define BTN_DRIVER_H

#include <Arduino.h>

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
    uint8_t pinStateEncoder;
    uint8_t encoderPinA, encoderPinB, encoderPinALast, encoderPosition, encoderPositionLast, encoderSteps = 1;
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

    void encoder() {
        pinStateEncoder = (uint8_t) digitalRead(encoderPinA);
        if ((encoderPinALast == LOW) && (pinStateEncoder == HIGH)) {
            if (digitalRead(encoderPinB) == LOW) {
                encoderPosition = encoderPosition - encoderSteps;
            } else {
                encoderPosition = encoderPosition + encoderSteps;
            }
        }
        encoderPinALast = pinStateEncoder;
    }

    void buttons() {
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

public:

    ButtonsDriver() {
    }

/**
 *
 * @param btn
 */
    void set(Button btn) {
        this->container[btnLen++] = btn;
        pinMode(btn.pin, INPUT);
        digitalWrite(btn.pin, btn.state == HIGH ? LOW : HIGH);
    }

/**
 *
 * @param pinA
 * @param pinB
 * @param step
 */
    void setEncoder(const uint8_t pinA, const uint8_t pinB, const uint8_t step) {
        encoderPinA = pinA;
        encoderPinB = pinB;
        encoderSteps = step;
        pinMode(encoderPinA, INPUT);
        pinMode(encoderPinB, INPUT);
    }

/**
 *
 * @param pinA
 * @param pinB
 */
    void setEncoder(const uint8_t pinA, const uint8_t pinB) {
        encoderPinA = pinA;
        encoderPinB = pinB;
        pinMode(encoderPinA, INPUT);
        pinMode(encoderPinB, INPUT);
    }

/**
 *
 * @return
 */
    boolean click() {
        boolean state = this->isPressed;
        isPressed = false;
        return state;
    }

/**
 *
 * @param btn
 * @return
 */
    boolean click(Button btn) {
        if (this->isPressed) {
            isPressed = false;
            return this->is(btn);
        }
        return false;
    }

/**
 *
 * @param btn
 * @return
 */
    boolean is(Button btn) {
        for (offset = 0; offset < BTN_TOGETHER_MAX; ++offset) {
            if (this->pressed[offset].pin == btn.pin && lastPressed != btn.pin) {
                lastPressed = btn.pin;
                return true;
            }
        }
        return false;
    }

    uint8_t getEncoder() {
        return encoderPosition;
    }
/**
 *
 * @return
 */
    boolean isEncoder() {
        if (encoderPositionLast != encoderPosition) {
            encoderPositionLast = encoderPosition;
            return true;
        }
        return false;
    }


    void listen(void) {
        if (encoderPinA && encoderPinB) {
            this->encoder();
        }
        this->buttons();


    }


};


#endif //ARDUINOMID_BUTTONS_H
