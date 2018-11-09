#pragma once

#include "tcpUserSocket.h"
#include <string>
#include <vector>
#include <iostream>    
#include <sstream>
#include <algorithm>
#include <cctype>   
#include "tcpUserSocket.h"
#include "tcpServerSocket.h"


using namespace std; 



    class chatUser{
        public: 
            inline chatUser(string username, string password, shared_ptr<cs457::tcpUserSocket> socket): nickName(username), password(password), userSocket(socket){};


        private:

        string nickName; 
        string password; 
        shared_ptr<cs457::tcpUserSocket> userSocket; 



    };




