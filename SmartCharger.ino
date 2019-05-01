#include <Arduino.h>
#include <U8g2lib.h>


#define VERSION 1

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif


#define BTN_MAX 1
#define BTN_BOUNCE_TIME 300

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
Button btnSet = {encoderPinC, LOW, BTN_BOUNCE_TIME + 1};

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


    if (btn.click(btnSet)) {
        mn.getMB().moveDown();
        mn.getMB().use();
        Serial.println("Button active");
    }
    if (btn.click(btnExit)) {
        mn.getMB().toRoot();
        Serial.println("Reset active");
    }

    if (btn.isEncoderUp()) {
        mn.getMB().moveRight();
        mn.getMB().use();
        offset = 301;
        Serial.println("Up");
    }

    if (btn.isEncoderDw()) {
        mn.getMB().moveLeft();
        mn.getMB().use();
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







