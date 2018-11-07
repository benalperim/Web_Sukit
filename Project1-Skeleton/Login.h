#pragma once 
#include <string>
#include <iostream>
#include <vector>
#include "userObject.h"

using namespace std;
    
    class Login
    {
        public:
        string getBanner();
        bool bannedUser(string&);
        void userPopulate();
        bool validateUser(string&, string&);
        void addUserName(string&, string&);

            
        private:
        vector<userObject> userList;
        };
    
