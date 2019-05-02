//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SMARTCHARGER_UI_H
#define SMARTCHARGER_UI_H

#include <U8g2lib.h>
#include "Language.h"
#include "SmartCharger.h"

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"


#endif
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);


class UserInterface {


public:
    static uint8_t cursor, sector, mode;

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

        String strDsp = String(msg(7));
        strDsp += amperage;

        u8g2.setCursor(60, 32);
        u8g2.print(strDsp);

    }

    void showVoltages(float voltage) {


        String strDsp = String(msg(6));
        strDsp += voltage;

        u8g2.setCursor(2, 32);
        u8g2.print(strDsp);
    }


public:

    void begin() {
        u8g2.begin();
        u8g2.setFont(u8g2_font_10x20_tr);
    }


    void draw(SmartCharger *smartCharger) {

        u8g2.clearBuffer();

        u8g2.setCursor(2, 16);
        u8g2.print(msg(cursor));

        switch (sector) {
            case 0:
                u8g2.setCursor(2, 32);
                u8g2.print(msg(1));
                u8g2.print(VERSION);
                break;

            case 10:
                smartCharger->start();
                showAmperage(smartCharger->getData()->load);
                showVoltages(smartCharger->getData()->volt);
                break;
            case 15:
            case 16:
            case 17:
            case 18:
            case 19:
            case 20:
            case 21:
            case 22:
            case 23:
                smartCharger->setMode(sector - 15);
                break;
        }

        u8g2.sendBuffer();
    }

};

uint8_t UserInterface::cursor = 0;
uint8_t UserInterface::sector = 0;

#endif //SMARTCHARGER_UI_H_H
