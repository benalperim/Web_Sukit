#include <iostream> 
#include "tcpClientSocket.h"
#include "client.h"
#include <thread> 
#include <stdio.h>
#include <string.h>
#include <vector>
#include <fstream>
#include <sstream>

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



int Usage(char* arg0){
    cout << "When you are passing arguments please pass in the order of " << endl;
    cout << "-h hostname (if applicable) " << endl; 
    cout << "-u username (if applicable) " << endl; 
    cout << "-p server port (if applicable) " << endl; 
    cout << "-c configuarionfile (if applicable) please put the file under Web_Sukit folder or give absolute path as the argument" << endl;  
    cout << "-t please put the file under Web_Sukit folder or give absolute path as the argument test file " << endl; 
    cout << "Commands or messages  to send at the end." << endl; 
    cout << "please pass at least 1 argument "<< endl;
    cout << "if there are only commands or messages put as argument it will follow the simple config setup"<< endl;

    return -1;
}

void RecvMess(client & Client , tcpClientSocket & socket){
    while(true){
        string msg;
            ssize_t v;
            tie(msg,v) =  socket.recvString(4096,true);
            if(v > 0){
                cout << "server said: " << msg << endl;
            }
           
    }
}



int main(int argc, char * argv[])
{
    vector <string> commands;
    string serverIP ="127.0.0.6";
    int port = 2040;
    string userName = "AlperDaddy";
    string message ="no value passed";
    if(argc < 2){return Usage(argv[0]);}
    
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
        }
   
    }
     
      
        

  
    //int ready  = 1;
    cout << "Starting client example" <<endl; 
    client Client(serverIP ,userName, port );

    tcpClientSocket clientSocket(serverIP,port);
    int x = 1;
    int val = clientSocket.connectSocket(); 
    cout << "Client Socket Value after connect = " << val << endl; 
    while (x == 1){
        cout << "enter a command: "; 
        
        clientSocket.sendString(message,false);
        x= 2;        

        
        
        
        
    }
    

    clientSocket.sendString(message,false); 
    //THREAEEEAD
    thread child1(RecvMess, ref(Client), ref(clientSocket));

    cout << "Client will try to exit now" <<endl;

    

    //tie(msg,v) =  clientSocket.recvString(4096,false);
    //g++-8 -g tcpClientSocket.cpp chatClient.cpp client.cpp -std=c++11 -pthread -o chatClient.out && ./chatClient.out


    
    child1.join();
    return 0; 
}