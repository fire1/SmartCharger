#include <Arduino.h>
#include <U8g2lib.h>


#define VERSION 1

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif



#define BTN_MAX 2
#define BTN_BOUNCE_TIME 200

#include <Wire.h>
#include "lib/SmartCharger.h"
#include "lan/en.h"
#include "lib/Language.h"

#include "lib/ButtonsDriver.h"
#include "lib/MenuStructure.h"

#include "ChargeMode.h"


const uint8_t encoderPinA = 8;
const uint8_t encoderPinB = 7;
const uint8_t encoderPinC = 6;

SmartCharger smc;
ButtonsDriver btn;
UserInterface ui;
MenuStructure mn;
Button btnSet = {encoderPinC, LOW, 200};

Button btnExit = {encoderPinC, LOW, 2000};

void setup() {
    Serial.begin(115200);

    mn.begin();
    ui.begin();
    smc.begin();
    btn.set(btnSet);
    btn.set(btnExit);
    btn.setEncoder(encoderPinA, encoderPinB, 10);
    delay(150);

}

volatile uint16_t offset;

void loop() {
    btn.listen();

    if (Serial.available()) {
        byte read = Serial.read();
        switch (read) {
            case 'w': mn.getMB().moveUp(); break;
            case 's': mn.getMB().moveDown(); break;
            case 'd': mn.getMB().moveRight(); break;
            case 'a': mn.getMB().moveLeft(); break;
            case 'e': mn.getMB().use(); break;
        }
    }

    if (btn.click(btnSet)) {
        mn.goTo();
        Serial.println("Button active");
    }
    if (btn.click(btnExit)) {
        mn.goHome();
        Serial.println("Reset active");
    }

    if (btn.isEncoderUp()) {
        mn.moveLeft();
        offset = 301;
        Serial.println("Up");
    }

    if (btn.isEncoderDw()) {
        mn.goRight();
        offset = 301;
        Serial.println("Dw");
    }


    if (offset > 300) {
        smc.charge(offset);
        ui.draw(smc.getData(), mn.getMB());
        offset = 0;
    }

    offset++;
}







