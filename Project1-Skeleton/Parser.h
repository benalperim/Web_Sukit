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
        void Parse(string command , cs457::tcpUserSocket clientSocket , string username); 

        bool DIE(vector <string> command);
        bool INFO(vector <string> command);
        void HELP();
        bool QUIT(vector <string> command, cs457::tcpUserSocket clientSocket , string username);
        
    private:


};