#include <Arduino.h>


#include "../libraries/U8g2/src/U8g2lib.h"

#endif

#include <Wire.h>

U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);


const uint8_t pinVoltageControl = 3;
const uint8_t pinVoltageLoad = A0;

void setup() {
    u8g2.begin();
    Serial.begin(115200);
    pinMode(pinVoltageControl, OUTPUT);
    pinMode(pinVoltageLoad, INPUT);
    u8g2.setFont(u8g2_font_10x20_tr);

}

uint8_t index = 0;
unsigned long readContainer = 0;
uint8_t voltageOffset = 0;

void loop() {
    // transfer internal memory to the display


    while (Serial.available()) {
        int val = Serial.parseInt(); //read int or parseFloat for ..float...
        if (val > 0) {
            voltageOffset = val;
            analogWrite(pinVoltageControl, val);
            Serial.print(F("Output is "));
            Serial.println(val);
        }
    }

    if (index > 250) {
        uint8_t voltage = map(voltageOffset, 1, 255, 2, 13);
        uint8_t load = (readContainer / index);
        Serial.print(F(" Read: "));
        Serial.print(load);
        uint16_t amperage = map(load, 110, 1, 200, 18);
        Serial.print(F("  Amp: "));
        Serial.println(amperage);

        readContainer = 0;
        index = 0;

        String dspVoltage = String(F("V: "));
        dspVoltage += voltage;

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