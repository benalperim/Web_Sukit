#pragma once 
#include <string>
#include <iostream>
#include <vector>

namespace cs457
{
    using namespace std;
    
        class Login
        {
            public:
            string getBanner();
            bool bannedUser(string&);
            vector<string> userFileCopy();
            bool checkUserName(string&);
            void addUserName(string&, string&, string&);
            private:
        };
    
}