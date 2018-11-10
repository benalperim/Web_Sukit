#pragma once

#include <string>
#include <vector>
#include <iostream>    
#include <sstream>
#include <algorithm>
#include <cctype>   
#include "tcpUserSocket.h"
#include "tcpServerSocket.h"
#include "chatUser.h"
#include "userObject.h"
#include <fstream>
using namespace std;

class Parser{
    public:
        void Parse(string command , shared_ptr<cs457::tcpUserSocket> clientSocket , string & username , bool & loop); 

        bool DIE(vector <string> command);
        bool INFO(vector <string> command);
        void HELP(shared_ptr<cs457::tcpUserSocket> clientSocket);
        void QUIT(vector <string> command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username, bool & loop);
        chatUser GUEST( shared_ptr<cs457::tcpUserSocket> clientSocket , string& username, bool & Authval);
        bool USER(vector <string> command , shared_ptr<cs457::tcpUserSocket> clientSocket, string username,  bool & Authval);
        bool bannedUser(string&);
        void userPopulate();
        bool validateUser(string & username, string& password);
    private:
        int  counter = 0;
        vector<userObject> userList;

};