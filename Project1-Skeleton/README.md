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
        runClient (For Admin registered account)
        runClient2 (For non-Admin registered account)
        runGuest (For Guest account)
    Test: 
        runClientTest

----------------------------------------
Command line arguments
----------------------------------------
    The compile files (run, runClient, runGuest, runClientTest_) should handle anything needed with the command line, however if you compile and run yourself, it should handle any variation from the client side. 

    the Client options are:

        -h hostname
            ~ the IP address of the host you're connecting to, 127.0.0.1 is default. 
        -p port
            ~ the port number of the host you're trying to go through, 2000 is default.
        -u username
            ~ username you want to connect as, guest is defualt.
        -t testfile
            ~ uses test files to call a command. This will spawn 4 different terminals, automatically testing (when turning in) help, info, list, and quit.


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
        chatUser(.h)
            - This is an object that is similar to userObject, minus the socket tied to it. (graveyard)
        client(.h)
            - Contains the necessities for a client, including a way to store hostname, username, and port number
        Commands(.cpp/.h)(graveyard)
            - Contains a switch statement with every chat command that we should implement.  It switches on an integer value assigned to it in both the server and the client. 
              Holds values that are used by these commands as well, such as our chatRoom storage.
        driver(.cpp)
            - This is the driver for the server of our chat application.  This will run/create clients for every client spawned along with threading each socket. 
        Login(.cpp/.h)(mostly graveyard)
            - This file contains a way to check and authenticate users, along with writing new users to users.txt file.  While authenticating it will check if the indiviudal username is on the 
              banned user list of banusers.txt.  Lastly this file contains the IO to be able to read and print out our banner from banner.txt
        Parcer(.cpp/.h)
            - This file parses the command given along with handling the arguments for each command.  This is the new and approved version of Commands.* due to the issue of parsing before instead of after.  most of the functions from Login.* and Command.* is made into this function.
        tcpClientSocket(.cpp/.h)
            - This file was one of the provded files that is the old version of of the tcpUserSocket.
        tcpServerSocket(.cpp/.h)
            - This file was one of the provided files that contains methods to spawn a socket for the server.  Has methods to set the socket options, to bind the socket, to listen for connections, and accepting connection requests.     
        tcpUserSocket(.cpp/.h)
            - This file was one of the provided files that contains methods to spawn a socket for the client. Has methods to open and close the given socket, along with methods to send and recieve strings on the given socket.
        userObject(.h)
            - This is an object file that creates and object name userObject, that contains the contents of the users.txt file.  Each object holds the username, password, their socket ,level of permission, and if they are banned or not. 
        utils(.h)
            - This file was one of the provided files that contains a singular method to be able to round up to the nearest multiple of a number.
        
    other:
        runClient
            - compiles and runs a client with the Admin JakeBaby
        runGuest
            - compiles and runs a client with no user specification therefore defaulted to a unique guest
        runClientTest_
            - compiles and runs a client with the corresponding testfile
        run
            - compiles and runs the Server
        .gitignore
            - includes files to ignore for our git repository


----------------------------------------
Design Decisions and Issues
----------------------------------------

    We were able to implement the following commands:
        -/QUIT
            - Allows the client to quit their session within the server.
        -/HELP
            - Displays a list of commands that we have implemented during the sessions 
        -/DIE
            - Allows an Admin to shut down the server, notifying all the clients that s/he has done so.
        -/PRIVMSG
            - Allows two users to message privately between one another
        -/JOIN
            - Allows a user to join a Channel in order to talk to others inside that channel. You can only be in one chat room at one time.
        -/INFO
            - Displays info on the creaters of the chatting application.
        -/LIST
            - Displays the information on which channels are on the server, what their topic is, and if they require a password.
        -/RULES
            - Displays the rules for the server.
        -/TIME
            - Displays the local time for the user who requested it.
        -/VERSION
            - Displays the version of the current running server.
        


        -/Guest & /User
            - this is a project design, allowing us to differentiate between a guest and a registered user.

    We purposely left the SERVER REPLY funciton in order to identify what you typed to the server, and if the server was responding.

    -One of the issues we have right now, we do not check for the same user. So do not try to runClient more than once. We have runClient and runClient2 if you want to run mutliple clients (it will work, however it will break when it comes to chat rooms).  Running runGuest multiple times will not throw an error because we append an individual number to each guests name. We do not know how to compare TcpUserSockets.