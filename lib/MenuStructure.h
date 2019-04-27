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
const uint8_t MENU_NAME_13 = 13;

const uint8_t MENU_NAME_121 = 121;
const uint8_t MENU_NAME_122 = 122;
const uint8_t MENU_NAME_123 = 123;
const uint8_t MENU_NAME_124 = 124;

const uint8_t MENU_NAME_2 = 2;
const uint8_t MENU_NAME_21 = 21;
const uint8_t MENU_NAME_22 = 22;
const uint8_t MENU_NAME_4 = 4;
const uint8_t MENU_NAME_41 = 41;
const uint8_t MENU_NAME_42 = 42;
const uint8_t MENU_NAME_43 = 43;


static void menuUseEvent(MenuUseEvent used);

static void menuChangeEvent(MenuChangeEvent changed);

/**
 * Building the menu
 */
class MenuStructure {

    MenuBackend menu;
    ButtonsDriver *btn;
    MenuItem
    //
    // Main menu
            mainMenu,
            modeMenu,
            setupMenu, ;


public:
/**
 * Menu constructor
 */
    MenuStructure(ButtonsDriver &_b) : btn(&_b), menu(menuUseEvent, menuChangeEvent),//  base menu initialization

            //
            // Main menu
                                      mainMenu(MenuItem(MENU_NAME_1, 1)),
                                      modeMenu(MenuItem(MENU_NAME_11)),
                                      setupMenu(MenuItem(MENU_NAME_12)) {
    }

    void begin(void) {
        menu.getRoot()
                .add(mainMenu);
        ;

        mainMenu.addRight(modeMenu).addRight(setupMenu).addRight(aboutMenu);
        modeMenu.add(mainMenu);


        menu.moveDown();
        UserInterface::cursor = 1;

    }

    MenuBackend getMB() {
        return menu;
    }


    void menuChanged(MenuChangeEvent change) {
        //
        // Check is navigation is active
//        if (btn->getNavigationState() == 0) {
//            return;
//        }

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

#endif //SMARTCHARGER_MENUSTRUCT_H
