#include <iostream> 
#include "tcpClientSocket.h"
#include "client.h"
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

vector<string> testFile(string testFile , vector <string> & commands){
    
    ifstream ifstr;
    ifstr.open(testFile);
    string line;

    while(getline(ifstr, line)){
        commands.push_back(line);
    }
    ifstr.close();
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
   
    vector <string> commands;
    string serverIP ="127.0.0.1";
    int port = 2000;
    string userName = "guest";
    string message ="no value passed";



    
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
            port  = stoi(argv[i +1 ]);
            cout << "port " << port << endl;
        }
        //get config setup config 
         if(strcmp(argv[i] , "-c") == 0){
            cout << "config file passed " << argv[i+1] << endl;
            if(!Setup(argv[i + 1] , serverIP, userName, port)){
                return Usage(argv[0]);
            }
         }

        if(argv[i] == "-t"){
            cout << "test file passed " << argv[i+1] << endl;
            testFile(argv[i + 1], commands);
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