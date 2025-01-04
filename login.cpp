#include<unordered_map>
#include "splay.h"
#include "login.h"
#include "crypt.h"

using namespace std;

typedef unordered_map<string, pair<string, SplayTree<string, int>>> Portal;
extern Portal logins;

//checks validity of password within five attempts
int checkpword(string user){
    int attempts = 1;
    while(true){
        cout << "Password: ";
        string pword;
        cin >> pword;
        pword = encrypt(pword);                                         //encrypts password
        if(attempts > 4){                                               //too many incorrect attempts
            return attempts;
        }
        if(logins.find(user)->second.first != pword){                   //wrong password
            cout << "Wrong password" << endl;
            attempts++;
        } 
        else{
            cout << endl << "Login successful" << endl << endl;         //successful log in
            return 0;
        }
    }
}

//logs into existing account
string existinguser(){
    string uname;
    while(true){
        cout << "Username: ";
        cin >> uname;
        if(logins.find(uname) == logins.end()){                             //checks to see there is an existing account with that username
            cout << "User not found" << endl << endl;
        } else{
            int n = checkpword(uname);                                      
            if(n != 0){                                                     //returns empty string if number of incorrect password attempts exceeds five
                return "";
            }
            return uname;                                                   //returns username if password is correct
        }
    }
}

//creates a new account
string createuser(){                                                        
    string uname;
    while(true){
        cout << "Choose username: ";
        cin >> uname;
        if(logins.find(uname) != logins.end()){                             //checks that user's input is an unique username
            cout << "Username taken" << endl << endl;
        } else {
            cout << "Choose password: ";
            string pword;
            cin >> pword;
            pword = encrypt(pword);
            logins.insert({uname, {pword, SplayTree<string, int>()}});      //creates new account with chosern username and password combo
            cout << "User created" << endl << endl;
            return uname; 
        }
    }
}
