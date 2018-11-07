#pragma once

#include <string>
#include <vector>
#include <iostream>    
#include <sstream>
#include <algorithm>
#include <cctype>   

using namespace std;

class Parser{
    public:
        void Parse(string command); 

        bool DIE(vector <string> command);
        bool KILL(vector <string> command);
        bool HELP(vector <string> command);
        bool QUIT(vector <string> command);
        
    private:


};