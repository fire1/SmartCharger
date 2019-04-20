#include <Arduino.h>


#include "../libraries/U8g2/src/U8g2lib.h"

#endif

#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

const uint8_t pinGroundControl = 3;
const uint8_t pinVoltageControl = 9;
const uint8_t pinVoltageLoad = A0;

int val;
const uint8_t encoder0PinA = 8;
const uint8_t encoder0PinB = 7;
uint8_t encoder0Pos = 0;
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
            encoder0Pos--;
        } else {
            encoder0Pos++;
        }
        Serial.print(encoder0Pos);
        Serial.print("/");
        Serial.println();
    }
    encoder0PinALast = n;
}


void setup() {

    TCCR2B = TCCR2B & B11111000 | B00000001; // D3 for PWM frequency of 31372.55 Hz
    TCCR1B = TCCR1B & B11111000 | B00000001; // D9 & D10: set timer 1 divisor to 1 for PWM frequency of 31372.55 Hz

    u8g2.begin();
    Serial.begin(9600);
    pinMode(pinVoltageControl, OUTPUT);
    pinMode(pinGroundControl, OUTPUT);
    pinMode(pinVoltageLoad, INPUT);

    pinMode(encoder0PinA, INPUT);
    pinMode(encoder0PinB, INPUT);

    u8g2.setFont(u8g2_font_10x20_tr);
    analogWrite(pinGroundControl, 255);


}

uint16_t index = 0;
unsigned long readContainer = 0;


void loop() {

    // transfer internal memory to the display
    encoder();
    if (encoderLast != encoder0Pos) {
        analogWrite(pinVoltageControl, encoder0Pos);
        encoderLast = encoder0Pos;
    }

    while (Serial.available()) {
        int val = Serial.parseInt(); //read int or parseFloat for ..float...
        if (val > 0) {
            analogWrite(pinVoltageControl, val);
            encoderLast = val;
            Serial.print(F("Output is "));
            Serial.println(val);
        }
    }

    if (index > 330) {

        uint16_t voltageOffset = analogRead(A2);
        uint8_t voltage = map(voltageOffset, 0, 1024, 1, 200);
        uint8_t load = (readContainer / index);
        Serial.print(F(" V: "));
        Serial.print(voltage);
        uint16_t amperage = map(load, 110, 1, 200, 18);
        Serial.print(F("  A: "));
        Serial.println(amperage);

        readContainer = 0;
        index = 0;

        String dspVoltage = String(F("V: "));
        dspVoltage += voltage * 0.1;

        String dspAmperage = String(F("A: "));
        dspAmperage += amperage;

        u8g2.clearBuffer();                    // clear the internal memory
        u8g2.setCursor(2, 32);
        u8g2.print(dspVoltage);

        u8g2.setCursor(2, 16);
        u8g2.print(dspAmperage);

        u8g2.sendBuffer();
    }

    readContainer = analogRead(pinVoltageLoad) + readContainer;

    index++;
}