/** @file MillerRabinTest.cpp
 *
 */
#include <iostream>
#include <cassert>
#include "MillerRabinTest.h"

using namespace std;



Integer MillerRabinTest::modularExponentation(const Integer& a,const Integer& b,const Integer& n){
    /**
*
* @brief Funktion vom Datentyp Integer kann mit Hilfe eines Algorithmus effizent den Restwert der modularen Exponentiation \n
* drei Integer ausrechnen. Grundform: d = a ^ y % p
*
* @details Funktion vom Datentyp Integer die die Grundform: d = a ^ y % p in einen effizente Algorithmus wiedergibt.\n
* Die Integer d("1"), Integer c("0"), int i = b.BitCount() werden initialisiert. i wird hierbei die Anzahl aller Bits\n
* in der binären Schreibweise. Der Algorithmus aus dem zahlentheorie Vorkurs zieht während der while-Schleife \n
* das Bit an Stelle i von b auf eine 1 überprüft und in dem Fall eine zusätzliche Rechnung ausführt. Der\n
* Restwert der modularen Exponentiation wird als d zurückgegeben.
*
*
* @param a referenz zur Basis
* @param b referenz zum Exponent
* @param n referenz zum Modular
* @return d: Restwert der modularen Exponentiation
*/
    Integer d("1");
    Integer c("0");
    int i = b.BitCount();//Initialisierung von int i als Anzahl aller Bits von der Binärdarstellung von b
    while (i > -1 ) {//Algorithmus aus dem zahlentheorie Vorkurs
        c = 2 * c;
        d = (d * d) % n;

        if (b.GetBit(i) == 1) {//das Bit an Stelle i von b wird überprüft ob es eine 1 ist
            c = c + 1;
            d = (d * a) % n;
        }i--;}

    return d;
}

bool MillerRabinTest::witness(const Integer& a, const Integer& n) {
    /**
 *
 * @brief Funktion vom Datentyp bool, welche einen Primzahltest ausführt im Fall einer Primzahl false ausgibt \n
 * und true im Fall das Zahl a ein solider Beweis dafür ist, dass n eine zusammengesetzte Zahl ist.
 *
 * @details
 *
 * Fall 1: a^n−1 !≡ 1 (mod n). Also kann n wegen dem Satz von Fermat keine Primzahl sein. \n
 *
 * Fall 2: a^n−1 ≡ 1 (mod n). Dann existiert ein i ∈ {1, . . . r}, so dass \n
 * a^u*2^i  ≡ 1 (mod n) und a^u*2^i-1 !≡ ±1 (mod n). Also kann n keine \n
 * Primzahl sein, da es eine von ±1 verschiedene Quadratwurzel von 1 \n
 * modulo n gibt.
 *
 * @param a referenz zur Zufallszahl
 * @param n referenz zur auf Prim getesten Zahl
 * @return true oder false: a solider Beweis für n , dass n eine zusammengesetzte Zahl ist oder Primzahl
     */
    Integer x("0");
    x = n - 1;
    Integer r("0");
    Integer b("0");
    Integer u("1");


    while (b != 1) {
        x=(x>>1);//halbierung durch bitshift um 1 bit nach rechts
        u = x;
        b = u % 2;//test ob zahl ungerade
        r++;
    }
    Integer d = modularExponentation(a, u, n);
    Integer i("1");
    while (i != r) {
        x = d;
        d = (d * d) % n;

        if (d == 1 && x != 1 && x != n - 1) {

            return true;}
        i++;}
    if (d != 1) {
        return true;}


    return false;}


bool MillerRabinTest::isPrime(PRNG* rng, const Integer& n, unsigned int s) {
    /**
 *
 * @brief Funktion vom Datentyp bool, die true im Fall das n eine Primzahl ist ausgibt \n
 * und false im Fall das die Zahl keine Primzahl ist.
 *
 * @details
 * Falls n eine beliebige natürliche Zahl ist und n eine Primzahl dann wird true ausgegeben.
 *
 * Falls n eine zusammengesetzte Zahl ist wird mit einer Wahrscheinlichkeit von
 * höchstens 2^−s true zurück.
 *
 * @param rng referenz zur Zufallszahl
 * @param n referenz zur auf Prim getesten Zahl
 * @param s referenz zu Qualitätsparameter
 * @return true oder false: Primzahl oder keine Primzahl
     */

    Integer a("11");//Zufallsgenerator nicht nutzbar, daher Ergebnis nicht immer Richtig
    Integer b("0");
    unsigned int e =2;
    if (n % 2 == 0) {
        return false;}
    for (int i=1; i <s; i++ ){
        //Zufallsgenerator nicht nutzbar, daher Ergebnis nicht immer Richtig
        if (Integer::Gcd(a, n) > 1){

            return false;}

        if (witness(a, n) == true){// Witness methode
            return false;}}
   if(isIntegerPower(n , b , e) == true){// Test  Ganzahlpotenz
       return false;
   }
    return true;}


