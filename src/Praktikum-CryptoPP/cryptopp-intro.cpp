/** @file cryptopp-intro.cpp */

#include <cassert>
#include <iostream>
#include <string>
#include "filters.h" // StringSink
#include "hex.h" // HexEncoder
#include "sha.h"
#include "aes.h"
#include "modes.h"
#include "base64.h"
#include "files.h" // FileSink
#include "osrng.h" // BlockingRNG
#include "integer.h" // Integer
#include "nbtheory.h" // RabinMillerTest
#include "BlumBlumShubGenerator.h"

using namespace std;
using namespace CryptoPP;

void DataFlowExercise() {
/**
 *
 * @brief Funktion vom Datentyp void die mit Hilfe des Hex- und Base64-Encoders und Decoders Strings ver- und entschlüsselt.
 *
 * @details Funktion vom Datentyp void die Anfangs zwei Konsolenausgaben betätigt um bessere lesbarkeit der \n
 * Konsole zu erreichen. Es werden zwei Strings initialisiert src = "Kryptographie macht Spaß!!!" und dst.\n
 * Es wird eine neue Senke mit dem Parameter dst mit einem HexEncoder deklariert. \n
 * Der Inhalt des Strings wird als Quelle genutzt und hexadezimal verschlüsselt in der Senke dst abgelegt.\n
 * Anschließend wird dst in der Konsole ausgegeben.
 *
 * Nach dem selben Prinzip wird mit einem HexDecoder der \n
 * string hex = "4963682062696E2065696E20537472696E6720696E204865786164657A696D616C6B6F64696572756E6721",
 * entschlüsselt und in string dst2 geschrieben und ausgegeben.
 *
 * Nach dem selben Prinzip wird mit einem Base64Decoder die Datei "base64data.txt" entschlüsselt und\n
 * in string dst3 geschrieben und ausgegeben.
 *
 * Das Ziel der Übung ist das Verständnis des Quellen und Senken Prinzips. \n
 */
    cout << endl//Konsolenausgaben
         << "Data Flow Exercise:" << endl
         << "===================" << endl << endl;
    //2a
    string src = "Kryptographie macht Spaß!!!";//string src wird initialisiert
    string dst;//string dst wird initialisiert
    StringSink* sink = new StringSink(dst);//Neue Senke mit dem Parameter dst
    HexEncoder* encoder = new HexEncoder(sink);//Hexadezimal verschlüssler deklariert
    StringSource(src, true, encoder);  //Der Inhalt des Strings src wird Hexadezimal verschlüsselt
    cout << dst << endl;//Konsolenausgabe: 4B727970746F67726170686965206D6163687420537061C39F212121
    //2b
    string hex = "4963682062696E2065696E20537472696E6720696E204865786164657A696D616C6B6F64696572756E6721";
    string dst2;
    StringSink* hsink = new StringSink(dst2); //Ein neuer String und eine neue StringSink für die Dekodierung
    HexDecoder* decoder = new HexDecoder(hsink);  //deklarieren eines HexDecoders
    StringSource(hex, true, decoder);  //Dekodieren der gegeben Hexsequenz
    cout << dst2 << endl; //Konsolenausgabe: Ich bin ein String in Hexadezimalkodierung!

    //2c
    string dst3;
    StringSink* fsink = new StringSink(dst3);//Neue Senke mit dem Parameter dst3
    Base64Decoder* Bdecoder = new Base64Decoder(fsink);//Base64 entschlüssler deklariert
    FileSource("./data/base64data.txt",
               true, Bdecoder);//Dekodieren der gegeben base64data.txt
    cout << dst3 << endl;//Konsolenausgabe: Base64 ist ein Begriff aus dem Computerbereich und beschreibt ein Verfahren zur Kodierung von 8-Bit-Binärdaten (z. B. ausführbare Programme, ZIP-Dateien) in eine Zeichenfolge, die nur aus lesbaren Codepage-unabhängigen ASCII-Zeichen besteht. Im Zusammenhang mit OpenPGP wird noch eine Prüfsumme (CRC-24) angehängt; dieses leicht modifizierte Verfahren trägt den Namen Radix-64.

}

