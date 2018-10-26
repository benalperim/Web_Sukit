
#include "client.h"
#include "tcpUserSocket.h"
#include <iostream>
#include <stdio.h> 
#include <sys/socket.h> 
#include <stdlib.h> 
#include <netinet/in.h> 
#include <string.h> 

using namespace std;




int main(int argc, char * argv[]){
    cs457::client client;
    if (argc != 4){
        cout <<"Not enough arguments passed" << endl;
    }
    string hostAddress = argv[1];
    string username = argv[2];
    int port = stoi(argv[3]);
    int client_Sukit = client.INIT_SOCKET(port , hostAddress);
   

    connect( client_Sukit, client.getAddressPointer()  ,client.getLenghtPointer());

    
}




// MAIN(){

//    int gate_n = 6666;
//    int main_socket, ds_sock, ds_sock_bis;
//    struct sockaddr client;
//    int main_socket_bis, dim;
//    char buff[BUFF_SIZE];
//    char buffer_nome_file[F_NAME_L];
//    int ret, status;
//    dim = sizeof(client);  
//    main_socket = INIT_SOCKET(gate_n); 
//    dim = sizeof(client);
//    cout << "Waiting for connections..........\n";   
//    while(1) {
//       main_socket_bis = accept(main_socket, &client, &dim);
//       while(accept(main_socket, &client, &dim)) == -1);
//       cout << "Conenction established!\n";