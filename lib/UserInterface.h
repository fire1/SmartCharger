//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SMARTCHARGER_UI_H
#define SMARTCHARGER_UI_H

#include <U8g2lib.h>

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"

#endif
U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);

#ifndef UI_REFRESH_RATE
#define UI_REFRESH_RATE 300
#endif

class UserInterface {
    uint16_t offset = 0;
private:


public:
    static uint8_t cursor;

    void begin() {
        u8g2.begin();
        u8g2.setFont(u8g2_font_10x20_tr);
    }


    void draw() {
        if (offset > UI_REFRESH_RATE) {
            offset = 0;
        }
        offset++;
    }
};

static uint8_t UserInterface::cursor = 0;

#endif //SMARTCHARGER_UI_H_H
