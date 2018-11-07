#include "Parser.h"

void Parser::Parse(string command){
    if(command.at(0) == '/'){  
        istringstream tokenStream(command);
        vector<string> tokens;
        string token;
        char space = ' ';
        while (getline(tokenStream, token, space)){
            if(token.at(0)== '/'){
                transform(token.begin(), token.end(), token.begin(), ::tolower);
            }
            tokens.push_back(token);
        }


        if(tokens[0] == "/quit"){
            QUIT(tokens);
        }

         if(tokens[0] == "/info"){
            INFO(tokens);
        }

         if(tokens[0] == "/help"){
            HELP(tokens);
        }
    }
}