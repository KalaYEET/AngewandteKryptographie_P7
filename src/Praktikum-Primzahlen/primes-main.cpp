/** @file primes-main.cpp */

#include <cassert>
#include <cmath>
#include <iostream>
#include <iomanip>
#include "FortunaGenerator.h"
#include "MillerRabinTest.h"

using namespace std;

void millerRabin() {
    /**
*
* @brief Funktion vom Datentyp void die alle Methoden des MillerRabinTest aufruft.
*/
   cout << "Miller-Rabin Test"
        << "================="
        << endl << endl;


   Integer n("121399589920585397786647347761633");
   Integer a("19");

   Integer p1("249236727971798483921811058804041930204535828339");//p1 und p2 prim
   Integer p2("167376539261987877304745111417636335723391598799");
   Integer np1("207241657224647904979925877995751997643166331621");//np1 und np2 nicht prim
   Integer np2("203681457354349143050092586190992078578082388049");
   unsigned int s = 50;

   Integer b("13");
   Integer ex("57");
   PRNG* rng;

   Integer A3 = MillerRabinTest::witness(a ,n);
   Integer A4_1 = MillerRabinTest::isPrime(rng ,p1 ,s);
   Integer A4_2 = MillerRabinTest::isPrime(rng ,p2 ,s);
   Integer A4_3 = MillerRabinTest::isPrime(rng ,np1 ,s);
   Integer A4_4 = MillerRabinTest::isPrime(rng ,np2 ,s);
   Integer A5 = MillerRabinTest::exp(b ,ex);

   cout << "A3 = "  << A3 << endl << endl
        << "A4_p1 = " << A4_1 << endl
        << "A4_p2 = " << A4_2 << endl
        << "A4_np1 = " << A4_3 << endl
        << "A4_np2 = " << A4_4 << endl << endl

        << "A5 Testwert = 3124432031290254610011894949223517352998211575328796815860858733"<< endl
        << "A5 = " << A5 << endl
        << endl << endl;

   MillerRabinTest MRT;
   Integer r;
   Integer n1 ("11944789308433963188362869029471041566864144");
   Integer n2 ("35834367925301889565088607088413124700592432");
   Integer n3 ("82459222190377411904521629217281504933358750190521");
   Integer n4 ("61374642523762897753653566439246517537628495634413694129");
   cout << "Aufgabe 6" << endl;
   cout << "a-1: " << MRT.searchSqrt(n1, r) << endl;
   cout << "a-2: " << r << endl;
   cout << "b-1: " << MRT.searchSqrt(n2, r) << endl;
   cout << "b-2: " << r << endl;
   cout << "c-1: " << MRT.searchSqrt(n3, r) << endl;
   cout << "c-2: " << r << endl;
   cout << "d-1: " << MRT.searchSqrt(n4, r) << endl;
   cout << "d-2: " << r << endl << endl;
   Integer i1 ("433769751949605918939094356724813641");
   Integer i2 ("5639006775344876946208226637422577333");
   Integer i3 ("70462039047496669316177512730246460325447");
   Integer i4 ("70462039047496669316177512730246460325447");
   Integer i5 ("390625");
   cout << "Aufgabe 7" << endl;
   cout << "a-1: " << MRT.searchRoot(i1, 7, r) << endl;
   cout << "a-2: " << r << endl;
   cout << "b-1: " << MRT.searchRoot(i2, 7, r) << endl;
   cout << "b-2: " << r << endl;
   cout << "c-1: " << MRT.searchRoot(i3, 5, r) << endl;
   cout << "c-2: " << r << endl;
   cout << "d-1: " << MRT.searchRoot(i4, 9, r) << endl;
   cout << "d-2: " << r << endl << endl;
   cout << "Aufgabe 8" << endl;
   unsigned int e = 2;
   Integer j1 ("3124432031290254610011894949223517352998211575328796815860858733");
   cout << "a-1: " << MRT.isIntegerPower(j1, r, e) << endl;
   cout << "a-b: " << r << endl << "a-e: " << e << endl;
   e = 2;
   cout << "a-2: " << MRT.isIntegerPower(n1, r, e) << endl;
   cout << "a-b: " << r << endl << "a-e: " << e << endl;
   e = 2;
   cout << "a-3: " << MRT.isIntegerPower(n2, r, e) << endl;
   cout << "a-b: " << r << endl << "a-e: " << e << endl;
   e = 2;
   cout << "a-4: " << MRT.isIntegerPower(n3, r, e) << endl;
   cout << "a-b: " << r << endl << "a-e: " << e << endl;
   e = 2;
   cout << "a-5: " << MRT.isIntegerPower(n4, r, e) << endl;
   cout << "a-b: " << r << endl << "a-e: " << e << endl;
}

void fortuna() {
    /**
*
* @brief Funktion vom Datentyp void die alle Methoden des FortunaGenerators aufruft.
*/
   cout << "Fortuna PRNG"
        << "============"
        << endl << endl;
   FortunaGenerator fort;
   byte seed [] = "0x7ab2af1a4561abf8";
   fort.reseed(seed, sizeof(seed));
   byte buffer[1000];
   fort.getBlock(buffer, 1000);
   cout << "A2f = " << endl;
   for (int i = 999; i >= 0; i--)
       cout << buffer[i];

   cout << endl;

}

int main() {
    /**
*
* @brief Funktion vom Datentyp int die als Haupteil alles aufruft.
*/
   cout << "Generierung von Primzahlen" << endl
        << "=========================="
        << endl << endl;
   fortuna();
   millerRabin();

   return 0;
}
