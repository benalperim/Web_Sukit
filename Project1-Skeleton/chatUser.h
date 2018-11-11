#pragma once

#include "tcpUserSocket.h"
#include <string>
#include <vector>
#include <iostream>    
#include <sstream>
#include <algorithm>
#include <cctype>   



using namespace std; 



    class chatUser{
        public: 

            inline chatUser(string username, string password, string level, string banned): nickName(username), password(password), level(level) , banned(banned){};
            inline string getNickname(){return this->nickName;}
            inline string getPassword(){return this->password;}
            inline string getLevel(){return this -> level;}
            inline string getBanned() {return this -> banned;}
            

        private:

            string nickName; 
            string password; 
            string level;
            string banned
        


    };




