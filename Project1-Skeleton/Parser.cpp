#include "Parser.h"

void Parser::Parse(string command , cs457::tcpUserSocket clientSocket, string username ){
    
    if(command.at(0) == '/'){  
        istringstream tokenStream(command);
        vector<string> tokens;
        string token;
        char space = ' ';
        while (getline(tokenStream, token, space)){
            if(token.at(0)== '/'){
                transform(token.begin(), token.end(), token.begin(), ::tolower);
            }
            tokens.push_back(token);
        }


        if(tokens[0] == "/quit"){
            QUIT(tokens , clientSocket.getSocket() , username);
        }

         if(tokens[0] == "/info"){
            INFO(tokens);
        }

         if(tokens[0] == "/help"){
            HELP();
        }
    }
}


void Parser::HELP(){
    cout << "/CONNECT: \n" << "Connect takes a target server and port. Telling the server to connect to said server and port. Only allowed for Sysop or higher" << endl;
    cout << "/DIE \n" << "Die instructs the server to shut down. Only allowed by Admin" << endl;
    cout << "/INVITE\n" << "Invite takes a nickname and a channel name.  This invites the specified user to the specified channel." << endl;
    cout << "/JOIN \n" << "Join takes a list of channels seperated by a ','.  This will allow the client to join the specified channels, and if the channel does not exist one is made. Channel must be a number." << endl;
    cout << "/KILL \n" << "Kill takes a client and a comment.  This removes the client from the network with a message of why. Only allowed for Sysop or higher." << endl;
    cout << "/PRIVMSG \n" << "Privmsg takes a message reciever and a message.  This will send the message to the inidivual you specify." << endl;
    cout << "/QUIT \n" << "Quit removes the user from the server." << endl;
    cout << "/WHO \n" << "Who takes a name or part of a name.  This returns anyone who has name or part of the name in their nickname." << endl;
}

bool Parser::QUIT(vector <string> command , cs457::tcpUserSocket clientSocket , string username){
    
    if (command.size() >= 2){
        clientSocket.sendString(command[1]);
    }
    else{clientSocket.sendString("goodbye"); }
    
    clientSocket.closeSocket(); 
}