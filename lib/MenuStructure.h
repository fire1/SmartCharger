//
// Created by Angel Zaprianov on 2019-04-16.
//

#ifndef SMARTCHARGER_MENUSTRUCT_H
#define SMARTCHARGER_MENUSTRUCT_H

#include <Arduino.h>
#include "MenuBackend.h"
#include "ButtonsDriver.h"
#include "UserInterface.h"

const uint8_t MENU_NAME_1 = 1;
const uint8_t MENU_NAME_11 = 2;
const uint8_t MENU_NAME_12 = 3;

static void menuUseEvent();

static void menuChangeEvent();

/**
 * Building the menu
 */
class MenuStructure {

    MenuBackend menu;
    MenuItem
            mainMenu,
            modeMenu,
            chargeMenu;


public:
/**
 * Menu constructor
 */
    MenuStructure() :
                                       menu(menuUseEvent, menuChangeEvent),//  base menu initialization

            //
            // Main menu
                                       mainMenu(MenuItem(MENU_NAME_1, 1)),
                                       modeMenu(MenuItem(MENU_NAME_11)),
                                       chargeMenu(MenuItem(MENU_NAME_12)) {
    }


    static void menuUseEvent(MenuUseEvent used) {

    }

    static void menuChangeEvent(MenuChangeEvent changed) {

    }

    void begin(void) {
        menu.getRoot().add(mainMenu);

        mainMenu.addRight(modeMenu).addRight(chargeMenu);
        modeMenu.add(mainMenu);
        menu.moveDown();
        UserInterface::cursor = 0;

    }

    MenuBackend getMB() {
        return menu;
    }


    static void menuChanged(MenuChangeEvent change) {
        //
        // Resolve
        MenuItem curMenuItem = change.to; //get the destination menu
        UserInterface::cursor = curMenuItem.getName();
        return;

    }

    void moveUp() {
        menu.moveDown();
        menu.use();

    }

    void moveDw() {
        menu.moveRight();
        menu.use();

    }
};

static void menuUseEvent(MenuUseEvent used) {
    UserInterface::cursor = used.item.getName();
}

#endif //SMARTCHARGER_MENUSTRUCT_H
