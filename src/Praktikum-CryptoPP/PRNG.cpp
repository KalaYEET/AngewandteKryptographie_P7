/** @file PRNG.cpp */
#include "PRNG.h"


byte PRNG::getByte() {
    /*************************************************************************
 * @details Funktion berechnung des nächsten Bytes in Folge.\n
 *
 * @return b ist das nächste Byte in Folge
     *************************************************************************/
     //6d
    byte b = 0;

    for (int i = 0; i < 8; ++i) {
        b = 2 * b + this->getBit();     //Übernommen aus Folie 61 der Vorlesung
    }
    return b;
}

void PRNG::getBlock(byte *buffer, unsigned int n) {
    /*************************************************************************
 * @details Funktion berechnung des nächsten Byteblocks in Folge.\n
 *@param buffer ist Byte Pointer
 * @param n ist unsigned int
     *************************************************************************/
    //6e
    for (int i = 0; i < n; i++) {
        buffer[i] = this->getByte();
    }
}

Integer PRNG::getInteger(unsigned int size) {
    /*************************************************************************
 * @details Funktion berechnet eine Zufallszahl, die eine Größe von size Byte hat. \n
 *
 *@param size ist unsigned int
 * @return prng ist eine Zufallszahl die eine Größe von size Byte hat
  *************************************************************************/
    //6g
    byte temp[size];
    Integer prng(temp, size, prng.UNSIGNED, BIG_ENDIAN_ORDER);
    return prng;
}

Integer PRNG::getInteger(const Integer &m) {
    /*************************************************************************
   * @details Funktion berechnet eine gleichverteilte Zufallszahl aus
   * der Menge {0, 1, . . . , m−1}.\n
   *
   * @param m ist const Integer
   *
   * @return prng ist gleichverteilte Zufallszahl aus der Menge {0, 1, . . . , m−1}
       *************************************************************************/
    //6i
      Integer temp;
      RandomNumberGenerator rng;
      temp.GenerateRandom(rng);
    return temp;
}
