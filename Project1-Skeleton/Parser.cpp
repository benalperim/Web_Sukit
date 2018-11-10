#include "Parser.h"

void Parser::Parse(string command , shared_ptr<cs457::tcpUserSocket> clientSocket, string&  username, bool & loop ){
    
    if(command.at(0) == '/'){  
        istringstream tokenStream(command);
        vector<string> tokens;
        string token;
        char space = ' ';
        while (getline(tokenStream, token, space)){
             cout << "token: " << token<< endl;
            if(token.at(0)== '/'){
                transform(token.begin(), token.end(), token.begin(), ::tolower);
            }
             
            tokens.push_back(token);
        }


        if(tokens[0] == "/quit"){
            cout << "hit quit" << std::endl;
            QUIT(tokens , clientSocket , username, loop);
        }

        else if(tokens[0] == "/guest"){
            cout << "hit guest" << std::endl;
             GUEST(clientSocket , username , loop);
        }

        if(tokens[0] == "/help"){
             HELP(clientSocket);
        }

        else if(tokens[0] == "/user"){
            cout << "hit user" << endl;
            USER(tokens, clientSocket, username, loop);
        }

        if(tokens[0] == "/die"){
            DIE(username); // USERNAME IS STORED WRONG ASK ALPER
        }

        if(tokens[0] == "/privmsg"){
            PRIVMSG(tokens, username);
        }

        if(tokens[0] == "/join"){
            JOIN();
        }

        if(tokens[0] == "/info"){
            INFO(clientSocket);
        }
    }
}


void Parser::DIE(string&  username){// THIS METHOD DOES NOT WORK IN THE SLIGHTEST BECUASE USERNAME GIVEN IS WRONG
    bool allowed = false;
    cout << username << endl;
    for(unsigned int j = 0; j < userList.size(); j++){
        if(username.compare(userList[j].userName) == 0){
            string admin = "Admin";
            if(admin.compare(userList[j].level) == 0){
                allowed = true;
            }
        }
    }
    if(allowed){
        for(unsigned int i = 0; i < messagingList.size(); i ++){
        messagingList[i].getSocket()->sendString("Server is shutting down.");
        sleep(1);
        messagingList[i].getSocket()->sendString("goodbye");
        }
        exit(-1);
    }
}

void Parser::HELP(shared_ptr<cs457::tcpUserSocket> clientSocket){
    string help = "";
    help += "/CONNECT: \n Connect takes a target server and port. Telling the server to connect to said server and port. Only allowed for Sysop or higher\n\n";
    help += "/DIE \n Die instructs the server to shut down. Only allowed by Admin\n\n";
    help += "/INVITE\n Invite takes a nickname and a channel name.  This invites the specified user to the specified channel.\n\n";
    help += "/JOIN \n Join takes a list of channels seperated by a ','.  This will allow the client to join the specified channels, and if the channel does not exist one is made. Channel must be a number.\n\n";
    help += "/KILL \n Kill takes a client and a comment.  This removes the client from the network with a message of why. Only allowed for Sysop or higher.\n\n";
    help += "/PRIVMSG \n Privmsg takes a message reciever and a message.  This will send the message to the inidivual you specify.\n\n";
    help += "/QUIT \n Quit removes the user from the server.\n\n";
    help += "/WHO \n Who takes a name or part of a name.  This returns anyone who has name or part of the name in their nickname.\n\n";
    clientSocket.get()->sendString(help);
}

void Parser::INFO(shared_ptr<cs457::tcpUserSocket> clientSocket){
    string about = "This Chatting Application is brought to you by a Turkish Delight and Baby Blue  (Alper K. and Jacob T.)";
    clientSocket.get()->sendString(about);
}

void Parser::JOIN(){
    //CANNOT DO THIS UNTIL CHAT ROOMS
}

