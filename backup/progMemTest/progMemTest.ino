
#include <Arduino.h>

struct chargeMode {
    uint8_t maxTime;
    uint8_t setVolt;
    uint8_t setLoad;
    uint8_t maxVolt;
    uint8_t maxLoad;
    uint8_t pgmName; // index of PROGMEM name
};


const chargeMode chargeModeTable[] PROGMEM = {
        {1, 36, 255, 36, 200, 15},  // lis1
        {1, 36, 255, 36, 200, 16,}, // lis2
        {1, 36, 255, 36, 200, 17,}, // lis3
        {1, 36, 255, 36, 200, 18,}, // lis4
        {1, 36, 255, 36, 200, 19,}, // nis2
        {1, 36, 255, 36, 200, 20,}, // nis4
        {1, 36, 255, 36, 200, 21,}, // nis8
        {1, 36, 255, 36, 200, 22,},
        {1, 36, 255, 36, 200, 23,}, // aci6
};

template <typename T> void PROGMEM_readAnything(const T *sce, T &dest) {
    memcpy_P(&dest, sce, sizeof(T));
}



chargeMode chargeModeBuffer;

chargeMode *loadChargeMode(uint8_t i) {
    PROGMEM_readAnything((chargeMode *) ((&chargeModeTable[i])), chargeModeBuffer);
    return &chargeModeBuffer;
}


void setup() {

    Serial.begin(9600);
}

chargeMode *test;

void loop() {

    test = loadChargeMode(1);
    Serial.print(test->maxTime);
    Serial.print(F(" / "));
    Serial.print(test->setVolt);
    Serial.print(F(" / "));
    Serial.print(test->setLoad);
    Serial.print(F(" / "));
    Serial.print(test->pgmName);
    Serial.println();

    delay(500);
}