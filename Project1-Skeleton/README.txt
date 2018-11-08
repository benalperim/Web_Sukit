----------------------------------------
Chat Project 1
----------------------------------------
    By: Alper karslioglu & Jacob Tancher

----------------------------------------
Compile
----------------------------------------
    Server:
        run 
    Client:
        runClient


----------------------------------------
Command line arguments
----------------------------------------
    The compile files should handle anything needed with the command line, however if you compile and run yourself, it should handle any variation from the client side. 

    the Client options are:

        -h hostname
            ~ the IP address of the host you're connecting to, 127.0.0.1 is default. 
        -p port
            ~ the port number of the host you're trying to go through, 2000 is default.
        -u username
            ~ username you want to connect as, guest is defualt.
        -t testfile
            ~ uses test files to call a command.


----------------------------------------
File List
----------------------------------------
    .txt:
        banner
            - Contains the text for the 'WELCOME' banner that is displayed when users are authenticated and logged onto the server
        banusers
            - Contains the list of usernames (which are unique) that are banned from using the Chat application
        Config
            - Contains the default configuration of the client if the parameters are not passed in the command line
        users
            - Contains the list of users (unique), passwords(@ sign if no password), level of permission (user, Admin, sysop), and ban status (true or false)
                ~Example: David myp4ssw0rd user false
        testFile_.txt
            - After running the server, these create clients using the different parameters running different commands
    
    .cpp/.h:
        chatClient(.cpp)
            - This file initiates a client, creates a socket inbetween the server and the client.  Send and recieves messages from and to the server.  The recieve is threaded so it can recieve multiple messages.
        client(.h)
            - Contains the necessities for a client, including a way to store hostname, username, and port number
        Commands(.cpp/.h)
            - Contains a switch statement with every chat command that we should implement.  It switches on an integer value assigned to it in both the server and the client. 
              Holds values that are used by these commands as well, such as our chatRoom storage.
        driver(.cpp)
            - This is the driver for the server of our chat application.  This will run/create clients for every client spawned along with threading each socket. 
        Login(.cpp/.h)
            - This file contains a way to check and authenticate users, along with writing new users to users.txt file.  While authenticating it will check if the indiviudal username is on the 
              banned user list of banusers.txt.  Lastly this file contains the IO to be able to read and print out our banner from banner.txt
        tcpClientSocket(.cpp/.h)
            - This file was one of the provided files that contains methods to spawn a socket for the client. Has methods to open and close the given socket, along with methods to send and recieve strings on the given socket.
        tcpServerSocket(.cpp/.h)
            - This file was one of the provided files that contains methods to spawn a socket for the server.  Has methods to set the socket options, to bind the socket, to listen for connections, and accepting connection requests.              
        tcpUserSocket(.cpp/.h)
            - ASK ALPER IM NOT QUITE CERTAIN WHAT THIS FILE DOES 
        userObject(.h)
            - This is an object file that creates and object name userObject, that contains the contents of the users.txt file.  Each object holds the username, password, level of permission, and if they are banned or not. 
        utils(.h)
            - This file was one of the provided files that contains a singular method to be able to round up to the nearest multiple of a number.
        
    other:
        Makefile
            - compiles the clients code, to run a client see above (command line)
        run
            - compiles and runs the Server.
        .gitignore
            - includes files to ignore for our git repository


----------------------------------------
Design Decisions and Issues
----------------------------------------

    PUT DECISIONS AND ERRORS HERE