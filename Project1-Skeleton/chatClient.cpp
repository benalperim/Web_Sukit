#include <iostream> 
#include "tcpClientSocket.h"
#include <thread> 
#include <tuple> 
#include <vector> 
#include <string>
using namespace std; 

int main(int argc, char * argv[])
{

    cout << "Starting client example" <<endl; 
    string serverIP(argv[1]);
    int port = stoi(argv[3]);
    int ready  = 1;
    vector<unique_ptr<thread>> threadList;
    string msg;
    size_t v;

    

    cs457::tcpClientSocket clientSocket(serverIP,port);
    int val = clientSocket.connectSocket(); 
    cout << "Client Socket Value after connect = " << val << endl;
    string line;
    
    while (ready){
        cout << "enter a command: "; 
        getline(cin, line);
        clientSocket.sendString(line,false); 
        tie(msg,v) =  clientSocket.recvString(4096,false);

        cout << "server said: " << msg << endl;
        
        
        
    }
    
    return 0; 
}