/** @file BlumBlumShubGenerator.cpp */

#include "BlumBlumShubGenerator.h"

BlumBlumShubGenerator::BlumBlumShubGenerator(const Integer &n, const Integer &seed) {
    /*************************************************************************
 * @details Funktion zur Initialisierung des BlumBlumShub Generators.\n
 * @param n
 * @param seed
 *
     *************************************************************************/
    this->n = n;
    this->s = (seed * seed) % n;
}

bool BlumBlumShubGenerator::getBit() {
/*************************************************************************
 * @details Funktion berechnung des nächsten Bits in Folge.\n
 *
 * @return  Restwert der modularen Rechnung von s ist boolean
     *************************************************************************/
    //6b
    //PRNG::getByte();
    this->s = (this->s * this->s) % this->n;
    return this->s % 2;
}