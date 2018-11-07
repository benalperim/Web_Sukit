#include "Commands.h"
#include "Login.h"
#include <string>
#include <iostream>

using namespace std;
//May need other headers to be able to do functions
//Do the check for the '/' in driver

void checkCommand(int& command, string& arguments){
    switch(command){
        case 0: AWAY(arguments); break;
        case 1: CONNECT(arguments); break;
        case 2: DIE(arguments); break;
        case 3: HELP(arguments); break;
        case 4: INFO(arguments); break;
        case 5: INVITE(arguments); break;
        case 6: ISON(arguments); break;
        case 7: JOIN(arguments); break;
        case 8: KICK(arguments); break;
        case 9: KILL(arguments); break;
        case 10: KNOCK(arguments); break;
        case 11: LIST(arguments); break;
        case 12: MODE(arguments); break;
        case 13: NICK(arguments); break;
        case 14: NOTICE(arguments); break;
        case 15: PART(arguments); break;
        case 16: OPER(arguments); break;
        case 17: PASS(arguments); break;
        case 18: PING(arguments); break;
        case 19: PONG(arguments); break;
        case 20: PRIVMSG(arguments); break;
        case 21: QUIT(arguments); break;
        case 22: RESTART(arguments); break;
        case 23: RULES(arguments); break;
        case 24: SETNAME(arguments); break;
        case 25: SILENCE(arguments); break;
        case 26: TIME(arguments); break;
        case 27: TOPIC(arguments); break;
        case 28: USER(arguments); break;
        case 29: USERHOST(arguments); break;
        case 30: USERIP(arguments); break;
        case 31: USERS(arguments); break;
        case 32: VERSION(arguments); break;
        case 33: WALLOPS(arguments); break;
        case 34: WHO(arguments); break;
        case 35: WHOIS(arguments); break;
        //default: cout << "clients talk" << endl;
        //send message from one client to another
    }
}

void AWAY(string& arguments){

}

void CONNECT(string& arguments){

}

void DIE(string& arguments){

}

void HELP(string& arguments){
    cout << "/CONNECT: \n" << "Connect takes a target server and port, telling the server to connect to said server and port. Only allowed for Sysop or higher" << endl;
    cout << "/DIE \n" << "Die instructs the server to shut down, only allowed by Admin" << endl;
    cout << "/\n" << "" << endl;
    cout << "/\n" << "" << endl;
    cout << "/\n" << "" << endl;
    cout << "/\n" << "" << endl;
    cout << "/\n" << "" << endl;
    cout << "/\n" << "" << endl;
    cout << "/\n" << "" << endl;
    cout << "/\n" << "" << endl;
    cout << "/\n" << "" << endl;
}

void INFO(string& arguments){

}

void INVITE(string& arguments){
    string nickname;
    int channel;
    istringstream ss(arguments);

}

void ISON(string& arguments){

}

void JOIN(string& arguments){

}

void KICK(string& arguments){

}

void KILL(string& arguments){

}

void KNOCK(string& arguments){

}

void LIST(string& arguments){

}

void MODE(string& arguments){

}

void NICK(string& arguments){

}

void NOTICE(string& arguments){

}

void PART(string& arguments){

}

void OPER(string& arguments){

}

void PASS(string& arguments){

}

void PING(string& arguments){

}

void PONG(string& arguments){

}

void PRIVMSG(string& arguments){

}

void QUIT(string& arguments){

}

void RESTART(string& arguments){

}

void RULES(string& arguments){

}

void SETNAME(string& arguments){

}

void SILENCE(string& arguments){

}

void TIME(string& arguments){

}

void TOPIC(string& arguments){

}

void USER(string& arguments){

}

void USERHOST(string& arguments){

}

void USERIP(string& arguments){

}

void USERS(string& arguments){

}

void VERSION(string& arguments){

}

void WALLOPS(string& arguments){

}

void WHO(string& arguments){

}

void WHOIS(string& arguments){

}