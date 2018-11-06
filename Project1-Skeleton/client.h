#pragma once
#include <string>
using namespace std;

class client{
    public:
        inline client(string hostname, string username, int port): host(hostname), user(username), port(port){};


    private:
        string host = "";
        string user = "";
        int port;
        bool running = true;


};