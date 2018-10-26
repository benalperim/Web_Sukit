
#include "client.h"
#include "tcpUserSocket.h"
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 
using namespace std;




int main(int argc, char * argv[]){

    if (argc != 4){
        std::cout <<"Not enough arguments passed" << std::endl;
    }

   

    connect( sockfd, const struct sockaddr *addr, socklen_t addrlen);

    
}

MAIN(){

   int gate_n = 6666;
   int main_socket, ds_sock, ds_sock_bis;
   struct sockaddr client;
   int main_socket_bis, dim;
   char buff[BUFF_SIZE];
   char buffer_nome_file[F_NAME_L];
   int ret, status;
   dim = sizeof(client);  
   main_socket = INIT_SOCKET(gate_n); 
   dim = sizeof(client);
   cout << "Waiting for connections..........\n";   
   while(1) {
      main_socket_bis = accept(main_socket, &client, &dim);
      while(accept(main_socket, &client, &dim)) == -1);
      cout << "Conenction established!\n";