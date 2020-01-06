//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SMARTCHARGER_UI_H
#define SMARTCHARGER_UI_H

#include <U8g2lib.h>
#include "Language.h"
#include "PowerControl.h"

#ifndef _U8G2LIB_HH

#include "../libraries/U8g2/src/U8g2lib.h"


#endif
/*const uint8_t u8g2_font_battery19_tn[167] U8G2_FONT_SECTION("u8g2_font_battery19_tn") =
        "\10\0\3\3\4\5\1\1\5\10\23\0\0\23\0\23\0\0\0\0\0\0\212\60\13\70\317\42\35\304\372\377"
                "\371 \61\17\70\317\42\35\304\372\177\241H(\342\203\0\62\23\70\317\42\35\304\372/\24\11E,\241H"
                "(\342\203\0\63\27\70\317\42\35\304\372\205\42\241\210%\24\11E,\241H(\342\203\0\64\33\70\317\42"
                "\35\304\272P$\24\261\204\42\241\210%\24\11E,\241H(\342\203\0\65\37\70\317\42\35\304\22\212\204"
                "\42\226P$\24\261\204\42\241\210%\24\11E,\241H(\342\203\0\66\5\0\316\0\67\5\0\316\0\0"
                "\0\0\4\377\377\0";*/

//U8G2_SSD1306_128X32_UNIVISION_F_HW_I2C u8g2(U8G2_R0);
U8G2_SSD1306_128X32_UNIVISION_2_HW_I2C u8g2(U8G2_R2);


const uint8_t lcdRow1 = 14;
const uint8_t lcdRow2 = 28;
const uint8_t *defFont = u8g2_font_crox3h_tf;

class UserInterface {
    char char_3[4];


public:
    static uint8_t cursor, sector, mode;

private:

/**
 * Converts float to lower decimal
 * @param value
 * @param output
 * @return
 */
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



/**
 * Shows voltages on screen
 * @param voltage
 */
    void showVoltages(float voltage) {
        displayFloat(voltage, char_3);
        u8g2.setCursor(2, lcdRow1);
        u8g2.print(msg(6));
        u8g2.print(char_3);
    }

/**
 * Shows amperage on screen
 * @param amperage
 */
    void showAmperage(float amperage) {

        displayFloat(amperage, char_3);
        u8g2.setCursor(2, lcdRow2);
        u8g2.print(msg(7));
        u8g2.print(char_3);

    }

    void showBattery(){
        u8g2.setFont(u8g2_font_battery19_tn);
        u8g2.setCursor(94, 26);
        u8g2.print(0);
        u8g2.setFont(defFont);
    }
/**
 * Shows title from this->cursor on screen
 */
    void showTitle() {
        u8g2.setCursor(2, lcdRow1);
        u8g2.print(msg(cursor));
    }

public:

    void begin() {
        u8g2.begin();
        u8g2.setFont(defFont);
    }

/**
 * Draws UI on screen
 * @param smartCharger
 */
    void draw(PowerControl *smartCharger) {

        u8g2.clearBuffer();
        u8g2.firstPage();
        do {
            ui(smartCharger);
        } while (u8g2.nextPage());
    }

protected:
    void ui(PowerControl *smartCharger) {
        switch (sector) {
            default:
            case 0:

                u8g2.drawFrame(0, 0, u8g2.getDisplayWidth(), u8g2.getDisplayHeight());
                this->showTitle();

                if (cursor == 0) {
                    u8g2.setCursor(2, lcdRow2);
                    u8g2.print(msg(1));
                    u8g2.print(VERSION);
                }
                break;

            case 10:
                smartCharger->start();

                showAmperage(smartCharger->getData()->load);
                showVoltages(smartCharger->getData()->volt);
                showBattery();

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
                this->showTitle();
                smartCharger->setMode(sector - 15);
                break;
        }
    }

};

uint8_t UserInterface::cursor = 0;
uint8_t UserInterface::sector = 0;

#endif //SMARTCHARGER_UI_H_H
