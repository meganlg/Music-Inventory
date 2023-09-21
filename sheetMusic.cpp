// Megan Gillen
// 08-30-2023
 
#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include "musicOrg.h"
using namespace std;

/*
* reads list sheet music from txt file
* organizes by alphabetical order in a binary search tree
* implements musicOrg class
*/

// insert the inventory details into musicOrg object
void readFile(musicOrg &object);

enum MENU {ROOT, HEIGHT, PRINT, FINDNAME, EXIT};

int main(){

    musicOrg BinaryTree;
    // read text file and insert data into BinaryTree object
    readFile(BinaryTree);

    // create menu loop for user to continue to enter an action until they want to quit
    bool quit = false;
    int task;
    MENU TASK;
    cout << "Welcome to your sheet music collection! Please select an option.\n\n";
    while(!quit){
        // have user enter what task they would like to do 
        cout << "What would you like to do next?" << endl << 
            "1. Print the information for the root node" << endl <<
            "2. Display the tree height" << endl <<
            "3. Display info for all items" << endl << 
            "4. Search for a specific title" << endl <<
            "5. Exit" << endl << endl;
        cout << "Enter a number: ";
        cin >> task;
        cout << endl;
        task --;
        TASK = static_cast<MENU>(task); // convert to enum

        string searchStr; // var to hold search string
        switch(TASK){
            case ROOT:
                BinaryTree.displayRoot();
                cout << endl;
                break;

            case HEIGHT:
                // wrapper function for treeHeightPrivate 
                BinaryTree.treeHeight();
                cout << endl;
                break;

            case PRINT:
                // wrapper function - runs displayTreePrivate
                BinaryTree.displayTree();
                cout << endl;
                break;
            
            case FINDNAME:
                // ask user what they would like to search for
                cout << "What title would you like to search for? : ";
                cin >> searchStr;
                BinaryTree.findName(searchStr);
                cout << endl;
                break;
            
            case EXIT:
                quit = true;
                break;

        }
    }

    return 0;
}


// inserts the inventory details from text file into object
void readFile(musicOrg &object){
    // open text file for reading
    ifstream inFile;
    inFile.open("sheetMusic.txt");

    // if error opening file
    if(!inFile){
        cout << "Error reading file.";
        exit(102);
    }

    int genre;
    int instrument;
    string name;

    // put data in binary tree
    while(!inFile.eof()){
        inFile >> genre >> instrument;
        inFile.ignore();
        getline(inFile, name);
        // put into object
        object.insert(genre, instrument, name);
    }

    inFile.close();
}