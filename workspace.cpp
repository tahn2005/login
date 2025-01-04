#include <unordered_map>
#include <iostream>
#include <fstream>
#include "splay.h"
#include "workspace.h"

using namespace std;

typedef unordered_map<string, pair<string, SplayTree<string, int>>> Portal;
extern Portal logins;

//interface that allows for users to find, add, and delete files
void activity(string uname){
    Portal::iterator it = logins.find(uname);
    while(true){
        cout << "1. Find file\n2. Add file\n3. Delete file\n";
        string option;
        cin >> option;
        if(option == "1"){                                                                  //finds existing file in database given file name
            cout << "Enter filename: ";
            string file;
            cin >> file;
            SplayTree<string, int>::iterator itx = it->second.second.find(file);
            if(itx != it->second.second.end()){
                cout << "Edit file? \n1. Yes \n2. No\n";
                string n;
                cin >> n;
                if(n == "1"){
                    cout << "Opening file..." << endl;
                    work(file);
                }
            }
            else{
                cout << "File does not exist" << endl;
            }
        }
        else if(option == "2"){                                                             //creates and adds new file to user database
            cout << "Enter filename: ";
            string file;
            cin >> file;
            it->second.second.insert({file, 0});
            ofstream nfile(file);
            nfile.close();
            cout << "Edit file? \n1. Yes \n2. No\n";
            string n;
            cin >> n;
            if(n == "1"){
                cout << "Opening file..." << endl;
                work(file);
            }
        }
        else if(option == "3"){                                                             //removes file from current user database
            cout << "Enter filename: ";
            string file;
            cin >> file;
            it->second.second.remove(file);
            cout << "File deleted" << endl;
        }
        else{                                                                               //any invalid user input results in logging out of account
            cout << "Logging out..." << endl << endl;
            return;  
        }
    }
}

//interface allowing users to edit and/or overwrite files
void work(string filename){
    while(true){
        cout << "1. add to file \n2. overwrite file\n";
        string option;
        cin >> option;
        if(option == "1"){                                                                  //appending file
            string add;
            cin.ignore();
            getline(cin, add);
            ofstream file(filename, ios::app);
            file << add;
            file.close();
            cout << "end" << endl;
        }
        else if(option == "2"){                                                             //overwrites contents of file
            string add;
            cin.ignore();
            getline(cin, add);
            ofstream file(filename);
            file << add;
            file.close();
            cout << "end2" << endl;
        }
        else{                                                                               //invalid input returns user outside of file
            cout << "Exiting file..." << endl << endl;
            return;
        }
    }
}