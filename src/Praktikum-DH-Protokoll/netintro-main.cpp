#include <iostream>
#include "MessageEncoder.h"
#include <asio.hpp>

using asio::ip::tcp;
//Aufgabe 3b: Die verwendete Klassen: TCP, io_context

using namespace std;
using namespace CryptoPP;

void alice(string host, string port) {
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

        /*
         * Aufgabe 3c.
         */


    }
}

bool bob(tcp::iostream &alice_stream) {

    cout << "Accepting incoming connection." << endl;
    /*
     * Receiving a message from Alice.
     * IMPORTANT: Alice must terminate the message with an endl.
     */
    string message;
    getline(alice_stream, message);
    MessageEncoder me;
    me.decode(message);
    message = me.getString(0);
    Integer z1 = me.getInteger(1);
    Integer z2 = me.getInteger(2);
    cout << "Got: " << message  << " and: " << z1+z2 << endl;

    /*
     * Send a message to Alice.
     * IMPORTANT: Terminate the message with an endl.
     */
    message = "Hello from Bob.";
    alice_stream << message << endl;

    /*
     * Aufgabe 3c.
     */

    return true;
}

void serverBob(string port) {
    try {
        /*
         * Bob is the server and waits for incoming connections.
         * This is done via an Asio acceptor. The code is as follows:
         */
        asio::io_context io_context;
        tcp::acceptor acceptor(io_context, tcp::endpoint(tcp::v4(), stoi(port)));

        /*
         * The server does not stop. Use CTRL-C to terminate the software!
         */
        while (true) {
            cout << endl << "Server Bob: waiting for incoming connections." << endl;
            // Create a TCP-Stream to handle the incoming connection.
            tcp::iostream alice_stream;
            if (!alice_stream) {
                // Stream could not be created => Error!
                cout << "Error: " << alice_stream.error().message() << endl;
            } else {
                // Accept the incoming connection and ...
                acceptor.accept(*alice_stream.rdbuf());
                // ... start the communication!
                bob(alice_stream);
            }
        }
    } catch (exception &err) {
        cout << err.what() << endl;
    }
}

void help(string name) {
    cout << "Usage: " << name << " <mode>" << endl << endl;
    cout << "Modes:" << endl;
    cout << "  Alice <hostname> <port>" << endl;
    cout << "  Bob <port>" << endl;
}

int main(int argc, char **argv) {
    /*
     * Depending on the command line arguments, the program
     * acts as Alice or Bob
     */
    if (argc < 2) {
        help(argv[0]);
        return 1;
    }

    string mode = argv[1];

    /*
     * Act as Alice.
     */
    if (mode == "Alice") {
        if (argc < 3) {
            help(argv[0]);
            return 1;
        } else {
            string host(argv[2]);
            string port = argv[3];
            alice(host, port);
            return 0;
        }
    }

    /*
     * Act as Bob.
     */
    if (mode == "Bob") {
        if (argc < 2) {
            help(argv[0]);
            return 1;
        } else {
            serverBob(argv[2]);
            return 0;
        }
    }

    help(argv[0]);
    return 0;
}
