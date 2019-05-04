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
    MenuItem menuEntry, menuSelect, menuAbouts, menuTypeLi, menuTypeNi, menuTypeAc, menuTypeOt, menuCharge,
            lis1, lis2, lis3, lis4, nis2, nis4, nis8, aci6;


public:
/**
 * Menu constructor
 */
    MenuStructure() : menu(menuUseEvent, menuChangeEvent),//  base menu initialization
                      menuEntry(MenuItem(0)),
                      menuSelect(MenuItem(2)),
                      menuAbouts(MenuItem(3)),
                      menuTypeLi(MenuItem(11)),// li
                      menuTypeNi(MenuItem(12)),// ni
                      menuTypeAc(MenuItem(13)),
                      menuTypeOt(MenuItem(14)),
                      menuCharge(MenuItem(10)),

                      lis1(MenuItem(15)),
                      lis2(MenuItem(16)),
                      lis3(MenuItem(17)),
                      lis4(MenuItem(18)),
                      nis2(MenuItem(19)),
                      nis4(MenuItem(20)),
                      nis8(MenuItem(21)),
                      aci6(MenuItem(23)) {
    }

    void begin(void) {
        menu.getRoot().add(menuEntry);
        menuEntry.add(menuSelect);
        menuSelect.addRight(menuAbouts);
        menuAbouts.addRight(menuSelect);


        menuSelect.add(menuTypeLi);
        menuTypeLi.addRight(menuTypeNi).addRight(menuTypeAc)/*.addRight(menuTypeOt)*/.addRight(menuTypeLi);


        menuTypeLi.add(lis1);
        lis1.addRight(lis2).addRight(lis3).addRight(lis4).addRight(lis1);
        lis1.add(menuCharge).add(menuSelect);
        lis2.add(menuCharge).add(menuSelect);
        lis3.add(menuCharge).add(menuSelect);
        lis4.add(menuCharge).add(menuSelect);


        menuTypeNi.add(nis2);
        nis2.addRight(nis4).addRight(nis8).addRight(nis2);
        nis2.add(menuCharge).add(menuSelect);
        nis4.add(menuCharge).add(menuSelect);
        nis8.add(menuCharge).add(menuSelect);

        menuTypeAc.add(aci6).add(menuCharge).add(menuSelect);

//        menuTypeOt.add(menuCharge);

        menu.moveDown();
        menu.use();

    }

    static void menuUseEvent(MenuUseEvent used) {

        uint8_t cursor = used.item.getName();
        Serial.print(F("Sector: "));
        Serial.println(cursor);

        UserInterface::sector = cursor;
    }

    static void menuChangeEvent(MenuChangeEvent changed) {
        Serial.print(F("Change: "));
//        Serial.print(msg(changed.from.getName()));
//        Serial.print(" ");
        Serial.println(msg(changed.to.getName()));
        UserInterface::cursor = changed.to.getName();


    }


    MenuBackend getMB() {
        return menu;
    }


    void doEnter() {
        menu.moveDown();
        menu.use();
    }

    void goHome() {
        menu.getRoot().moveDown();
        menu.use();
    }


    void moveLeft() {
        menu.moveLeft();
    }

    void goRight() {
        menu.moveRight();
    }
};

#endif //SMARTCHARGER_MENUSTRUCT_H
