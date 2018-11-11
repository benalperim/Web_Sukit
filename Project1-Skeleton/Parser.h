#pragma once

#include <string>
#include <vector>
#include <iostream>    
#include <sstream>
#include <algorithm>
#include <cctype>   
#include "tcpUserSocket.h"
#include "tcpServerSocket.h"

#include "userObject.h"
#include <fstream>
#include <unordered_map>


using namespace std;
struct channel {
    string roomname;
    string topic;
    string password;
};
struct chatUser{
    string username;
    string password;
    string level;
    string banned;
};
 
struct RoomUser{
    shared_ptr<cs457::tcpUserSocket> socket;
    string userName;
}; 

struct Chatroom {
    string roomName;
    RoomUser user;
};


    
class Parser{
   

    public:
          
        void Parse(string command , shared_ptr<cs457::tcpUserSocket> clientSocket , string & username , bool & loop); 

        void DIE(string&  username);
        void INFO(shared_ptr<cs457::tcpUserSocket> clientSocket);
        void HELP(shared_ptr<cs457::tcpUserSocket> clientSocket);
        void PRIVMSG(vector<string> &, string& username);
        void QUIT(vector <string> command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username, bool & loop);
        void LIST(shared_ptr<cs457::tcpUserSocket> clientSocket );
        void JOIN(vector <string> command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username);

        
        bool USER(vector <string> command , shared_ptr<cs457::tcpUserSocket> clientSocket, string username,  bool & Authval);
        bool bannedUser(string&);
        void userPopulate();
        bool validateUser(string & username, string& password);


        userObject GUEST( shared_ptr<cs457::tcpUserSocket> clientSocket , string& username, bool & Authval);
        vector<channel> GetChatRooms();
        // this is where the magic happens    
        void MAGIC(string command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username);   
    private:
        int  counter = 0;
        vector<userObject> messagingList;
        vector<chatUser> userList;
        vector<channel> ChannelList;
        vector<Chatroom> ChatRooms;
        //vector<chatUser> generalChat;

        
};