#include "Commands.h"
#include <string>

using namespace std;
//May need other headers to be able to do functions
//Do the check for the '/' in driver
void checkCommand(int command, string& arguments){
    switch(command){
        case 0: AWAY(string& arguments); break;
        case 1: CONNECT(string& arguments); break;
        case 2: DIE(string& arguments); break;
        case 3: HELP(string& arguments); break;
        case 4: INFO(string& arguments); break;
        case 5: INVITE(string& arguments); break;
        case 6: ISON(string& arguments); break;
        case 7: JOIN(string& arguments); break;
        case 8: KICK(string& arguments); break;
        case 9: KILL(string& arguments); break;
        case 10: KNOCK(string& arguments); break;
        case 11: LIST(string& arguments); break;
        case 12: MODE(string& arguments); break;
        case 13: NICK(string& arguments); break;
        case 14: NOTICE(string& arguments); break;
        case 15: PART(string& arguments); break;
        case 16: OPER(string& arguments); break;
        case 17: PASS(string& arguments); break;
        case 18: PING(string& arguments); break;
        case 19: PONG(string& arguments); break;
        case 20: PRIVMSG(string& arguments); break;
        case 21: QUIT()string& arguments; break;
        case 22: RESTART(string& arguments); break;
        case 23: RULES(string& arguments); break;
        case 24: SETNAME(string& arguments); break;
        case 25: SILENCE(string& arguments); break;
        case 26: TIME(string& arguments); break;
        case 27: TOPIC(string& arguments); break;
        case 28: USER(string& arguments); break;
        case 29: USERHOST(string& arguments); break;
        case 30: USERIP(string& arguments); break;
        case 31: USERS(string& arguments); break;
        case 32: VERSION(string& arguments); break;
        case 33: WALLOPS(string& arguments); break;
        case 34: WHO(string& arguments); break;
        case 35: WHOIS(string& arguments); break;
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

}

void INFO(string& arguments){

}

void INVITE(string& arguments){

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