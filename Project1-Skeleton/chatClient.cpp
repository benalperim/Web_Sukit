#include <iostream> 
#include "tcpClientSocket.h"
#include "Commands.h"
#include <thread> 
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>
#include <algorithm>
using namespace std;
//read the config file
vector <string> testFileCommands;

bool Setup(string configFile, string& hostName, string& userName, int & port){
    string type, data;
    string line;
    ifstream ifstr;
    ifstr.open(configFile);
    if(fopen(configFile.c_str(),"r") == NULL){return false;}
    while(getline(ifstr, line)){
        istringstream ss(line);
        ss >> type >> data;
        if(type == "Server"){
            hostName = data;
            cout << "host " << data << endl;
        }
        else if(type == "User"){
            userName = data;
            cout << "user: " << data << endl;
        }
        else if (type == "Port"){
            port = stoi(data);
            cout << "port: " << data << endl;
        }
    }
    return true;
}

/*vector<string> testFile(string testFile , vector<string> & commands){ //FIX THIS, its hard coded but i dont care
    ifstream ifstr;
    ifstr.open(testFile);
    string line;
    string com , arguments;
    vector <string> argumentsString;
   
    while(getline(ifstr, line)){
        istringstream ss(line);
        ss >> com >> arguments;
        commands.push_back(com);
        argumentsString.push_back(arguments);
    }
    for(unsigned int i = 0; i < commands.size(); i ++){
       if(commands[i] == "/Quit"){
           command.QUIT(argumentsString[i]);
       }
       else if(commands[i] == "/List"){
           command.LIST(argumentsString[i]);
       }
       else if(commands[i] == "/Join"){
           command.checkCommand(7, argumentsString[i]);
       }
       else if(commands[i] == "/Privmsg"){
           command.checkCommand(20, argumentsString[i]);
       }
    }
    ifstr.close();
}*/
bool readTestFile(string& testFile){
    ifstream ifstr;
    ifstr.open(testFile);
    if(ifstr.is_open()){
    string line;
    string command;
    while(getline(ifstr, line)){
        istringstream ss(line);
        ss >> command;
        testFileCommands.push_back(command);
    }
    return true;
    }
    else{return false;}
}

bool exitcondition  = true;
int Usage(char* arg0){
    cout << "When you are passing arguments please pass in the order of " << endl;
    cout << "-h hostname (if applicable) This is the IP address of the host, Default is set to 127.0.0.1" << endl; 
    cout << "-u username (if applicable) This is the Username you wish to be logged in as, Will be prompted if not given in later screen" << endl; 
    cout << "-p server port (if applicable) This is the port you with to take on the Server, Will be given a default if not specified" << endl; 
    cout << "-c configuarionfile (if applicable) please put the file under Web_Sukit folder or give absolute path as the argument" << endl;  
    cout << "-t testfile (if applicable) please put the file under Web_Sukit folder or give absolute path as the argument test file " << endl;  
    cout << "please pass at least 1 argument if not it will automatically setup everything with a guest user "<< endl;
    

    return -1;
}

void RecvMess(tcpClientSocket & socket){
   
    while(exitcondition){
        string msg;
            ssize_t v;
            tie(msg,v) =  socket.recvString(4096,true);
            if(v > 0){
                cout << "server said: " << endl;
                cout << msg <<endl;
            }

            if (msg == "goodbye"){break;}
           
    }
}



int main(int argc, char * argv[])
{
   
    vector<string> commands;
    string serverIP ="127.0.0.1";
    int port = 2000;
    string userName = "guest";
    string message ="no value passed";
    bool TEST = false;

    //cout << argv[1] << " "<< argv[2]<< endl;

    
    for(int i = 1; i <argc; i++){
        // get host
        if(strcmp(argv[i] , "-h") == 0){
            serverIP = argv[i + 1];
            cout << "host " << serverIP << endl;
        }
        // get user
        if(strcmp(argv[i] , "-u") == 0){
            userName = argv[i + 1];
            cout << "username " << userName << endl;
        }
        // get port
        if(strcmp(argv[i] , "-p") == 0){
            port  = stoi(argv[i + 1]);
            cout << "port " << port << endl;
        }
        //get config setup config 
         if(strcmp(argv[i] , "-c") == 0){
            cout << "config file passed " << argv[i+1] << endl;
            if(!Setup(argv[i + 1] , serverIP, userName, port)){
                return Usage(argv[0]);
            }
         }

        if(strcmp(argv[i] , "-t") == 0){
            cout << "test file passed " << argv[i+1] << endl;
            string filename = argv[i + 1];
            TEST = readTestFile(filename);
        }
        //get the command
        string fullcommand = "";
        if(argv[i][0] == '/'){
            //cout << "got a command  " << argv[i] << endl;
            //cout << "argc " << argc << endl;
            //cout << "argv " << i << endl;
            while(argc > i){
                fullcommand += argv[i];
                i++;
                
                if(i == argc){
                   break;
                }
                
                //cout << "argv " << i << endl;
                fullcommand += " ";
                //cout << "full command  " << fullcommand << endl;
                
                if( strcmp(argv[i] , "-p") == 0 || strcmp(argv[i] , "-h") == 0 ||strcmp(argv[i] , "-u") == 0
                 || strcmp(argv[i] , "-c") == 0  || strcmp(argv[i] , "-t") == 0 || argv[i][0] =='/')
                {
                    break;
                }
            }
            i --;
            cout << "command passed " << fullcommand << endl;
            commands.push_back(fullcommand);
            message = fullcommand;
        }
   
    }
     
      
    string exit = "/quit";
    //THREAEEEAD

    cout << "Starting client example" <<endl; 
    

    tcpClientSocket clientSocket(serverIP,port);
    
    int val = clientSocket.connectSocket();
    clientSocket.sendString(userName,false);
    //sleep(1);
 
    if(TEST){
        string testMsg;
        ssize_t testValue;

        for(unsigned int i = 0; i < testFileCommands.size(); i++){
            sleep(1);
            clientSocket.sendString(testFileCommands[i], false);
            tie(testMsg, testValue) = clientSocket.recvString(4096, true);
        }
        /*cout << "Sending password: " <<testFileCommands[0] << endl;
        clientSocket.sendString(testFileCommands[0],false); //sends password but never gets there 
        cout << "recieving Message: " << endl;
        tie(testMsg,testValue) =  clientSocket.recvString(4096,true);
        sleep(3);
        
        

        for(unsigned int i = 1; i < testFileCommands.size(); i++){
            sleep(1);
            cout << "SENDING: " << testFileCommands[i] << endl;
            clientSocket.sendString(testFileCommands[i],false);
            cout << "RECIEVING: " << endl;
            tie(testMsg,testValue) =  clientSocket.recvString(4096,true);
        }*/
    }
     
    
    cout << "Client Socket Value after connect = " << val << endl;
    
    thread child1(RecvMess,  ref(clientSocket));
    while (true){
    
        getline(cin, message);

        clientSocket.sendString(message,false);
        
        if(message.length() >= 5){
            string hokuspokus = message.substr(1,4);
           
            transform(hokuspokus.begin(), hokuspokus.end(), hokuspokus.begin(), ::tolower);
        
            if(hokuspokus.compare("quit") == 0){
               
                exitcondition = false;
                break;
            }
        }               
    }
    
    child1.join();
    return 0; 
}