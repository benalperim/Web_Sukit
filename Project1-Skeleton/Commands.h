#pragma once

#include <string>

namespace cs457
{
    using namespace std;
    class Commands
    {
        public:
        void checkCommand(int, string&);
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
    }
}