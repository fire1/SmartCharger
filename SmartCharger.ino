#include <Arduino.h>
#include <U8g2lib.h>

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif


#define BTN_MAX 1

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

void setup() {
    Serial.begin(115200);

    ui.begin();
    smc.begin();
    btn.set(btnSet);
    btn.setEncoder(encoderPinA, encoderPinB, 10);
    delay(150);

}

volatile uint16_t offset;

void loop() {
    btn.listen();


    if (btn.click(btnSet)) {
        Serial.println("Button active");
    }

    if (btn.isEncoderUp()) {
        mn.moveUp();
        offset = 301;
    }

    if (btn.isEncoderDw()) {
        mn.moveDw();
        offset = 301;
    }


    if (offset > 300) {
        smc.charge(offset);
        ui.draw(smc.getData());
        offset = 0;
    }

    offset++;
}







