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
                      menuEntry(MenuItem("SmartCharger")),
                      menuSelect(MenuItem("Select Type")),
                      menuAbouts(MenuItem("About")),
                      menuTypeLi(MenuItem("Li-Ion")),// li
                      menuTypeNi(MenuItem("Ni-Mh")),// ni
                      menuTypeAc(MenuItem("Acid")),
                      menuTypeOt(MenuItem("Other")),
                      menuCharge(MenuItem("Charging")) {
    }

    void begin(void) {
        menu.getRoot().add(menuEntry);
        menuEntry.addRight(menuSelect).addRight(menuAbouts);
        menuAbouts.addRight(menuEntry);

        menuSelect.addRight(menuTypeLi).addRight(menuTypeNi).addRight(menuTypeAc).addRight(menuTypeOt);
        menuTypeOt.addRight(menuSelect);
        menuTypeLi.add(menuCharge).add(menuCharge);
        menuTypeNi.add(menuCharge).add(menuCharge);
        menuTypeAc.add(menuCharge).add(menuCharge);
        menuTypeOt.add(menuCharge).add(menuCharge);

        menu.moveDown();
        menu.use();

    }

    static void menuUseEvent(MenuUseEvent used) {
        Serial.print(F("Menu use "));
        Serial.println(used.item.getName());
        if (used.item == "Delay") //comparison agains a known item
        {
            Serial.println(F("menuUseEvent found Delay (D)"));
        }
    }

    static void menuChangeEvent(MenuChangeEvent changed) {
        Serial.print(F("Menu change "));
        Serial.print(changed.from.getName());
        Serial.print(" ");
        Serial.println(changed.to.getName());



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
