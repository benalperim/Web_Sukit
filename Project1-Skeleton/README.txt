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
    Example: 


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
    
    .cpp/.h:
        chatClient(.cpp)
            -
        client(.h)
            -
        clientdriver(.cpp)
            -
        Commands(.cpp/.h)
            -
        driver(.cpp)
            -
        Login(.cpp/.h)
            -
        tcpClientSocket(.cpp/.h)
            -
        tcpServerSocket(.cpp/.h)
            -
        tcpUserSocket(.cpp/.h)
            -
        userObject(.h)
            -
        utils(.h)
            -
        
    other:
        Makefile
            - 
        run
            -
        .gitignore
            - includes files to ignore for our git repository


----------------------------------------
Design Decisions and Issues
----------------------------------------

