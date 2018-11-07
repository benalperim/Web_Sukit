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

bool Login::bannedUser(string& userName){ //checks to see if the username is within the banned list. Returns True if user is banned, false elsewise
    string line;
    ifstream ifstr;
    ifstr.open("banusers.txt");
    while(getline(ifstr, line)){
		if (line.find(userName) != string::npos ){
			return true;
		}
	}
    return false;
}

void Login::userPopulate(){ //Call this upon start of SERVER
    ifstream ifstr;
    ifstr.open("users.txt");
    string line;
    string username, password, level, banned;

    while(getline(ifstr, line)){
        userObject tempObj;
        istringstream ss(line);
        ss >> username >> password >> level >> banned;
        tempObj.userName = username;
        tempObj.password = password;
        tempObj.level = level;
        tempObj.banned = banned;
        userList.push_back(tempObj);
    }
    ifstr.close();
    
}

bool Login::validateUser(string& username, string& password){ //checks to see if the username is taken by somebody else in the system. Returns True if username already taken , false elsewise 
    if(bannedUser(username)){cout << "Banned User: "<< username << endl; return false;}
    for(unsigned int i = 0; i < userList.size(); i++){
        string uName = userList[i].userName;
        if(username == uName){ //Username is in list, check the password
            string uPass = userList[i].password;
            if(password == uPass){ //password is correct
            return true;
            }
            else{return false;} //password is incorrect
        }
    }
    return false;
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