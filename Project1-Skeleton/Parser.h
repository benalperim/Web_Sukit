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
struct channel {
    string roomname;
    string topic;
    string password;
};
    
class Parser{
   

    public:
          
        void Parse(string command , shared_ptr<cs457::tcpUserSocket> clientSocket , string & username , bool & loop); 

        void DIE(string&  username);
        void INFO(shared_ptr<cs457::tcpUserSocket> clientSocket);
        void JOIN();
        void HELP(shared_ptr<cs457::tcpUserSocket> clientSocket);
        void PRIVMSG(vector<string> &, string& username);
        void QUIT(vector <string> command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username, bool & loop);
        bool JOIN(vector <string> command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username, bool & loop);


        bool USER(vector <string> command , shared_ptr<cs457::tcpUserSocket> clientSocket, string username,  bool & Authval);
        bool bannedUser(string&);
        void userPopulate();
        bool validateUser(string & username, string& password);


        chatUser GUEST( shared_ptr<cs457::tcpUserSocket> clientSocket , string& username, bool & Authval);
        vector<channel> GetChatRooms();

            
    private:
        int  counter = 0;
        vector<chatUser> messagingList;
        vector<userObject> userList;
        vector<channel> ChannelList;
        vector<chatUser> generalChat;
        
};