void EncryptionExercise() {
/**
 * @brief Funktion vom Datentyp void die mit Hilfe des Advanced Encryption Standard einen Stringkey dazu \n
 * Nutzt um einen String mit Hilfe des HexEncoders zu verschlüsseln und ihn danach auszugeben.\n
 * Folgend den Verschlüsselten String wieder mit Hilfe des HexDecoders zu entschlüsseln und ihn \n
 * danach auszugeben. Zusätzlich wird eine Datei "aescipher.txt" mit Hilfe des Base64 Decoders \n
 * entschlüsselt und in einem String gespeichert und ausgegeben.
 *
 * @details Funktion vom Datentyp void die Anfangs zwei Konsolenausgaben betätigt um bessere lesbarkeit der\n
 * Konsole zu erreichen. Der try catch block enthält ein byte key[16] und den string encoded_key = "08a8cbfe7a3d1262c8abc3d1197dfefe"\n
 * und der string encodekey wird durch Hexadezimalentschlüsselung in ein 16 byte langes Byte array geschrieben.\n
 * Die zwei Strings plain_text = "Streng geheime Botschaft" ,string cipher_text werden initialisiert.\n
 * Der Betriebsmodus des Kryptosystems AES wird auf Verschlüsselung geschalten und der key wird gesetzt.\n
 * Durch den StreamTransformationFilter wird der String auf die richtige Länge gekürzt und danach Hexadezimal\n
 * verschlüsselt in cipher_text geschrieben und in der Konsole ausgegeben.
 *
 * Der Betriebsmodus des Kryptosystems AES wird folgend auf Entschlüsselung geschalten und der key wird gesetzt.\n
 * Der string decrypt wird initialisiert und anschließend wird cipher_text Hexadezimal entschlüsselt und in decrypt\n
 * geschrieben und dann ausgegeben.
 *
 * Der Betriebsmodus des Kryptosystems AES wird folgend auf Countermode Entschlüsselung geschalten und der key wird gesetzt.\n
 * Der string cdecrypt, string enckey = "47656865696D65725363686CC3BC7373", string IV = "496E697469616C6973696572756E6773" und\n
 * byte ek[16] werden initialisiert. Der string enckey wird durch Hexadezimalentschlüsselung in ein 16 byte langes Byte array geschrieben.\n
 * Der Initialisierungsvektor IV wird genau wie der key durch Hexadezimalentschlüsselung in ein 16 byte langes Byte array geschrieben.\n
 * Die Datei "aescipher.txt" wird daraufhin mit dem Base64Decoder entschlüsselt und in cdecrypt geschrieben und in der Konsole ausgegeben.
 *
 *
 *
 */
    cout << endl//Konsolenausgaben
         << "Encryption Exercise:" << endl
         << "====================" << endl
         << endl;
    //3a
    try {
        byte key[16];
        string encoded_key = "08a8cbfe7a3d1262c8abc3d1197dfefe";
        StringSource(encoded_key, true,
                     new HexDecoder(new ArraySink(key,
                                                  16)));//string encodekey wird durch Hexadezimalentschlüsselung in ein 16 byte langes Byte array geschrieben

        string plain_text = "Streng geheime Botschaft";
        string cipher_text;
        ECB_Mode<AES>::Encryption aes_enc;//Betriebsmodus des Kryptosystems AES auf Verschlüsselung
        aes_enc.SetKey(key, sizeof(key));//setzen des Schlüssels

        StringSource(plain_text, true,
                     new StreamTransformationFilter(aes_enc,//filter aes_enc ,StreamTransformationFilter passt die Länge des Datenstroms an
                                                    new HexEncoder(//Hexadezimal verschlüsseler deklariert
                                                            new StringSink(cipher_text))));
        cout << cipher_text << endl;//Konsolenausgabe: 109F89B21CEC5BD71567099DF09E6265FC3566FD895328E196FD7743BE83C72B

        //3b
        ECB_Mode<AES>::Decryption aes_dec;//Betriebsmodus des Kryptosystems AES auf Entschlüsselung
        string decrypt;
        aes_dec.SetKey(key, sizeof(key));//setzen des Schlüssels

        StringSource(cipher_text, true, new HexDecoder(//Hexadezimal entschlüsseler deklariert
                new StreamTransformationFilter(aes_dec,//filter aes_dec ,StreamTransformationFilter passt die Länge des Datenstroms an
                                               new StringSink(decrypt)
                )));
        cout << decrypt << endl;//Konsolenausgabe: Streng geheime Botschaft

        //3c
        CTR_Mode<AES>::Decryption ctr_dec;//Betriebsmodus des Kryptosystems AES auf Entschlüsselung
        string cdecrypt;
        string enckey = "47656865696D65725363686CC3BC7373";
        byte ek[16];

        StringSource(enckey, true,
                     new HexDecoder(new ArraySink(ek, 16)));

        string IV = "496E697469616C6973696572756E6773";
        byte iv[16];
        StringSource(IV, true,
                     new HexDecoder(new ArraySink(iv, 16)));
        ctr_dec.SetKeyWithIV(ek, sizeof(ek), iv);

        FileSource("./data/aescipher.txt", true,
                   new Base64Decoder(
                           new StreamTransformationFilter(ctr_dec,
                                                          new StringSink(cdecrypt))));
        cout << cdecrypt << endl;//Konsolenausgabe: Hallo Studis. Ich bin eine Botschaft, die man unbedingt geheimhalten muss. Also schön auf mich aufpassen! :-)


    } catch (const Exception& e){//Abfangen einer Exception, falls ein Fehler auftritt
        cerr << e.what() << endl;//Ausgabe einer Exception
        assert(false);
    }
}


