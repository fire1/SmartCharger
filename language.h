//
// Created by Admin on 4/27/2019.
//

#ifndef SMART_CHARGER_LANGUAGE_H
#define SMART_CHARGER_LANGUAGE_H

#include <Arduino.h>

const char *const LcdMsgTable[] PROGMEM = {
        msg0, msg1, msg2, msg3, msg4, msg5, msg6, msg7, msg8, msg9, msg10, msg11, msg12, msg13, msg14, msg15,
        msg16, msg17, msg18, msg19, msg20, msg21, msg22, msg23, msg24, msg25, msg26, msg27, msg28, msg29, msg30,
        msg31, msg32, msg33, msg34, msg35, msg36, msg37, msg38, msg39, msg40, msg41, msg42, msg43, msg44, msg45,
        msg46, msg47, msg48, msg49, msg50, msg51, msg52, msg53, msg54, msg55, msg56, msg57, msg58, msg59, msg60,
        msg61, msg62, msg63, msg64, msg65, msg66, msg67, msg68, msg69, msg70, msg71, msg72, msg73, msg74, msg75,
        msg76, msg77, msg78, msg79, msg80, msg81, msg82, msg83, msg84, msg85, msg86, msg87, msg88, msg89, msg90,
        msg91, msg92, msg93, msg94, msg95, msg96, msg97, msg98, msg99, msg100, msg101, msg102, msg103, msg104,
        msg105, msg106, msg107, msg108, msg109, msg110, msg111, msg112, msg113, msg114, msg115,
        msg116, msg117, msg118, msg119, msg120, msg121, msg122, msg123, msg124
};

const char *msg(uint8_t i) {
    strcpy_P(messageBuffer, (char *) pgm_read_word(&(LcdMsgTable[i])));
    return messageBuffer;
}


#endif //SMARTCHARGER_LANGUAGE_H