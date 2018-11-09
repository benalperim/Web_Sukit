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
        string userName;
        string password;
        string level;
        string banned;
        shared_ptr<cs457::tcpUserSocket> socket;
        private:
    };
    