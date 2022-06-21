/*
 * DHProtocol.cpp
 */
#include <cassert>
#include <fstream>
#include <asio.hpp>
#include "FortunaGenerator.h"
#include "MessageEncoder.h"
#include "DHProtocol.h"

using asio::ip::tcp;
using namespace std;
using namespace CryptoPP;

DHProtocol::DHProtocol(const string &param_file) {
    ifstream file;
    string data;
    MessageEncoder encoder;

    file.open(param_file.c_str());
    if (file.is_open() == false) {
        cout << "Could not open file: " << param_file << endl;
        assert(false);
    }

    file >> data;
    file.close();

    if (encoder.decode(data) == false) {
        cout << "Could not decode DH parameters." << endl;
        assert(false);
    }

    if (encoder.size() != 3) {
        cout << "Wrong number of DH parameters." << endl;
        assert(false);
    }

    q = encoder.getInteger(0);
    p = encoder.getInteger(1);
    alpha = encoder.getInteger(2);

    /*
     cout << "q = " << q << endl;
     cout << "p = " << p << endl;
     cout << "alpha = " << alpha << endl;
     */

}

void DHProtocol::alice(const string &host, const string &port) {
    /*
     * Aufgabe 4c)
     */

    /*
  * Alice is the client and connects the server Bob using
  * an ASIO TCP-IOStream object.
 */
    tcp::iostream bob_stream(tcp::resolver::query{host, port});

    if (!bob_stream) {
        // Connection could not established => Error!
        cout << "Error: " << bob_stream.error().message() << endl;
    } else {
        /*
         * Send a message to Bob.
         * IMPORTANT: The endl is used to mark the end of the message.
         */
        MessageEncoder me;
        string message = "Hello Server, I am Alice!";
        Integer z1("10232");
        Integer z2("8934");
        me.append(message);
        me.append(z1);
        me.append(z2);

        bob_stream << me.encode() << endl;
        /*
         * Receive a message from Bob.
         *
         * Bob must terminate the message with an endl.
         */
        getline(bob_stream, message);
        cout << "Got: " << message << endl;

        cout << "Acting as Alice." << endl;

}


void DHProtocol::serverBob(const string &port) {
    cout << "Acting as Bob." << endl;

    try {

        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), stoi(port)));

        while (true) {
            cout << endl << "Server Bob: waiting for incoming connections." << endl;
            tcp::iostream stream;
            if (!stream) {
                cout << "Error: " << stream.error().message() << endl;
            } else {
                acceptor.accept(*stream.rdbuf());
                bob(stream);
            }

        }
    } catch (exception &err) {
        cout << err.what() << endl;
    }

}

bool DHProtocol::bob(tcp::iostream &alice_strm) {
    /*
     * Aufgabe 4c)
     */

    return true;
}

void DHProtocol::serverOscar(const string& inport, const string &host, const string& port) {
    cout << endl << "Acting as Oscar." << endl;

    try {

        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), stoi(inport)));

        while (true) {
            cout << endl << "Server Oscar: waiting for incoming connections." << endl;
            tcp::iostream stream;
            if (!stream) {
                cout << "Error: " << stream.error().message() << endl;
            } else {
                acceptor.accept(*stream.rdbuf());
                oscar(stream, host, port);
            }

        }
    } catch (exception &err) {
        cout << err.what() << endl;
    }
}

bool DHProtocol::oscar(tcp::iostream &alice_strm, const string &host, const string& port) {
    /*
     * Aufgabe 4e)
     */

    /*
  * Alice is the client and connects the server Bob using
  * an ASIO TCP-IOStream objec/tcp::iostream bob_stream(tcp::resolver::query{host, port});

    if (!bob_stream) {
        // Connection could not established => Error!
        cout << "Error: " << bob_stream.error().message() << endl;
    } else {
        /*
         * Send a message to Bob.
         * IMPORTANT: The endl is used to mark the end of the message.
         */
    /*
        MessageEncoder me;
        string message = "Hello Server, I am Alice!";
        Integer z1("10232");
        Integer z2("8934");
        me.append(message);
        me.append(z1);
        me.append(z2);

        bob_stream << me.encode() << endl;
        /*
         * Receive a message from Bob.
         *
         * Bob must terminate the message with an endl.
         */
        getline(bob_stream, message);
        cout << "Got: " << message << endl;

        cout << "Acting as Alice." << endl;
        return true;
  }

}