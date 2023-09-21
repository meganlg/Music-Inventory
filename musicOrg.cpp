// Megan Gillen 
// 08-30-2023

#include <iostream>
#include <string>
#include <iomanip>
#include <fstream>
#include <algorithm>
#include <cctype>
#include "musicOrg.h"
using namespace std;

const string translateGen[5] = {"Christmas", "Wedding", "Church", "Duet", "Solo"};
const string translateInst[3] = {"Piano", "Cello", "Guitar"};


// destroys BST
void musicOrg::destroyTree(musicTree *nodePtr){
    // if nodePtr is not null, then move to the left and right trees
    if(nodePtr != nullptr){
        if(nodePtr->left){
            destroyTree(nodePtr->left);
        }
        if(nodePtr->right){
            destroyTree(nodePtr->right);
        }
        // delete current node
        delete nodePtr;
    }
}


// private function for insert - inserts a new node to the tree
void musicOrg::insertPrivate(musicTree *newNode, musicTree *&nodePtr){
    // if the current branch is null, insert the new node
    if(!nodePtr){       
        nodePtr = newNode;
    }
    // if the new node name is less than current branch name it should go to the left sub-branch
    else if(newNode->name < nodePtr->name){   
        insertPrivate(newNode, nodePtr->left);
    }
    else{ // else the newNode name will either be greater than or equal to the nodePtr name, and should go to the right
        insertPrivate(newNode, nodePtr->right);
    }
}


// inserts information into a new node
void musicOrg::insert(int genreInt, int instrumentInt, string name){
    // create new node and allocate space
    musicTree *newNode;
    newNode = new musicTree;

    // assing values and set left and right to null
    newNode->genre = translateGen[genreInt];
    newNode->instrument = translateInst[instrumentInt];
    newNode->name = name;
    newNode->left = nullptr;
    newNode->right = nullptr;

    // insert the node through the private insert function which finds the correct spot
    insertPrivate(newNode, root);
}


// private function for displaying the tree - displays in order
void musicOrg::displayTreePrivate(musicTree *nodePtr) const{
    // if nodePtr is not null, recursively call left branch, display current node, then call right branch
    if(nodePtr){
        displayTreePrivate(nodePtr->left);
        cout << setw(15) << nodePtr->genre << setw(15) << nodePtr->instrument << setw(25) << nodePtr->name << endl;
        displayTreePrivate(nodePtr->right);
    }
}


// displays information of the root
void musicOrg::displayRoot(){
    // display contents of the root node
    cout << "Information for root node:\n";
    cout << "Genre: " << root->genre << endl;
    cout << "Instrument: " << root->instrument << endl;
    cout << "Title: " << root->name << endl;
}


// private function for displaying the current height of the tree
int musicOrg::treeHeightPrivate(musicTree *nodePtr) const{
    // if nodeptr is not null
    if(nodePtr){
        // left variable to hold recursive call to the left branch
        // right vairable to hold the same
        int left, right = 0;
        left = treeHeightPrivate(nodePtr->left) +1;
        right = treeHeightPrivate(nodePtr->right) + 1;
        // if the left variable counted more branches
        if(left>right){
            return left;
        }
        else{
            return right;
        }
    }
    // base case
    else{
        return 0;
    }
}


// search function - uses .find to find the first instance of the string in each title
// displays every title that includes the search string
void musicOrg::findNameSearch(bool &found, string name, musicTree *nodePtr){

    // if nodePtr is not null
    if(nodePtr){
        // recursively call left branch to continue the search
        findNameSearch(found, name, nodePtr->left);
        // if the name of current title does not return npos, there is a match from the desired search string
        if (nodePtr->name.find(name) != string::npos){
            // print title
            cout<< "Title found: " << nodePtr->name << endl;
            found = true;
        }
        // continue search, recursive call
        findNameSearch(found, name, nodePtr->right);
    }
    // base case
    else{
        return;
    }
        
}


// searches for the desired string - runs findNameSearch funciton
void musicOrg::findName(string name){
    bool found = false;
    findNameSearch(found, name, root);
    // if the found bool is still false, that means there were no matches
    if(!found){
        cout << "There are no matches in the inventory. Try again." << endl;
    }
}
