#include "tcpUserSocket.h"
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 



namespace cs457{
    using namespace std;
    class client {
     
    
        public: 
            //setup  connection to the driver
            int INIT_SOCKET(int port_number, string hostname);
            struct socklen_t getLenghtPointer();
            struct sockaddr * getAddressPointer()

        private:
            struct sockaddr_in client; 
        }
}

