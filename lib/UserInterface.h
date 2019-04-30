//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SMARTCHARGER_UI_H
#define SMARTCHARGER_UI_H

#include <U8g2lib.h>
#include "Language.h"

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"
#include "SmartCharger.h"

#endif
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

#ifndef UI_REFRESH_RATE
#define UI_REFRESH_RATE 300
#endif


class UserInterface {

    String strDsp;

public:
    static uint8_t cursor;

private:

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


    void showAmperage(float amperage) {

        strDsp = String(msg(7));
        strDsp += amperage;

        u8g2.setCursor(2, 16);
        u8g2.print(strDsp);

    }

    void showVoltages(float voltage) {


        strDsp = String(msg(6));
        strDsp += voltage;

        u8g2.setCursor(2, 32);
        u8g2.print(strDsp);
    }


public:

    void begin() {
        u8g2.begin();
        u8g2.setFont(u8g2_font_10x20_tr);
    }


    void draw() {
        u8g2.clearBuffer();
        this->screens();
        u8g2.sendBuffer();
    }


protected:

    void screenWelcome() {

    }


    void screenSelection() {

    }

    void screenCharging() {
//        showAmperage(data.load);
//        showVoltages(data.volt);
    }


    void screens() {
        switch (UserInterface::cursor) {

            default:
            case 0:
                screenWelcome();
                break;

            case 1:
                screenSelection();
                break;

            case 2:
                screenCharging();
                break;

        }
    }
};

uint8_t UserInterface::cursor = 0;

#endif //SMARTCHARGER_UI_H_H
