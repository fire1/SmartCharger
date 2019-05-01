//
// Created by Admin on 4/27/2019.
//

#ifndef SMART_CHARGER_LANGUAGE_H
#define SMART_CHARGER_LANGUAGE_H

#ifdef LAN_H
#include "../lan/en.h"
#endif


#include <Arduino.h>

char messageBuffer[24];
const char *const LcdMsgTable[] PROGMEM = {
        msg0, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8, msg9, msg10,
        msg11, msg12, msg13, msg14, msg15, msg16, msg17, msg18, msg19, msg20,
        msg21, msg22, msg23

};

const char *msg(uint8_t i) {
    strcpy_P(messageBuffer, (char *) pgm_read_word(&(LcdMsgTable[i])));
    return messageBuffer;
}


#endif //SMARTCHARGER_LANGUAGE_H
