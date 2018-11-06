#include "Login.h"
#include <iostream>
#include <fstream>
#include <sstream>
#include <string>

using namespace std;

string getBanner(){ //returns a string of the banner to send after authentication
    string banner = "";
    string line;
    while(getline(ifstream("banner.txt"), line)){
        banner += line + "\n";
    }
    return banner;
}

bool bannedUser(string& userName){ //checks to see if the username is within the banned list. Returns True if user is banned, false elsewise
    string line;
    while(getline(ifstream("banusers.txt"), line)){
		if (line.find(userName) != string::npos ){
			return true;
		}
	}
    return false;
}

vector<string> userFileCopy(){ //helper function for checkUserName (needed to split individual lines into components. that is why can just ifstream the file) //THIS IS BAD CODING (WRITE AFTER YOU CLOSE SERVER READ WHEN YOU START UP SERVER)
    vector<string> copy;
    ifstream ifstr;
    ifstr.open("users.txt");
    string line;

    while(getline(ifstr, line)){
        copy.push_back(line);
    }
    ifstr.close();
    return copy;
}

bool checkUserName(string& userName){ //checks to see if the username is taken by somebody else in the system. Returns True if username already taken , false elsewise
    vector<string> copy = userFileCopy();  
    for(unsigned int i = 0; i < copy.size(); i++){
        string temp = copy[i];
        istringstream ss(temp);
        string username;
        ss >> username;
        if(username == userName){
            return true;
        }
    }
    return false;
}



void addUserName(string& userName, string& password, string& level){ //Makes a string of all the info to append to the end of the file (flagged by the app) writes to the file the line
    string info = userName + " " + password + " " + level + " false";
    ofstream myfile("users.txt",  ios::out | ios::app);
    myfile << info;
    
}



vector<string> testFileCopier(string& testFile){
    vector<string> testFileCopy;
    ifstream ifstr;
    ifstr.open(testFile);
    string line;

    while(getline(ifstr, line)){
        testFileCopy.push_back(line);
    }
    ifstr.close();
}