#include <Arduino.h>
#include <U8g2lib.h>

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif


#include <Wire.h>
#define BTN_MAX 1
#include "lib/ButtonsDriver.h"

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

const uint8_t pinGroundControl = 3;
const uint8_t pinVoltageControl = 9;
const uint8_t pinAmperage = A0;
//const uint8_t pinAmperage = A1;
const uint8_t pinVoltages = A2;

int val;
const uint8_t encoderPinA = 8;
const uint8_t encoderPinB = 7;
const uint8_t encoderPinC = 6;
uint8_t encoderPos = 0;
int encoderPinALast = LOW;
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

static void encoder();

static void timers();

ButtonsDriver btn;
Button btnSet = {encoderPinC, LOW, 50};

void setup() {
    timers();

    u8g2.begin();
    Serial.begin(115200);
    pinMode(pinVoltageControl, OUTPUT);
    pinMode(pinGroundControl, OUTPUT);

    pinMode(pinAmperage, INPUT_PULLUP);

    pinMode(pinVoltages, INPUT_PULLUP);
    pinMode(encoderPinA, INPUT);
    pinMode(encoderPinB, INPUT);
    pinMode(encoderPinC, INPUT);


    u8g2.setFont(u8g2_font_10x20_tr);
    btn.begin();
    btn.set(btnSet);

    delay(150);
    analogWrite(pinGroundControl, 255);
    digitalWrite(pinAmperage, HIGH);
}

uint16_t indexRead = 0, indexShow = 0;
unsigned long readContainerAmp = 0;
unsigned long readContainerVlt = 0;
float showVoltage, showAmperage;
volatile uint8_t ms = 0;


void loop() {
    btn.listen();


    if (btn.click(btnSet)) {
        Serial.println("Button active");
    }
    // transfer internal memory to the display
    encoder();
    if (encoderLast != encoderPos) {
        analogWrite(pinVoltageControl, encoderPos);
        encoderLast = encoderPos;
        readContainerVlt = readContainerVlt / (indexRead - 1);
        readContainerAmp = readContainerAmp / (indexRead - 1);
        indexRead = 2;
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

    if (indexRead > 300) {
        uint16_t volt = readContainerVlt / indexRead;
        uint16_t voltage = map(volt, 3, 720, 260, 1600);
//        float voltage = (volt * 22.0 / 1023.0);

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
        showAmperage = amperage * 0.001 + showAmperage;


        String dspVoltage = String(F("V: "));
//        dspVoltage += showVoltage / indexShow;
        dspVoltage += voltage * 0.01;

        String dspAmperage = String(F("A: "));
//        dspAmperage += showAmperage / indexShow;
        dspAmperage += amperage * 0.001;

        u8g2.clearBuffer();                    // clear the internal memory
        u8g2.setCursor(2, 32);
        u8g2.print(dspVoltage);

        u8g2.setCursor(2, 16);
        u8g2.print(dspAmperage);

        u8g2.sendBuffer();
        indexShow++;

        if (indexShow > 10) {
            showVoltage = (showVoltage / (indexShow - 1)) * 2;
            showAmperage = (showAmperage / (indexShow - 1)) * 2;
            indexShow = 2;
        }

    }


//    float mean = float(datasum / BUFFER);
//    for (int n = 0; n < BUFFER; n++) {
//        diffsum += ((data[n] - mean) * (data[n] - mean));
//    }
//    float sd = sqrt(diffsum / (BUFFER - 1));

    const uint8_t reads = 4;
    unsigned long vlt = 0, amp = 0;
    for (ms = 0; ms < reads; ++ms) {
        vlt += analogRead(pinVoltages);
        amp += analogRead(pinAmperage);
    }

//    Serial.print(analogRead(pinVoltages));
//    Serial.print(" ");

    readContainerVlt = vlt / (reads - 1) + readContainerVlt;
    readContainerAmp = amp / (reads - 1) + readContainerAmp;

    indexRead++;
}


void encoder() {
    n = digitalRead(encoderPinA);
    if ((encoderPinALast == LOW) && (n == HIGH)) {
        if (digitalRead(encoderPinB) == LOW) {
            encoderPos = encoderPos - 15;
        } else {
            encoderPos = encoderPos + 15;
        }
        Serial.print(encoderPos);
        Serial.print("/");
        Serial.println();
    }
    encoderPinALast = n;
}

void timers() {
    TCCR2B = TCCR2B & B11111000 | B00000001; // D3 for PWM frequency of 31372.55 Hz
//    TCCR1B = TCCR1B & B11111000 | B00000001; // D9 & D10: set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz
//    TCCR1B = TCCR1B & B11111000 | B00000010; // for PWM frequency of 3921.16 Hz
    TCCR2B = TCCR2B & B11111000 | B00000011; // for PWM frequency of 980.39 Hz
//    TCCR2B = TCCR2B & B11111000 | B00000100; // for PWM frequency of 490.20 Hz (The DEFAULT)
//    TCCR2B = TCCR2B & B11111000 | B00000101; // for PWM frequency of 245.10 Hz
//    TCCR2B = TCCR2B & B11111000 | B00000110; // for PWM frequency of 122.55 Hz
//    TCCR2B = TCCR2B & B11111000 | B00000111; // for PWM frequency of 30.64 Hz
}