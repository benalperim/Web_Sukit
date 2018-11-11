#pragma once 
#include <string>
#include <iostream>
#include <vector>
#include <memory> 
#include "tcpUserSocket.h"


using namespace std;
    
    class userObject
    {
        public:
            inline userObject(string username, string password, shared_ptr<cs457::tcpUserSocket> socket, string level, string banned ): userName(username), password(password), socket(socket), level(level), banned(banned) {};


            inline string getNickname(){return this->userName;}
            inline string getPassword(){return this->password;}
            inline shared_ptr<cs457::tcpUserSocket> getSocket(){return this-> socket;}
            inline string getBanned(){return this -> banned;}
            inline string getLevel(){return this->level;}

        private:
            string userName;
            string password;
            shared_ptr<cs457::tcpUserSocket> socket;
            string level;
            string banned;
            
    };
    