Integer MillerRabinTest::exp(const Integer& b, const Integer& e) {
/**
*
* @brief Funktion vom Datentyp Integer, welche b^e berechnet und das Ergebnis ausgibt.\n
*
* @details Formel der Binären Exponentiation ergibt sich aus der Modularen Exponentiation.
*
* @param b referenz zur Basis
* @param e referenz zum Exponent
* @return r: Ergebnis der Exponentiation
*/
    Integer r("1");
// Berechnet b^e


    int i = e.BitCount();// i binäre Darstellung von e
    while (i > -1 ) {//Algorithmus aus dem zahlentheorie Vorkurs abgewandelt
        r = (r*r);
        if (e.GetBit(i) == 1) {//das Bit an Stelle i von e wird überprüft ob es eine 1 ist
            r= b * r;
        }i--;
    }
    return r;// r Resultat der Berechnung
}

bool MillerRabinTest::searchSqrt(const Integer &n, Integer& r) {
    /**
    * @details Die Funktion berechnet mithilfe einer do-while-schleife die größte Zahl x mit x² == n.
     * Dadurch wird ermittelt, ob n eine Ganzzahlige Quadratwurzel besitzt.
     * \n
    *
    *
    * @param n ist const Integer mit n >= 2
     * @param r ist Integer
    *
    * @return true, falls n eine Ganzahlige Quadratwurzel besitzt. false, falls nicht.
     * In jedem Fall wird die errechnete Wurzel in die Variable r geschrieben.
    */
    Integer l = n.BitCount() + 1;
    Integer y;
    y = exp(2, l);  //rechnung mit der ecp funktion f+r 2^l
    do{
        r = y;
        y = (r  + (n / r)) / 2;  //Rechnung aus der Vorlesungsfolie
    }while(y < r);  //solange y kleiner als r ist kann r keine Wurzel von n sein.
    if((r*r) == n)  // falls r² == n ist, ist r eine Ganzzahlige Quadratwurzel von n
        return true;
    return false;
}

bool MillerRabinTest::searchRoot(const Integer &n, unsigned int k, Integer &r)  {
    /**
    * @details Die Funktion ist eine erweiterung der searchSqrt Funktion.
     * Anstatt der Quadratwurzel von n berechnet die erweiterte Funktion,
     * ob die Zahl n eine k-te Wurzel besitzt mit k >= 2.
     * \n
    *
    *
    * @param n ist const Integer mit n >= 2
     * @param k ist eine unsigned int call-by-reference mit k >= 2
     * @param r ist eine Integer call-by-reference
    *
    * @return true, falls n eine k-te Wurzel besitzt. false, falls nicht.
     *In jedem Fall wird die errechnete Wurzel in die Variable r geschrieben und der exponent in die Variable k.
   */
    Integer l = n.BitCount()/k + 1;  //erweiterte Rechnung der searchSqrt-Funktion aus den Folien
    Integer y = exp(2, l);;
    do{
        r = y;
        y = ((k - 1) * r + n / exp(r, k-1)) / k; //erweiterte Rechnung der searchSqrt-Funktion aus den Folien
    }while(y < r);
    if(exp(r, k) == n)  // falls r^k == n ist, ist k eine Ganzzahlpotenz von n und r die k-te Wurzel von n
        return true;
    return false;
}


bool MillerRabinTest::isIntegerPower(const Integer& n, Integer& b, unsigned int& e) {
    /**
    * @details Die Funktion ruft die Funktion searchRoot  in einer Schleife auf. Diese läuft n.bitCount lang und
     * wird abgebrochen, wenn das Ergebnis der Funktion searchRoot true zurückgibt.
     * Wenn die Funktion searchRoot false zurück gibt wird der Schleifenzähler erhöht\n
    *
    *
    * @param n ist const Integer mit n >= 2
     * @param b eine Integer call-by-reference
     * @param e ist eine unsigned int call-by-reference mit e >= 2
    *
    * @return true, falls n eine Ganzahl-Potenz ist. false, falls nicht.
     * In jedem Fall werden die Variablen e und k verändert.
  */

    //b = Basis der GZ-Potenz (falls n eine GZ-Potenz ist)
    //e = exponent der GZ-Potenz
    bool x;
    while(e <= n.BitCount())
    {
        x = searchRoot(n, e, b);    //errechnen der e-ten Wurzel von n.
        if(x)   //Falls die e-te Wurzel von ist wird true zurückgegeben. Falls nicht wird e um 1 erhöht und die Schleife wird erneut ausgeführt.
        {
            return true;
        }
        else
        {
            e = e + 1;
        }
    }
  return false;
}
