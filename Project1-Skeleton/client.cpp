#include "client.h"


int cs457::client::INIT_SOCKET(int port_number, string hostname) {
	int my_socket;
	
	cout << "Socket building.......................\n";
	my_socket = socket(AF_INET, SOCK_STREAM, 0);      
	if (my_socket == -1)  {                           
        perror("AAAAAA !!!!! SOCKET ERROR BUILDING OCCURRED!!! Probably another socket is using this port.\n");
  		exit(-1);
    }
	cout << "Socket built!!!\n";
    cout << "I am initializing the socket...\n";
	clientSocket.sin_family = AF_INET;                      
	clientSocket.sin_port = port_number;                    
	clientSocket.sin_addr.s_addr = inet_addr(hostname.c_str());                
 
	cout << "Socket initialization COMPLETED...!\n";
	
	return(my_socket);          
}



socklen_t cs457::client::getLenghtPointer()
{
    socklen_t len = sizeof(clientSocket);  
    return len;
}


struct sockaddr * cs457::client::getAddressPointer()
{
    return ((struct sockaddr *) &clientSocket);
}