/** @file FortunaGenerator.cpp
 *
 */

#include <iostream>
#include <fstream>
#include "filters.h"
#include "sha.h"
#include "aes.h"
#include "modes.h"
#include "hex.h"
#include "files.h"
#include "FortunaGenerator.h"

using namespace std;

FortunaGenerator::FortunaGenerator() {
	for (int i = 0; i < sizeof(key); i++) {
		key[i] = 0;
	}

	for (int i = 0; i < sizeof(cntr); i++) {
		cntr[i] = 0;
	}
	seeded = false;
	last_reseed=0;
}

bool FortunaGenerator::incCntr() {
    /**
    * @details Die Funktion erhöht den Wert des Counters Cntr um 1.
     * Dies wird durch eine Schleife ermöglicht die die i-te stelle des Counters Cntr um 1 erhöht.
     * Sollte ein Carry stattfinden wird mithilfe einer Abfrage der return übersprungen und die Schleife wird normal fortgeführt.
    *
    *
    *
    * @return true, falls die i-te Stelle von Cntr ungleich 0 ist. false, falls i + 1
     * größer oder gleich 16 ist, also ein überlauf stattfindet..
     *
   */

    for (int i = 0; i < sizeof(cntr); i++) {
        cntr[i] += i;
        if(cntr[i] != 0)
            return true;
        if(i + 1 >= 16)
            return false;
        //Die Zahl an der i-ten Stelle wurd um 1 erhöht. Da die Funktion nur über  Funktion erst true Zurück, sobalsd ein bit auf 1 gesetzt wird.
    }
}

void FortunaGenerator::reseed(byte* seed, unsigned int size) {
    /**
    * @details Die Funktion ist für das reseeden des Fortuna Generators zuständig.
     * Zuerst wird der seed an den key angehängt und danach mittels Sha-256 gehashed.
     * Im Anschluss wird der Counter erhöht.
    *
    *
    * @param seed: ein byte Array, welches den seed enthält
     * @param size: die Größe des seeds, gespeichert in einem unsigned int
    *
    * @return void
   */
    byte skey[sizeof(key) + size];
    for (int i = 0; i < sizeof(key); i++) {
        skey[i] = key[i];
    }
    for (int i = sizeof(key); i < sizeof(key) + size; i++) {
        skey[i] = seed[i-sizeof(key)];
    } //Konkatenation des keys und des seeds.
    SHA256 hash;
    ArraySource(skey, size, true ,new HashFilter(hash,  //dem Filter HashFilter wird zur berechnung der Prüfsumme eine geeignete Hashfunktion übergeben
                                               new ArraySink(skey, sizeof(key) + size)));
    //Hashen der konkatation des keys und des seeds.
    this->incCntr();
}

bool FortunaGenerator::getBit() {
    /**
    * @details Die Funktion liefert das erste bit aus einem zufallsgenerierten Block zurück.
    *
    *
    * @return ein boolean, welcher das erste bit enthält.
   */
    byte bit[1];
    generateBlocks(bit, 1);  //das erste bit des generierten Blocks
    return bit[0];
}

byte FortunaGenerator::getByte() {
    /**
    * @details Die Funktion liefert das erste byte aus einem zufallsgenerierten Block zurück.
    *
    *
    *
    * @return ein byte-Objekt, welches das generierte byte enthält.
   */
    byte bit[8];
    byte b;
    generateBlocks(bit, 8); //die ersten 8 bit des generierten Blocks.
    for (int i = 0; i < 8; i++) {
        b += bit[i];
    }
    return b;
}

void FortunaGenerator::generateBlocks(byte* buffer, unsigned int n) {
    /**
    * @details Die Funktion generiert eine gegebene Menge von Blöcken aus Byte-Folgen.
     * Diese werden mithilfe der Verschlüsselung mittels AES im ECB-Mode erstellt indem der aktuelle Zustand
     * des Cntr verschlüsselt wird. Danach wird Cntr erneut inkrementiert.
    *
    * @param buffer: ein byte Array, welches die generierten Blöcke erhält
     * @param n: die Anzahl der zu generierenden Byte-Blöcke.
    *
    * @return void
  */
    if(cntr == 0)   //falls der PRNG nicht korrekt initialisiert wurde.
    {
        //PRNG wurde nicht korrekt initialisiert
    }
    else
    {
        byte r[16*n];
        for (int i = 0; i < n; i++) {
            ECB_Mode<AES>::Encryption aes_enc;  //Betriebsmodus des Kryptosystems AES auf Entschlüsselung
            aes_enc.SetKey(key, sizeof(key));
            ArraySource(cntr, true,
                        new StreamTransformationFilter( aes_enc,
                                                                new ArraySink(r, 16)));
            //Den cntr mit key verschlüsseln und zurückgeben. Cntr danach inkrementieren.
            incCntr();
            buffer[i] = r[i];

        }
    }
}

void FortunaGenerator::getBlock(byte* buffer, unsigned int n) {
    /**
    * @details Die Funktion ruft die generateBlocks auf.
     * Die ersten n Bytes des generierten Blocks werden im Übergabeparaemeter buffe gespeichert.
    *
    * @param buffer: ein byte Array, welches die ersten n Bytes der generierten Blöcke erhält und
     * @param n: die Anzahl der Bytes, welche in buffer gespeichert werden sollen gegeben als unsigned int
    *
    * @return void
   */
    byte b[n];
    if(n < 0 || n > 1048576)
    {//error inkorrekte länge
    }
    else{
        this->generateBlocks(b, (n>>4)+1);  //implementierung der PseudoRandomData aus der Vorlesung
        for (int i = 0; i < n; i++) {
            buffer[i] = b[i];
        }
        generateBlocks(key, 2);
    }
}

uint32_t FortunaGenerator::getTimeStamp() const {
	struct timeval  tv;

	gettimeofday(&tv,NULL);
	return tv.tv_sec*1000 + tv.tv_usec/1000;
}

