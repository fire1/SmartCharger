//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SMARTCHARGER_MENUSTRUCT_H
#define SMARTCHARGER_MENUSTRUCT_H

#include <Arduino.h>
#include "MenuBackend.h"
#include "ButtonsDriver.h"
#include "UserInterface.h"



/**
 * Building the menu
 */
class MenuStructure {

    MenuBackend menu;
    MenuItem menuEntry, menuSelect, menuAbouts, menuTypeLi, menuTypeNi, menuTypeAc, menuTypeOt, menuCharge;


public:
/**
 * Menu constructor
 */
    MenuStructure() : menu(menuUseEvent, menuChangeEvent),//  base menu initialization
                      menuEntry(MenuItem(msg(0), 1)),
                      menuSelect(MenuItem(msg(2), 2)),
                      menuAbouts(MenuItem(msg(3), 3)),
                      menuTypeLi(MenuItem(msg(11), 4)),// li
                      menuTypeNi(MenuItem(msg(12), 5)),// ni
                      menuTypeAc(MenuItem(msg(13), 6)),
                      menuTypeOt(MenuItem(msg(14), 7)),
                      menuCharge(MenuItem(msg(15), 8)) {
    }

    void begin(void) {
        menu.getRoot().add(menuEntry);
        menuEntry.addRight(menuSelect).addRight(menuAbouts);

        menuSelect.addRight(menuTypeLi).addRight(menuTypeNi).addRight(menuTypeAc).addRight(menuTypeOt);
        menuTypeLi.addAfter(menuCharge).addBefore(menuCharge);
        menuTypeNi.addAfter(menuCharge).addBefore(menuCharge);
        menuTypeAc.addAfter(menuCharge).addBefore(menuCharge);
        menuTypeOt.addAfter(menuCharge).addBefore(menuCharge);


        menu.moveDown(); // shift to main menu
    }

    static void menuUseEvent(MenuUseEvent used) {
        UserInterface::cursor = used.item.getShortkey();
        Serial.print(F("Cursor:"));
        Serial.print(UserInterface::cursor, DEC);
        Serial.print(F("Name: "));
        Serial.print(used.item.getName());
        Serial.println();
    }

    static void menuChangeEvent(MenuChangeEvent change) {
        Serial.print(change.from.getName());
        Serial.print(F(" / To "));
        Serial.print(change.to.getShortkey(), DEC);
        Serial.print(F("  "));
        Serial.println(change.to.getName());
    }


    MenuBackend getMB() {
        return menu;
    }


    void moveTo() {
        menu.use();
    }

    void moveRight() {
        menu.moveRight();
    }

    void moveLeft() {
        menu.moveLeft();
    }
};

#endif //SMARTCHARGER_MENUSTRUCT_H