void Parser::PRIVMSG(vector<string>& tokens, string& username){
    string message = "From [" + username + "]: ";
    for(unsigned int i = 2; i < tokens.size(); i++){ // makes string to send to user
        message += tokens[i] + " ";
    }
    cout << message << endl;
    for(unsigned int j = 0; j < messagingList.size(); j++){ //searches user list in order to find which socket to send to 
        if(tokens[1].compare(messagingList[j].getNickname()) == 0){
            messagingList[j].getSocket()->sendString(message);
        }
    }
}

void Parser::QUIT(vector <string> command , shared_ptr<cs457::tcpUserSocket> clientSocket , string username, bool & loop){
    
    if (command.size() >= 2){
        string msg = command[1];
        clientSocket.get()->sendString(msg);
    }
    else{clientSocket.get()->sendString("goodbye"); }
    loop = false;
    clientSocket.get()->closeSocket(); 
}

chatUser Parser::GUEST(shared_ptr<cs457::tcpUserSocket> clientSocket , string & username, bool & Authval){
    
    string passwrd = "-1";
    username += to_string(counter); 
    cout << "username " << username << std::endl;
    counter++;
    
    chatUser user(username , passwrd, clientSocket);
    messagingList.push_back(user); //changed
    Authval = true;
    generalChat.push_back(user);

    return user;
}

  bool Parser::USER(vector <string> command , shared_ptr<cs457::tcpUserSocket> clientSocket ,string username , bool & Authval){
   
    string pasword = "-1";
    if(command.size() >= 2){
        pasword =command[1];
    }
    cout << "uname  " << username << std::endl;
     cout << "paswrd  " << pasword << std::endl;
    if(validateUser(username , command[1])){
        chatUser user(username , pasword, clientSocket);
        messagingList.push_back(user); //changed
        Authval = true;
        generalChat.push_back(user);
        return true;
    }

    return false;
  }


vector<channel> Parser::GetChatRooms(){
    ifstream ifstr;
    ifstr.open("channels.txt");
    string line;
   
    while(getline(ifstr, line)){
        string RN, Topic, PW;
        istringstream ss(line);
        ss >> RN >> Topic >> PW;
        channel pop;
        pop.roomname = RN;
        pop.topic = Topic;
        pop.password = PW;
        ChannelList.push_back(pop);
    }
    
    return ChannelList;



}













//###################################################################################################################################################


bool Parser::bannedUser(string& userName){ //checks to see if the username is within the banned list. Returns True if user is banned, false elsewise
    string line;
    ifstream ifstr;
    ifstr.open("banusers.txt");
    while(getline(ifstr, line)){
		if (line.find(userName) != string::npos ){
			return true;
		}
	}
    return false;
}

void Parser::userPopulate(){ //Call this upon start of SERVER
    ifstream ifstr;
    ifstr.open("users.txt");
    string line;
    string username, password, level, banned;

    while(getline(ifstr, line)){
        userObject tempObj;
        istringstream ss(line);
        ss >> username >> password >> level >> banned;
        tempObj.userName = username;
        tempObj.password = password;
        tempObj.level = level;
        tempObj.banned = banned;
        userList.push_back(tempObj);
    }
    ifstr.close();
    
}

bool Parser::validateUser(string& username, string& password){ //checks to see if the username is taken by somebody else in the system. Returns True if username already taken , false elsewise 
   //cout << "size : @@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@@- " << userList.size() << std::endl;
    if(bannedUser(username)){cout << "Banned User: "<< username << endl; return false;}
    for(unsigned int i = 0; i < userList.size(); i++){
        string uName = userList[i].userName;
        //cout << "checking " << uName << std::endl;
        
        if(username.compare(uName) == 0){ //Username is in list, check the password
            string uPass = userList[i].password;
            //cout << "passwrdsuppose toi be " << uPass << std::endl;
            if(password.compare(uPass) == 0){ //password is correct
            return true;
            }
            else{return false;} //password is incorrect
        }
    }
    return false;
}