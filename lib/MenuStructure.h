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
const uint8_t MENU_NAME_11 = 11;
const uint8_t MENU_NAME_12 = 12;

static void menuUseEvent();
static void menuChangeEvent();
/**
 * Building the menu
 */
class MenuStructure {

    MenuBackend menu;
    ButtonsDriver *btn;
    MenuItem
            mainMenu,
            modeMenu,
            chargeMenu;


public:
/**
 * Menu constructor
 */
    MenuStructure(ButtonsDriver &_b) : btn(&_b),
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
        menu.getRoot()
                .add(mainMenu);

        mainMenu.addRight(modeMenu).addRight(chargeMenu);
        modeMenu.add(mainMenu);


        menu.moveDown();
//        UserInterface::cursor = 1;

    }

    MenuBackend getMB() {
        return menu;
    }


   static  void menuChanged(MenuChangeEvent change) {
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

#endif //SMARTCHARGER_MENUSTRUCT_H
