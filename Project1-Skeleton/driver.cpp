#include <iostream>
#include <string> 
#include <tuple> 
#include <thread> 
#include <vector> 
#include <memory> 
#include "tcpUserSocket.h"
#include "tcpServerSocket.h"
#include "Login.h"
#include "Parser.h"

using namespace std;

bool ready = true; 

//for authentication setup
Parser parser;
Login login;



int cclient(shared_ptr<cs457::tcpUserSocket> clientSocket,int id   )
{
    string user="";
    ssize_t value;
    string retmsg ="uno understand";
    ssize_t authval;
    //banner 
    string banner = login.getBanner();
    //check auth
    bool Authenticated = false;

    tie(user,value) = clientSocket.get()->recvString();
    
    while(!Authenticated){
        if(user.compare("guest") == 0 ){
            parser.Parse("/guest" , clientSocket, user , Authenticated);
            
        }
        else {
            string check = "please type your password: ";
            clientSocket.get()->sendString(check);
            tie(retmsg,authval) = clientSocket.get()->recvString();
            cout << "recieved messg" << retmsg << endl;
            string parsestring = "/user " + retmsg;
            cout << "send  to parser: " << parsestring << endl;
            parser.Parse(parsestring , clientSocket, user , Authenticated);
        }

    }
    
    clientSocket.get()->sendString(banner);

    cout << "Waiting for message from Client Thread" << id << std::endl;
    string msg;
    ssize_t val;
    bool cont =true ;  
    while (cont) 
    {
        tie(msg,val) = clientSocket.get()->recvString();
        parser.Parse(msg , clientSocket, user , cont);
       
        cout << "[SERVER] The user "<< user<< " is sending message " << msg << " -- With value return = " << val << endl;
        string s =  "[SERVER REPLY] The client " + user  + " is sending message:" + msg  + "\n"; 
        thread childT1(&cs457::tcpUserSocket::sendString,clientSocket.get(),s,true);
        //thread childT2(&cs457::tcpUserSocket::sendString,clientSocket.get(),msg,true);
        //thread childT3(&cs457::tcpUserSocket::sendString,clientSocket.get(),"\n",true);
        
        childT1.join();
        //childT2.join(); 
        //childT3.join(); 
        //clientSocket.get()->sendString(msg); 
        //clientSocket.get()->sendString("\n"); 
         if (msg.substr(0,6) == "SERVER")
        {
            thread childTExit(&cs457::tcpUserSocket::sendString,clientSocket.get(),"GOODBYE EVERYONE",false);
            thread childTExit2(&cs457::tcpUserSocket::sendString,clientSocket.get(),"\n",false);
            ready = false;   
            cont = false;   
            childTExit.join(); 
            childTExit2.join();
        }
        else
        {
            cout << "waiting for another message" << endl; 
        }
    }

    clientSocket.get()->sendString("goodbye"); 
    clientSocket.get()->closeSocket(); 
  
    return 1; 
}

int main(int argc, char * argv[])
{
   
    //used to check valid username and password
    parser.userPopulate();
    //fill chat rooms 
    parser.GetChatRooms();
    
    cout << "Initializing Socket" << std::endl; 
    cs457::tcpServerSocket mysocket(2000);
    cout << "Binding Socket" << std::endl; 
    mysocket.bindSocket(); 
    cout << "Listening Socket" << std::endl; 
    mysocket.listenSocket(); 
    cout << "Waiting to Accept Socket" << std::endl;
    int id = 0; 
    vector<unique_ptr<thread>> threadList;
   
  
    while (ready)
    { 
        shared_ptr<cs457::tcpUserSocket> clientSocket;
        int val; 
        tie(clientSocket,val) = mysocket.acceptSocket();
        cout << "value for accept is " << val << std::endl; 
        cout << "Socket Accepted" << std::endl; 
        unique_ptr<thread> t = make_unique<thread>(cclient,clientSocket,id); 
        threadList.push_back(std::move(t)); 
        
        id++; //not the best way to go about it. 
       // threadList.push_back(t); 
       
    
        
    }

    
    for (auto& t: threadList)
    {
        t.get()->join();
    }
    
        
    cout << "Server is shutting down after one client" << endl; 
    return 0; 
}