void HashExercise() {
    /**
    *
    * @brief Funktion vom Datentyp void die Mithilfe des SHA256 Algorithmus aus einem String eine Prüfsumme generiert \n
    * und sie ausgibt. Die Berechnung der Prüfsumme erfolgt mit dem Hashfilter nachdem eine geeignete \n
    * Hashfunktion übergeben wird. Diese Prüfsumme wird im Anschluss auf Richtigkeit geprüft.
    *
    *
    * @details Funktion vom Datentyp void die Anfangs zwei Konsolenausgaben betätigt um bessere lesbarkeit der\n
    * Konsole zu erreichen. Zwei Strings message = "Kryptographie macht immer noch Spaß!!!" , digest und der\n
    * SHA256 hash werden initialisiert. Mithilfe von HashVerificationFilter::HASH_AT_BEGIN kann angegeben werden,\n
    * dass die Prüfsumme vor der Nachricht kommt und das PUT_RESULT legt fest das das Ergebnis direkt in die Senke\n
    * geschrieben wird. Ein bool result wird initialisiert und der interne Zustand von hash wird durch restart zurück gesetzt.\n
    * Folgend wird die Prüfsumme in digest geschrieben und ausgegeben.
    *
    *
    */
    cout << endl//Konsolenausgaben
         << "Hash Exercise:" << endl
         << "==============" << endl
         << endl;
    //4a
    string message = "Kryptographie macht immer noch Spaß!!!";
    string digest;
    SHA256 hash;
    StringSource(message, true ,new HashFilter(hash,//dem Filter HashFilter wird zur berechnung der Prüfsumme eine geeignete Hashfunktion übergeben
                                               new StringSink(digest)));
    //message = "Kryptographie macht immer noch sehr Spaß!!!";   //4b Nachricht ändern hat keine Auswirkung
    //Keine Veränderung
    word32 flags= HashVerificationFilter::HASH_AT_BEGIN | HashVerificationFilter::PUT_RESULT;
    //4c
    //Mithilfe von HashVerificationFilter::HASH_AT_END kann angegeben werden, dass die Prüfsumme nach dem String kommt
    //4a
    //message = "Kryptographie macht immer noch sehr Spaß!!!";   //Nachricht ändern hat keine Auswirkung

    //verifikation
    bool result;
    hash.Restart();//der interne Zustand von hash wird durch restart zurück gesetzt
    StringSource(digest + message, true, new HashVerificationFilter(
            hash, new ArraySink((byte*)&result, sizeof(result)), flags));
    cout << digest << endl;//Konsolenausgabe: m ����4ZD�h�Li����,d�I@[�
}


