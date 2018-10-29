
CC = g++
CFLAGS = -Wall -c		#compiler flags
LFLAGS = -Wall			#linkflags
OBJS = chatClient.o tcpClientSocket.o
INCLUDE = -I.
clientServer : $(OBJS)
	$(CC) $(OBJS) $(INCLUDE) $(LFLAGS) -o clientServer 

chatClient.o :chatClient.cpp tcpClientSocket.h
	$(CC) chatClient.cpp $(INCLUDE) $(CFLAGS)

tcpClientSocket.o : tcpClientSocket.cpp tcpClientSocket.h
	$(CC) tcpClientSocket.cpp $(INCLUDE) $(CFLAGS)

clean :
	-rm *.o clientServer
