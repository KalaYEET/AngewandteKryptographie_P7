/*
 * enctest.cpp
 */
#include <iostream>
#include "MessageEncoder.h"
#include <integer.h>

using namespace std;
using namespace CryptoPP;

void encoderTest() {
	cout << "MessageEncoderTest" << endl <<
			"==================" << endl;
   /*
    * Aufgabe 2b+c+d+e+f
    */
    MessageEncoder me;
    me.append(Integer("10892"));
    me.append("Hallo Welt!");
    me.append(Integer("459111231"));

    string coded = me.encode();
    me.decode(coded);

    Integer i = me.getInteger(0);
    string s = me.getString(1);
    Integer j = me.getInteger(2);
    string k;


    cout << "Aufgabe 2b)" << endl;
    cout << coded << endl;
    cout << i << endl << s << endl << j << endl << endl;

    me.clear();

    cout << "Aufgabe 2c)" << endl;
    me.append(Integer ("98921323668113423232"));
    me.append("Kryptografie macht Spass!");
    me.append("Crypto++ ist eine Kryptografie-Bibliothek");
    me.append (Integer ("456291260721096"));

    coded = me.encode();
    cout << coded << endl << endl;
    cout << "Aufgabe 2d)" << endl;

    me.decode(coded);
    i = me.getInteger(0);
    s = me.getString(1);
    j = me.getInteger(3);
    k = me.getString(2);

    cout << i << endl << s << endl << k << endl << j << endl << endl;

    me.clear();
    cout << "Aufgabe 2e + f)" << endl;
    coded = "6DB03BF70E#4963682062696E2065696E65205A65696368656E666F6C67652C20646965#207369636820617573207A776569205465696C656E207A7573616D6D656E7365747A74";
    me.decode(coded);
    string MAC = "937A6984EE71C06E808AB996BF76C246AC29E198B6637B02C37ABDE92D6A46C8";
    string key = "ahVoh4naghie";
    cout << me.verify(key, MAC) << endl;
    i = me.getInteger(0);
    s = me.getString(1);
    k = me.getString(2);

    cout << i << endl << s << endl << k << endl << endl;

    me.clear();


}

int main(int argc, char **argv) {
	encoderTest();
	return 0;
}
