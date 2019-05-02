//
// Created by Angel Zaprianov on 2019-05-02.
//

#ifndef SMARTCHARGER_PRG_MEM_H
#define SMARTCHARGER_PRG_MEM_H

#include <Arduino.h>

template <typename T> void PROGMEM_readAnything (const T * sce, T& dest)
{
    memcpy_P (&dest, sce, sizeof (T));
}

template <typename T> T PROGMEM_getAnything (const T * sce)
{
    static T temp;
    memcpy_P (&temp, sce, sizeof (T));
    return temp;
}
#endif //SMARTCHARGER_PRGMEM_H
