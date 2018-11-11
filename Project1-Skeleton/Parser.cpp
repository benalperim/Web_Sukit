#include "Parser.h"

void Parser::Parse(string command , shared_ptr<cs457::tcpUserSocket> clientSocket, string&  username, bool & loop ){
    
    if(command.at(0) == '/'){  
        istringstream tokenStream(command);
        vector<string> tokens;
        string token;
        char space = ' ';
        while (getline(tokenStream, token, space)){
             //cout << "token: " << token<< endl;
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

        else if(tokens[0] == "/help"){
             HELP(clientSocket);
        }

        else if(tokens[0] == "/user"){
            cout << "hit user" << endl;
            USER(tokens, clientSocket, username, loop);
        }

        else if(tokens[0] == "/die"){
            cout << "hit die check privilage" << endl;
            DIE(username); // USERNAME IS STORED WRONG ASK ALPER
        }

        else if(tokens[0] == "/privmsg"){
            cout << "priv msg" << endl;
            PRIVMSG(tokens, username);
        }

        else if(tokens[0] == "/join"){
             cout << "hit join" << endl;
            JOIN(tokens , clientSocket , username);
        }

        else if(tokens[0] == "/info"){
             cout << "hit info" << endl;
            INFO(clientSocket);
        }

        else if(tokens[0] == "/list"){
            cout << "hit list" << endl;
            LIST(clientSocket);
        }
       
    }
    else {
            cout << "hit MAGICCC" << endl;
            MAGIC(command, clientSocket , username);
    }
}


void Parser::DIE(string&  username){
    bool allowed = false;
    cout << username << endl;
    for(unsigned int j = 0; j < userList.size(); j++){
        if(username.compare(userList[j].username) == 0){
            string admin = "Admin";
            if(admin.compare(userList[j].level) == 0){
                allowed = true;
            }
        }
    }
    if(allowed){
        cout <<  "size of users " << messagingList.size() << endl;
        for(unsigned int i = 0; i < messagingList.size(); i ++){
        sleep(1);
        messagingList[i].getSocket()->sendString("Server is shutting down.");
        sleep(1);
        messagingList[i].getSocket()->sendString("goodbye");
        }
        sleep(1);
        exit(-1);
    }
}


void Parser::HELP(shared_ptr<cs457::tcpUserSocket> clientSocket){
    string help = "";
    //help += "/CONNECT: \n Connect takes a target server and port. Telling the server to connect to said server and port. Only allowed for Sysop or higher\n\n";
    help += "/DIE \n Die instructs the server to shut down. Only allowed by Admin\n\n";
    //help += "/INVITE\n Invite takes a nickname and a channel name.  This invites the specified user to the specified channel.\n\n";
    help += "/INFO \n Info displays information about the creators of this chatting application\n\n";
    help += "/JOIN \n Join takes a channel and a password if needed.  This will allow the client to join the specified channel, and if the channel does not exist one is made.\n\n";
    //help += "/KILL \n Kill takes a client and a comment.  This removes the client from the network with a message of why. Only allowed for Sysop or higher.\n\n";
    help += "/LIST \n List provides a list of of available channels along with thier topics and if a password is needed";
    help += "/PRIVMSG \n Privmsg takes a message reciever and a message.  This will send the message to the inidivual you specify.\n\n";
    help += "/QUIT \n Quit removes the user from the server.\n\n";
    //help += "/WHO \n Who takes a name or part of a name.  This returns anyone who has name or part of the name in their nickname.\n\n";
    clientSocket.get()->sendString(help);
}


void Parser::INFO(shared_ptr<cs457::tcpUserSocket> clientSocket){
    string about = "This Chatting Application is brought to you by a Turkish Delight and Baby Blue  (Alper K. and Jacob T.)";
    clientSocket.get()->sendString(about);
    
}


void Parser::JOIN(vector <string> command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username){
    
    if (command.size() > 1 ){
        //get room name
        string roomName = command[1];
        cout << "room name = " <<roomName << endl;
        //get room password
        string roomPassword = "-1";

        for(unsigned int i = 0; i < ChannelList.size(); i++ ){
            if(roomName.compare(ChannelList[i].roomname) == 0){
                roomPassword = ChannelList[i].password;
            }
        }
        if(roomPassword == "-1"){
            clientSocket.get()->sendString("Try /list to see all chat rooms available" );
            return;
        }
        cout << "room password = " << roomPassword << endl;

        for(unsigned int j = 0; j < messagingList.size(); j++){
            if(username.compare(messagingList[j].getNickname()) == 0){
                 cout << "user = " << messagingList[j].getNickname() << endl;
                if(messagingList[j].getLevel().compare("guest") == 0){ 
                    if(  roomPassword != "@" ){
                        clientSocket.get()->sendString("guests do not have the privilage to join a Password protected rooms");
                        return;
                    }else {
                        clientSocket.get()->sendString("[" + username + "] joined " + roomName + "!! \n" );
                        Chatroom room;
                        room.roomName = roomName;

                        RoomUser rmUsr;
                        rmUsr.userName = username;
                        rmUsr.socket = clientSocket;

                        room.user = rmUsr;
                        ChatRooms.push_back(room);

                        return;
                    } 
                }
                else if (messagingList[j].getLevel().compare("guest") != 0){
                    if(  roomPassword != "@" ){
                        if (!(command.size() > 2) ){
                            clientSocket.get()->sendString("Please provide a password for protected rooms " );
                            return;
                        }
                        if(roomPassword.compare(command[2]) == 0){
                            //cout << "user level " << messagingList[j].getLevel() << endl;
                            clientSocket.get()->sendString(username + " joined " + roomName + "!! \n" );
                                Chatroom room;
                                room.roomName = roomName;
                                
                                RoomUser rmUsr;
                                rmUsr.userName = username;
                                rmUsr.socket = clientSocket;

                                room.user = rmUsr;
                                ChatRooms.push_back(room);

                            return;
                        }
                        else if(roomPassword.compare(command[2]) != 0){
                            clientSocket.get()->sendString("wrong password for room :" + roomName );
                            return;
                        }
                    
                    }
                    else{
                        clientSocket.get()->sendString(username + " joined " + roomName + "!! \n" );
                            Chatroom room;
                            room.roomName = roomName;
                            
                            RoomUser rmUsr;
                            rmUsr.userName = username;
                            rmUsr.socket = clientSocket;

                            room.user = rmUsr;
                            ChatRooms.push_back(room);
                        return;
                    }
                }
                //clientSocket.get()->sendString("if you hit here IDK how you managed it but you dont exist technically" );
            }
        }
    }

    else{
        clientSocket.get()->sendString("send room name first and password if applicable");
        return;
    }
}


void Parser::LIST(shared_ptr<cs457::tcpUserSocket> clientSocket){
    string chatRoomInfo = "";
    for(unsigned int i = 0; i < ChannelList.size(); i++ ){
        chatRoomInfo += ChannelList.at(i).roomname + " with topic " + ChannelList.at(i).topic + " ";
        if(ChannelList.at(i).password.compare("@") == 0 ){
            chatRoomInfo += " public chat \n";
        }
        else 
            chatRoomInfo += " password Protected chat \n";
    } 
     clientSocket.get()->sendString(chatRoomInfo);

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
        for( unsigned int j = 0; j < messagingList.size(); j++){
            if(username.compare(messagingList[j].getNickname()) == 0){
                cout << "matched at " << j << std::endl;
                messagingList.erase(messagingList.begin()+j);
            }
        }
        sleep(1);
    }

    else{
        clientSocket.get()->sendString("goodbye"); 
        for( unsigned int j = 0; j < messagingList.size(); j++){
                if(username.compare(messagingList[j].getNickname()) == 0){
                    cout << "matched at " << j << std::endl;
                    messagingList.erase(messagingList.begin()+j);
                }
            }
        sleep(1);
    }

    loop = false;
    clientSocket.get()->closeSocket(); 
}

