#include <Arduino.h>
#include <U8g2lib.h>

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif

#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

const uint8_t pinGroundControl = 3;
const uint8_t pinVoltageControl = 9;
const uint8_t pinAmperage = A0;
//const uint8_t pinAmperage = A1;
const uint8_t pinVoltage = A2;

int val;
const uint8_t encoder0PinA = 8;
const uint8_t encoder0PinB = 7;
uint8_t encoderPos = 0;
int encoder0PinALast = LOW;
int n = LOW;
uint8_t encoderLast = 0;

char displayFloat(float value, char *output) {
    if (value < -99) {
        value = -99;
    }
    int dig1 = int(value) * 10; // 210
    int dig2 = int((value * 10) - dig1);
    dig1 = dig1 / 10;
    if (dig2 < 0) {
        dig2 = dig2 * -1;
    }
    sprintf(output, "%02d.%1d", dig1, dig2);
}

void encoder() {
    n = digitalRead(encoder0PinA);
    if ((encoder0PinALast == LOW) && (n == HIGH)) {
        if (digitalRead(encoder0PinB) == LOW) {
            encoderPos = encoderPos - 15;
        } else {
            encoderPos = encoderPos + 15;
        }
        Serial.print(encoderPos);
        Serial.print("/");
        Serial.println();
    }
    encoder0PinALast = n;
}


void setup() {

//    TCCR2B = TCCR2B & B11111000 | B00000001; // D3 for PWM frequency of 31372.55 Hz
//    TCCR1B = TCCR1B & B11111000 | B00000001; // D9 & D10: set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz
    TCCR1B = TCCR1B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz
    u8g2.begin();
    Serial.begin(9600);
    pinMode(pinVoltageControl, OUTPUT);
    pinMode(pinGroundControl, OUTPUT);

    pinMode(pinAmperage, INPUT_PULLUP);


    pinMode(encoder0PinA, INPUT);
    pinMode(encoder0PinB, INPUT);

//    TCCR1A = _BV(COM1A1) | _BV(WGM11);                // Enable the PWM output OC1A on digital pins 9
//    TCCR1B = _BV(WGM13) | _BV(WGM12) | _BV(CS12);     // Set fast PWM and prescaler of 256 on timer 1
//    ICR1 = 62499;                                     // Set the PWM frequency to 1Hz: 16MHz/(256 * 1Hz) - 1 = 62499
//    OCR1A = 6249;


    u8g2.setFont(u8g2_font_10x20_tr);


    delay(150);
    analogWrite(pinGroundControl, 255);
    digitalWrite(pinAmperage, HIGH);

//



}

uint16_t indexRead = 0, indexShow = 0;
unsigned long readContainerAmp = 0;
unsigned long readContainerVlt = 0;

boolean calibration = false;

struct battery {
    uint8_t vc;
    uint16_t am;
};

battery litIon = {vc: 58};


float showVoltage, showAmprage;


void loop() {
//    if (!calibration && indexRead >100) {
//        Serial.println(F("Calibrating"));
//        delay(150);
//        analogWrite(pinVoltageControl, 255);
//
//        u8g2.setCursor(2, 16);
//        u8g2.print(F("Calibrating ... "));
//        delay(3000);
//        analogWrite(pinGroundControl, 255);
//        analogWrite(pinVoltage, 0);
//        calibration = true;
//    }


    // transfer internal memory to the display
    encoder();
    if (encoderLast != encoderPos) {
        analogWrite(pinVoltageControl, encoderPos);
        encoderLast = encoderPos;
        readContainerVlt = 0;
        readContainerAmp = 0;
        indexRead = 0;
        showAmprage = 0;
        showVoltage = 0;
        indexShow = 0;
    }

    while (Serial.available()) {
        int val = Serial.parseInt(); //read int or parseFloat for ..float...
        if (val > 0) {
            analogWrite(pinVoltageControl, val);
            encoderLast = val;
            encoderPos = val;
            Serial.print(F("Output is "));
            Serial.println(val);
        }
    }

    if (indexRead > 500) {
        uint16_t volt = readContainerVlt / indexRead;
        uint16_t voltage = map(volt, 0, 720, 200, 1600);

        Serial.print(F(" PWM: "));
        Serial.print(encoderPos);

        Serial.print(F(" VRD: "));
        Serial.print(volt);

        Serial.print(F(" VLT: "));
        Serial.print(voltage);

        uint16_t load = (readContainerAmp / indexRead);
        uint16_t amperage = map(load, 70, 250, 700, 1250);

        Serial.print(F("  LDS: "));
        Serial.print(load);

        Serial.print(F("  AMP: "));
        Serial.println(amperage);


        readContainerVlt = volt * 100;
        readContainerAmp = load * 100;
        indexRead = 99;

        showVoltage = voltage * 0.01 + showVoltage;
        showAmprage = amperage * 0.001 + showAmprage;


        String dspVoltage = String(F("V: "));
//        dspVoltage += showVoltage / indexShow;
        dspVoltage += voltage * 0.01;

        String dspAmperage = String(F("A: "));
//        dspAmperage += showAmprage / indexShow;
        dspAmperage += amperage * 0.001;

        u8g2.clearBuffer();                    // clear the internal memory
        u8g2.setCursor(2, 32);
        u8g2.print(dspVoltage);

        u8g2.setCursor(2, 16);
        u8g2.print(dspAmperage);

        u8g2.sendBuffer();
        indexShow++;

        if (indexShow > 10) {
            showVoltage = (showVoltage / indexShow) * 2;
            showAmprage = (showAmprage / indexShow) * 2;
            indexShow = 2;
        }

    }

    readContainerVlt = analogRead(pinVoltage) + readContainerVlt;
    readContainerAmp = analogRead(pinAmperage) + readContainerAmp;

    indexRead++;
    delayMicroseconds(50);
}