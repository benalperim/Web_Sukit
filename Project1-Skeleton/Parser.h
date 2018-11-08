#pragma once

#include <string>
#include <vector>
#include <iostream>    
#include <sstream>
#include <algorithm>
#include <cctype>   
#include "tcpUserSocket.h"
#include "tcpServerSocket.h"
using namespace std;

class Parser{
    public:
        void Parse(string command , shared_ptr<cs457::tcpUserSocket> clientSocket , string username , bool & loop); 

        bool DIE(vector <string> command);
        bool INFO(vector <string> command);
        void HELP();
        void QUIT(vector <string> command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username, bool & loop);
        
    private:


};