#include<iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include "splay.h"
#include "login.h"
#include "workspace.h"
#include "crypt.h"

using namespace std;

typedef unordered_map<string, pair<string, SplayTree<string, int>>> Portal;
Portal logins;

int main(int argc, char *argv[]){
    if(argc > 1){                                                                           //reads in file if provided
        string line;
        ifstream ifile(argv[1]);
        while(getline(ifile, line)){
            stringstream ss(line);
            string uname;
            string pword;
            ss >> uname;
            ss >> pword;
            pword = encrypt(pword);
            logins.insert({uname, {pword, SplayTree<string, int>()}});                      //creates database of users
            string filename;
            while(ss >> filename){                                                          //creates each user's personal file database if files exist
                logins.find(uname)->second.second.insert({filename, 0});
            }
        }
        ifile.close();
    }
    if(logins.empty()){                                                                     //prompts user to create new account if no users exist
        string logged = createuser();
        activity(logged);
    }
    while(true){
        cout << "Login or create new user: \n1 - Login \n2 - Create new user\n";            //prompts user to either log in or to create an account
        string choice;
        cin >> choice;
        if(choice == "1"){                                                                  //logs into existing account
            string logged = existinguser();
            if(!logged.empty()){  
                activity(logged);
            }
        }
        else if(choice == "2"){
            string logged = createuser();                                                   //creates new account
            activity(logged);
        }
        else{
            cout << "Exiting..." << endl;                                                   //any invalid input will result in exiting program 
            break;
        }
    } 
    cout << endl;
    ofstream ofile(argv[1]);    
    Portal::iterator mapit;
    for(mapit = logins.begin(); mapit != logins.end(); ++mapit){                            //updates info file with any changes to new users and user activity
        ofile << mapit->first << ' ' << decrypt(mapit->second.first) << ' ';
        SplayTree<string, int>::iterator it;
        for(it = mapit->second.second.begin(); it != mapit->second.second.end(); ++it){
            ofile << it->first << ' ';
        }
        ofile << endl;
    }
    ofile.close();
    return 0;
}