Integer modexp(const Integer &a, const Integer &b, const Integer &n) {
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


void IntegerExercise() {
/**
 *
 *
 * @brief Funktion vom Datentyp void um den Restwert der modularen Exponentiation drei Integer auszugeben.
 *
 * @details Funktion vom Datentyp void die Anfangs zwei Konsolenausgaben betätigt um bessere lesbarkeit der\n
 * Konsole zu erreichen.Die Integer x("371"), Integer e("18961551"), Integer m("2371"), Integer t = modexp(x, e, m) und\n
 * Integer r = a_exp_b_mod_c(x, e, m) werden initialisiert. Den Funktionen modeexp und a_exp_b_mod_c werden\n
 * die selben Parametern übergeben, um ein Ergebnis zum Vergleich zu haben ,da sie den selben Zweck erfüllen sollen.
 *
 * Grundform: a = y ^ 2 % p  ==  a = y * y % p Diese zwei Gleichungen sind identisch.\n
 * eulersche Kriterium: a ^ ((p - 1) / 2) % p    \n
 * zu y = (p - 1) / 2 eingesetzt in a ^ y % p Teil des eulerschen Kriteriums zu einer Variablen geformt.\n
 * d = a ^ y % p ==  modexp(a,y,p) = d Die Rechnung der Gleichung wird in der Funktion gegeben.
 *
 *
 * Die Integer a("58788"), Integer p("95957"), Integer y = (p - 1) / 2 und Integer q = modexp(a, y, p) werden initialisiert.\n
 * Anschließend werden t, r und q untereinander in der Konsole ausgegeben.
 *
 */
    cout << endl
         << "IntegerExercise:" << endl
         << "================" << endl << endl;
    //5a
    Integer x("371");
    Integer e("18961551");
    Integer m("2371");
    Integer t = modexp(x, e, m);//Funktion werden die richtigen Parameter zugewiesen

    //5b
    Integer r = a_exp_b_mod_c(x, e, m);//Vorgefertigte Funktion aus integer.h werden die richtigen Parameter zugewiesen

    //5c
    Integer a("58788");
    Integer p("95957");
    Integer y = (p - 1) / 2;//ergibt sich aus dem eulerschen Kriterium



    Integer q = modexp(a, y, p);//Funktion werden die richtigen Parameter zugewiesen


    cout << endl//Konsolenausgaben
         << t << endl//Konsolenausgabe: 1779.
         << r << endl//Konsolenausgabe: 1779.
         << q << endl << endl;//Konsolenausgabe: 1.

}

void RNGExercise() {
    /**
     *
     * @brief Funktion vom Datentyp void, welche die definierten Methoden der Klasse PRNG \n
     * und BlumBlumSchubGenerator aufruft und deren Ergebnisse ausgibt.\n
     *
     * @details Funktion vom Datentyp void die Anfangs zwei Konsolenausgaben betätigt um bessere lesbarkeit der\n
     * Konsole zu erreichen. Die Primzahlen Integer p ("1252910265243849922375596598575099209083498535192739493227403"), \n
     * Integer q ("1476222059624949757818143837507324048590620075519516306265283") und die\n
     * Integer s ("42") und Integer n = p*q werden initialisiert. Um die Methode BlumBlumShubGenerator bbs\n
     * mit Parameter n und s aufzurufen. In der for-Schleife wird die Methode getbit aufgerufen und in der \n
     * Konsolenausgabe ausgegeben.
     *
     * Zusätzlich werden byte buff[100] initialisiert und die Methode getBlock(buff, 100) aufgerufen und \n
     * in der Konsole ausgegeben. Es folgt die Methode getInteger(200*8) die aufgerufen und in der Konsole ausgeben wird.
     *
     * Der Integer temp ( 1073741824) wird initialisiert und die Methode getInteger(temp) aufgerufen und in der Konsole ausgeben.
     */
    cout << endl
         << "RNGExercise:" << endl
         << "============" << endl << endl;
    Integer p ("1252910265243849922375596598575099209083498535192739493227403");
    Integer q ("1476222059624949757818143837507324048590620075519516306265283");
    Integer s ("42");
    Integer n = p*q;

    byte buff[100];
    BlumBlumShubGenerator bbs (n, s);
    for (int i = 0; i < 20; i++) {
        //bbs.PRNG::getByte(); Das Ergebnis wird verändert, da der Pointer des BBS um 8 stellen verschoben wird. //6d
        cout << bbs.getBit();                               //6c
    }
    cout << endl;

    bbs.PRNG::getBlock(buff, 100);
    cout << "[";
    for (int i = 0; i < sizeof(buff)-1; i++) {
        cout << BytesToWords(buff[i]) << " ";                      //6f
    }
    cout << "]" << endl;

    cout << bbs.PRNG::getInteger(200*8) << endl;      //6h


    Integer temp ( 1073741824);
    //cout << bbs.PRNG::getInteger(temp);    //6j
    cout << endl;
}


int main() {
/**
 *
 *
 * @details Hauppteil vom Datentyp int der alle Funktionen nacheinander aufruft.
 *
 */
    DataFlowExercise();
    EncryptionExercise();
    HashExercise();
    IntegerExercise();
    RNGExercise();
    return 0;
}
