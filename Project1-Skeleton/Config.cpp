#include "Config.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

bool Setup(string configFile, string& hostName, string& userName, int port){
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
        }
        else if(type == "User"){
            userName = data;
        }
        else if (type == "Port"){
            port = stoi(data);
        }
    }
    return true;
}

/*int main(int argc, char * argv[])
{
    string configFile = argv[1];
    string hostName = argv[2];
    string userName = argv[3];
    int port = stoi(argv[4]);
    Setup(configFile, hostName, userName, port);
    return 0;
}*/