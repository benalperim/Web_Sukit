#include "Login.h"
#include "userObject.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string Login::getBanner( ){ //returns a string of the banner to send after authentication
    string banner = "";
    ifstream ifstr;
    ifstr.open("banner.txt");
    string line;
    while(getline(ifstr, line)){
        banner += line + "\n";
    }
    return banner;
}





void Login::addUserName(string& userName, string& password){ //Makes a string of all the info to append to the end of the file (flagged by the app) writes to the file the line
    if(password.length() == 0){password = "@";}
    size_t found = password.find('@');
    if(found != string::npos){cout << "Cannot have @ sign in password";}
    else{
    string info = userName + " " + password + " " + "user" + " false";
    ofstream myfile("users.txt",  ios::out | ios::app);
    myfile << info;
    }
    
}

/*int main(int argc, char * argv[])
{
    Login login;
    cout << login.getBanner() << endl;;
    login.userPopulate();
    return 0;
}*/