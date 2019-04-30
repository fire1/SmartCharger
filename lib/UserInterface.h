//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SMARTCHARGER_UI_H
#define SMARTCHARGER_UI_H

#include <U8g2lib.h>
#include "lib/Language.h"

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"
#include "SmartCharger.h"

#endif
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

#ifndef UI_REFRESH_RATE
#define UI_REFRESH_RATE 300
#endif


class UserInterface {

    volatile uint16_t offsetDraw = 0;
    String strDsp;

private:


    void showAmperage(float amperage) {

        strDsp = String(msg(7));
        strDsp += amperage;

        u8g2.setCursor(2, 16);
        u8g2.print(strDsp);

    }

    void showVoltage(float voltage) {


        strDsp = String(msg(6));
        strDsp += voltage;

        u8g2.setCursor(2, 32);
        u8g2.print(strDsp);
    }


public:
    static uint8_t cursor;

    void begin() {
        u8g2.begin();
        u8g2.setFont(u8g2_font_10x20_tr);
    }


    void draw(uiData data) {

        if (offsetDraw > UI_REFRESH_RATE) {
            u8g2.clearBuffer();
            showAmperage(data.a);
            showVoltage(data.v);

            offsetDraw = 0;
            u8g2.sendBuffer();
        }

        offsetDraw++;
    }
};

static uint8_t UserInterface::cursor = 0;

#endif //SMARTCHARGER_UI_H_H
