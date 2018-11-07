#pragma once

#include <string>
#include <vector>
#include <unordered_map>
#include "tcpUserSocket.h"

using namespace std;
class Commands
{
    struct chatRoomUser{
        string name;
        cs457::tcpUserSocket socket;
    };


    public:
    void populateChatRoomUser(string&, cs457::tcpUserSocket&);
    void checkCommand(int&, string&);
    void AWAY(string&);
    void CONNECT(string&);
    void DIE(string&);
    void HELP(string&);
    void INFO(string&);
    void INVITE(string&);
    void ISON(string&);
    void JOIN(string&);
    void KICK(string&);
    void KILL(string&);
    void KNOCK(string&);
    void LIST(string&);
    void MODE(string&);
    void NICK(string&);
    void NOTICE(string&);
    void PART(string&);
    void OPER(string&);
    void PASS(string&);
    void PING(string&);
    void PONG(string&);
    void PRIVMSG(string&);
    void QUIT(string&);
    void RESTART(string&);
    void RULES(string&);
    void SETNAME(string&);
    void SILENCE(string&);
    void TIME(string&);
    void TOPIC(string&);
    void USER(string&);
    void USERHOST(string&);
    void USERIP(string&);
    void USERS(string&);
    void VERSION(string&);
    void WALLOPS(string&);
    void WHO(string&);
    void WHOIS(string&);

    private:
    int roomNumber = 0;
    vector<chatRoomUser> CRU;
    unordered_map<int, vector<chatRoomUser>> chatRoom;

    //unordered_map<string, string> privMessage;
        
};