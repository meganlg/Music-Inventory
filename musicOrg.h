// Megan Gillen
// 08-30-2023

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
using namespace std;

#ifndef musicOrg_H
#define musicOrg_H  

/*
* Organizes and stores sheet music, includes search function and filtering
*/

class musicOrg{
    private:
        struct musicTree{ string genre; string instrument; string name; musicTree *left; musicTree *right;};
        musicTree *root;
        // used in destructor
        void destroyTree(musicTree *nodePtr);
        // private function for insert
        void insertPrivate(musicTree *newNode, musicTree *&nodePtr);
        void displayTreePrivate(musicTree *nodePtr) const;
        int treeHeightPrivate(musicTree *nodePtr) const;
        // search for first instance of string in each title
        void findNameSearch(bool &found, string name, musicTree *nodePtr);

    public:
        // constructor
        musicOrg(){
            root = nullptr;
        }
        // destructor
        ~musicOrg(){
            destroyTree(root);
        }
        // display information of the root
        void displayRoot();
        // insert new node
        void insert(int genreInt, int instrumentInt, string name);
        // wrapper for findNameSearch
        void findName(string name);
        // wrapper for treeHeightPrivate 
        void treeHeight() const{
            cout << "Tree height: " << treeHeightPrivate(root) << endl;
        }
        // wrapper for displayTreePrivate
        void displayTree() const{
            // table headings
            cout << setw(15) << "Genre:" << setw(15) << "Instrument:" << setw(25) << "Title:" << endl;
            displayTreePrivate(root);
        }

};

#endif