userObject Parser::GUEST(shared_ptr<cs457::tcpUserSocket> clientSocket , string & username, bool & Authval){
    
    string passwrd = "-1";
    username += to_string(counter); 
    cout << "username " << username << std::endl;
    counter++;
    
    userObject user(username, passwrd , clientSocket , "guest", "false" );
 
    messagingList.push_back(user); //changed
    Authval = true;

    return user;
}

  bool Parser::USER(vector <string> command , shared_ptr<cs457::tcpUserSocket> clientSocket ,string username , bool & Authval){
    string level ="user";
    string pasword = "-1";
    if(command.size() >= 2){
        pasword =command[1];
    }
    cout << "uname  " << username << std::endl;
    cout << "paswrd  " << pasword << std::endl;
    if(validateUser(username , command[1])){
        
        for (unsigned int i = 0; i < userList.size(); i++ ){
            if(username.compare(userList[i].username) == 0){
                string level = userList[i].level;
            }
        }


        userObject user (username , pasword ,clientSocket, level, "false" ); 
        messagingList.push_back(user); //changed
        Authval = true;
        return true;
    }

    return false;
  }



//MAGIC
void Parser::MAGIC(string command, shared_ptr<cs457::tcpUserSocket> clientSocket , string username){
    cout << "chat Room Size : "<< ChatRooms.size() << endl;
    
    vector<RoomUser> sameUsers;

    string overall = "[" + username + "]" + ": " + command;


    for(unsigned int i = 0; i < ChatRooms.size(); i++){
        if(ChatRooms[i].user.userName.compare(username) == 0){
            string roomName = ChatRooms[i].roomName;
            cout << "roomname "<< roomName << endl;
            for(unsigned int j = 0; j < ChatRooms.size(); j++){
                if(ChatRooms[j].roomName.compare(roomName) == 0){
                    RoomUser RU;
                    RU.userName = ChatRooms[j].user.userName;
                    RU.socket = ChatRooms[j].user.socket;
                    sameUsers.push_back(RU);
                    
                }
            }
            
        }

    }
    if(sameUsers.size() == 0){
        return;
    }else{
    for(unsigned int k = 0; k < sameUsers.size(); k++){
                sameUsers[k].socket.get()-> sendString(overall);
                sleep(1);

    }

    }

}











//HELPER MTHODS

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
        chatUser tempObj;
        istringstream ss(line);
        ss >> username >> password >> level >> banned;
        tempObj.username = username;
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
        string uName = userList[i].username;
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
