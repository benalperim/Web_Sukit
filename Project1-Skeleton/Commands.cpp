#include "Commands.h"
#include "Login.h"
#include <string>
#include <iostream>
#include <sstream>

using namespace std;
//May need other headers to be able to do functions
//Do the check for the '/' in driver

void Commands::checkCommand(int command, string& arguments){
    switch(command){
        case 0: AWAY(arguments); break;
        case 1: CONNECT(arguments); break;
        case 2: DIE(arguments); break;
        case 3: HELP(arguments); break;
        case 4: INFO(arguments); break;
        case 5: INVITE(arguments); break;
        case 6: ISON(arguments); break;
        case 7: JOIN(arguments); break;
        case 8: KICK(arguments); break;
        case 9: KILL(arguments); break;
        case 10: KNOCK(arguments); break;
        case 11: LIST(arguments); break;
        case 12: MODE(arguments); break;
        case 13: NICK(arguments); break;
        case 14: NOTICE(arguments); break;
        case 15: PART(arguments); break;
        case 16: OPER(arguments); break;
        case 17: PASS(arguments); break;
        case 18: PING(arguments); break;
        case 19: PONG(arguments); break;
        case 20: PRIVMSG(arguments); break;
        case 21: QUIT(arguments); break;
        case 22: RESTART(arguments); break;
        case 23: RULES(arguments); break;
        case 24: SETNAME(arguments); break;
        case 25: SILENCE(arguments); break;
        case 26: TIME(arguments); break;
        case 27: TOPIC(arguments); break;
        case 28: USER(arguments); break;
        case 29: USERHOST(arguments); break;
        case 30: USERIP(arguments); break;
        case 31: USERS(arguments); break;
        case 32: VERSION(arguments); break;
        case 33: WALLOPS(arguments); break;
        case 34: WHO(arguments); break;
        case 35: WHOIS(arguments); break;
        //default: cout << "clients talk" << endl;
        //send message from one client to another
    }
}
void Commands::populateChatRoomUser(string& username, shared_ptr<cs457::tcpUserSocket> suckit){
    chatRoomUser user;
    user.name = username;
    user.socket = suckit; //I DONT KNOW WHY THIS GETS MAD
    CRU.push_back(user);
}

void Commands::AWAY(string& arguments){

}

void Commands::CONNECT(string& arguments){

}

void Commands::DIE(string& arguments){

}

void Commands::HELP(string& arguments){
    cout << "/CONNECT: \n" << "Connect takes a target server and port. Telling the server to connect to said server and port. Only allowed for Sysop or higher" << endl;
    cout << "/DIE \n" << "Die instructs the server to shut down. Only allowed by Admin" << endl;
    cout << "/INVITE\n" << "Invite takes a nickname and a channel name.  This invites the specified user to the specified channel." << endl;
    cout << "/JOIN \n" << "Join takes a list of channels seperated by a ','.  This will allow the client to join the specified channels, and if the channel does not exist one is made. Channel must be a number." << endl;
    cout << "/KILL \n" << "Kill takes a client and a comment.  This removes the client from the network with a message of why. Only allowed for Sysop or higher." << endl;
    cout << "/PRIVMSG \n" << "Privmsg takes a message reciever and a message.  This will send the message to the inidivual you specify." << endl;
    cout << "/QUIT \n" << "Quit removes the user from the server." << endl;
    cout << "/WHO \n" << "Who takes a name or part of a name.  This returns anyone who has name or part of the name in their nickname." << endl;
}

void Commands::INFO(string& arguments){
    //KEY COMMAND 
    cout << "Your mom is a whore" << endl;
}

void Commands::INVITE(string& arguments){
    string nickname, channel;
    
    istringstream ss(arguments);
    ss >> nickname >> channel;
    
    auto search = chatRoom.find(stoi(channel));
    if(search != chatRoom.end()){
        for(unsigned int i = 0; i < CRU.size(); i++){
            if(nickname == CRU[i].name){
                search->second.push_back(CRU[i]);
            }
        }
    }
    else{
        cout << "Chatroom does not exist" << endl;
    }
}

void Commands::ISON(string& arguments){

}

void Commands::JOIN(string& arguments){ // NEED socket from the user trying to join chat to be able to put him into the chat room users or the name after we populate CRU
    //NOT MADE FOR PASSWORDS YET
    //KEY COMMAND
    vector<string> channels;
    istringstream ss(arguments);
    string line;
    while (ss >> line){ //https://stackoverflow.com/questions/1894886/parsing-a-comma-delimited-stdstring
        channels.push_back(line);
        if(ss.peek() == ','){
            ss.ignore();
            }
    }
    for(unsigned int i = 0; i < channels.size(); i++){
        auto search = chatRoom.find(stoi(channels[i])); //CHANNEL MUST BE INTEGER
        if(search != chatRoom.end()){
            //let user join chat room
        }
        else{
            cout << "lol jk we havent implemented this" << endl;
            /*vector<chatRoomUser> temp;
            for(unsigned int j = 0; j < CRU.size(); j++){
                if(username == CRU[j].name){
                //USE NICKNAME TO GET THE CRU OF THE USERNAME
                    temp.push_back(CRU[j]);
                    chatRoom.insert({roomNumber, temp});
                    roomNumber += 1; //may be issue
                }*/
            //}
        }
    }
    
}

void Commands::KICK(string& arguments){

}

void Commands::KILL(string& arguments){

}

void Commands::KNOCK(string& arguments){

}

void Commands::LIST(string& arguments){

}

void Commands::MODE(string& arguments){

}

void Commands::NICK(string& arguments){

}

void Commands::NOTICE(string& arguments){

}

void Commands::PART(string& arguments){

}

void Commands::OPER(string& arguments){

}

void Commands::PASS(string& arguments){

}

void Commands::PING(string& arguments){

}

void Commands::PONG(string& arguments){

}

void Commands::PRIVMSG(string& arguments){ // again need the name of the person along with their indiviual socket passing
    //KEY COMMAND
    string to, message;
    istringstream ss(arguments);
    ss >> to >> message;
    for(unsigned int i = 0; i < CRU.size(); i++){
        if(to == CRU[i].name){
            //send message using CRU[i].socket
        }
        else{
            cout << "user not logged on" << endl;
        }
    }
}

void Commands::QUIT(string& arguments){
    //KEY COMMAND
}

void Commands::RESTART(string& arguments){

}

void Commands::RULES(string& arguments){

}

void Commands::SETNAME(string& arguments){

}

void Commands::SILENCE(string& arguments){

}

void Commands::TIME(string& arguments){

}

void Commands::TOPIC(string& arguments){

}

void Commands::USER(string& arguments){

}

void Commands::USERHOST(string& arguments){

}

void Commands::USERIP(string& arguments){

}

void Commands::USERS(string& arguments){

}

void Commands::VERSION(string& arguments){

}

void Commands::WALLOPS(string& arguments){

}

void Commands::WHO(string& arguments){

}

void Commands::WHOIS(string& arguments){

}