#include <Arduino.h>
#include <U8g2lib.h>

#define DEBUG


#define VERSION 1

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif

#include "SmartCharger.h"


#define BTN_MAX 1
#define BTN_BOUNCE_TIME 300

#include <Wire.h>
#include "lib/PowerControl.h"
#include "lan/en.h"
#include "lib/Language.h"

#include "lib/ButtonsDriver.h"
#include "lib/MenuStructure.h"
#include "lib/PowerControl.h"
#include "lib/ChargeMode.h"

PowerControl smc;
ButtonsDriver btn;
UserInterface ui;
MenuStructure mn;
const Button btnSet = {pinEncoderC, LOW, 50};

void setup() {
    Serial.begin(9600);

    mn.begin();
    ui.begin();
    smc.begin();
    btn.set(btnSet);
    btn.setEncoder(pinEncoderA, pinEncoderB, 10);
    tone(pinTone, 2000);
    delay(150);
    tone(pinTone, 2400);
    delay(150);
    noTone(pinTone);

    pinMode(pinEncoderC, INPUT_PULLUP);
    digitalWrite(pinEncoderC, HIGH);
}

volatile uint16_t offsetMainLoop;


void loop() {
    btn.listen();

    if (btn.click(btnSet)) {
        mn.doEnter();
        Serial.println(F("Button active"));
    }

    if (btn.isEncoderUp()) {
        mn.moveLeft();
        Serial.println(F("Up"));
    }

    if (btn.isEncoderDw()) {
        mn.goRight();
        Serial.println(F("Dw"));
    }


    if (offsetMainLoop > BTN_BOUNCE_TIME) {
        smc.charge(offsetMainLoop);
        ui.draw(&smc);
        offsetMainLoop = 0;

    }
    smc.measure();
    offsetMainLoop++;
}







