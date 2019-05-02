#include <Arduino.h>
#include <U8g2lib.h>


#define VERSION 1

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif


#define BTN_MAX 1
#define BTN_BOUNCE_TIME 450

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
const Button btnSet = {encoderPinC, LOW, 50};

void setup() {
    Serial.begin(115200);

    mn.begin();
    ui.begin();
    smc.begin();
    btn.set(btnSet);
    btn.setEncoder(encoderPinA, encoderPinB, 10);
    delay(150);
    pinMode(encoderPinC, INPUT_PULLUP);
    digitalWrite(encoderPinC, HIGH);
}

volatile uint16_t offset;

void loop() {

    btn.listen();



    if (btn.click(btnSet)) {
        mn.doEnter();
        Serial.println(F("Button active"));
    }

    if (btn.isEncoderUp()) {
        mn.moveLeft();
        offset = 301;
        Serial.println(F("Up"));
    }

    if (btn.isEncoderDw()) {
        mn.goRight();
        offset = 301;
        Serial.println(F("Dw"));
    }


    if (offset > 300) {
        smc.charge(offset);
        ui.draw(&smc);
        offset = 0;
    }

    offset++;
}







