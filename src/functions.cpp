#include <iostream>
#include <sstream>
#include <string>
#include "Node.h"

using namespace std;
/*
 * Steps to get an AVL Tree
 * 1. Insert the node into the tree (Check edge cases: if it's the first node inserted, else recurse)
 * 2. Find the max height of the left subtree and the right subtree of each node after it is inserted using DFS
 * 3. Calculate the Balance Factor (left subtree height - right subtree height)
 * 4. If the Balance Factor != -1,0, or 1 (bounds), do a rotation. This rotation being based off of the +/- value of
 * that current node's ->left or ->right depending on the rotation.
 *
 * Steps need to be done recursively for efficiency
 * Balance factor(node) = height(node->left) - height(node->right)
 *
 * Lecture/Dicussion Notes:
 *
 * You will only be expected to call rotations/balance the tree after insertions
 * We won’t ask you to rebalance on deletion, only on insertion! <-- HUGE
 *
 *
 *
 *
 */

void BST::masterFunction(){
    int numOfCommands = 0;
    cin >> numOfCommands;

    for(int i = 0; i < numOfCommands; i++){
        string command;
        cin >> command;

        //Separates each string by spaces
        istringstream sCall(command);

        string commandName = "";

        sCall >> commandName;

        string NAME = "";
        int ID = 0;
        int nth = 0;

        if(commandName == "removeInorder"){ //We need to also do this with remove, search,
            sCall >> commandName >> nth;

            removeInorder(nth);
        }
        else if(commandName == "remove"){
            sCall >> commandName >> ID;

            remove(ID);
        }
        else if(commandName == "search"){
            //Need to check sCall >> commandName >> if it is ID or NAME
            if(sCall.peek() == '"'){
                sCall >> commandName >> NAME;

                search(NAME);
            }
            else{
                sCall >> commandName >> ID;

                search(ID);
            }

        }
        else if(commandName == "insert"){
            sCall >> commandName >> NAME >> ID;

            insert(NAME, ID);
        }
        else if (commandName == "printInorder") {
            printInorder();
        } else if (commandName == "printPreorder") {
            printPreorder();
        } else if (commandName == "printPostorder") {
            printPostorder();
        } else if (commandName == "printLevelCount") {
            printLevelCount();
        } else {
            cout << "Unsuccessful" << endl;
        }
    }
}

//Start of Search Functions
BST::Node* BST::searchIDRecurse(BST::Node* root, int ID){
    //Use DFS in any order to search each root->ID.
    // If ID == root->ID, print out their root->NAME
    if(root == nullptr || ID == root->ID){
        cout << root->NAME << endl;
        return root;
    }
    if(ID < root->ID){
        return searchIDRecurse(root->left, ID);
    }
    else{
        return searchIDRecurse(root->right, ID);
    }
}

BST::Node* BST::searchNAMERecurse(BST::Node* root, string NAME){
    //Use DFS in preOrder to search each root->NAME
    //If NAME == root->name, print out their root->ID << endl;
    //else, cout << "Unsuccessful << endl;

    if(root == nullptr){
        return nullptr;
    }
    if(NAME == root->NAME){
        cout << root->ID << endl;
    }

    searchNAMERecurse(root->left, NAME);
    searchNAMERecurse(root->right, NAME);
}

void BST::search(int ID){
    searchIDRecurse(root, ID);
}

void BST::search(string NAME){
    searchNAMERecurse(root, NAME);
}
//Start of Print Functions
BST::Node* BST::printPreorderRecursive(BST::Node *root) {
    if(root == nullptr){
        return 0;
    }
    cout << root->NAME << ", ";
    printPreorderRecursive(root->left); //Can't include root->left in the function because it expects no arguments
    printPreorderRecursive(root->right);
}

BST::Node* BST::printInorderRecursive(BST::Node *root) {
    if(root == nullptr){
        return 0;
    }
    printInorderRecursive(root->left);
    cout << root->NAME << ", ";
    printInorderRecursive(root->right);
}

BST::Node* BST::printPostorderRecursive(BST::Node *root) {
    if(root == nullptr){
        return 0;
    }
    printInorderRecursive(root->left);
    printInorderRecursive(root->right);
    cout << root->NAME << ", ";
}

void BST::printPreorder() {
    printPreorderRecursive(root);
}

void BST::printInorder() {
    printInorderRecursive(root);
}

void BST::printPostorder() {
    printPostorderRecursive(root);
}

void BST::printLevelCount() {
    //Literally just the findHeight() function we created
    cout << findHeight(root) << endl;
}

//End of Print Functions - Start of Rotation Functions

BST::Node* BST::rotateLeft(BST::Node*& root){ //We need to update the parent nodes of the root if there is one
    parent = root;
    newParent = root->right;
    grandchild = root->right->right;

    root->right = nullptr;
    newParent->left = root;

    //Properly assign root, then assign its left and right pointers to their respective positions and return
    root = newParent;
    //root->left = parent; Obsolete code, already does this at the start
    //root->right = grandchild;

    //Deallocate after each rotation: could be completely unnecessary
    parent = nullptr, newParent = nullptr, grandchild = nullptr;
    return root;
}

BST::Node* BST::rotateRight(BST::Node*& root){
    parent = root;
    newParent = root->left;
    grandchild = root->left->left;

    root->left = nullptr;
    newParent->right = root;

    root = newParent;
    //root->left = grandchild;
    //root->right = parent;

    //Deallocate after each rotation: could be completely unnecessary
    parent = nullptr, newParent = nullptr, grandchild = nullptr;
    return root;
}

BST::Node* BST::rotateRightLeft(BST::Node*& root){
    root->right = rotateRight(root->right);

    return rotateLeft(root);
}

BST::Node* BST::rotateLeftRight(BST::Node*& root){
    root->left = rotateLeft(root->left);

    return rotateRight(root);
}

//End of Rotation Functions - Start of Insertion Functions

BST::Node* BST::balanceFactorOfAllNodes(BST::Node* root) { //Recursion isn't working correctly
    //Take the root and find its balance factor
    if(root == nullptr){ //No nodes in the tree (base case), Single node base case is not needed, return.
        return nullptr;
    }

    root->left = balanceFactorOfAllNodes(root->left);
    int balanceFactor = findBalanceFactor(root);

    //If-elseif statements for calling the correct rotations based off the chart from Balanced Trees Lecture
    if(balanceFactor == -2){
        if(findBalanceFactor(root->right) == -1){
            cout << "rotateLeft" << endl;
            root = rotateLeft(root);
        }
        else if(findBalanceFactor(root->right) == 1){
            cout << "rotateRightLeft" << endl;
            root = rotateRightLeft(root);
        }
    }

    else if(balanceFactor == 2){
        if(findBalanceFactor(root->left) == 1){
            cout << "rotateRight" << endl;
            root = rotateRight(root);
        }
        else if(findBalanceFactor(root->left) == -1){
            cout << "rotateLeftRight" << endl;
            root = rotateLeftRight(root);
        }
    }

    //Recursively traverse the list, Inorder traversal
    root->right = balanceFactorOfAllNodes(root->right);

    findHeight(root); //Update the height

    return root;
}

int BST::findBalanceFactor(BST::Node *root) { //Utilizes findHeight() function to find balanceFactor
    if(root == nullptr){
        return 0;
    }
    int leftHeight = findHeight(root->left);
    int rightHeight = findHeight(root->right);

    int balanceFactor = leftHeight - rightHeight;

    return balanceFactor;
}

int BST::findHeight(BST::Node *root) {
    //Take the node root and use recursion to find the height of its left subtree and right subtree
    //In order to do this, use recursion

    if(root == nullptr){
        return 0;
    }
    else{
        int leftTreeHeight = findHeight(root->left);
        int rightTreeHeight = findHeight(root->right);

        return max(leftTreeHeight, rightTreeHeight) + 1;
    }
}

BST::Node* BST::recursion(BST::Node* insertedNode, BST::Node* root) {
    if (root == nullptr) {
        root = insertedNode;
        return root;
    }

    else if (insertedNode->ID < root->ID) { //If ID is less than root Node's ID, move left, recurse
        root->left = recursion(insertedNode, root->left);
    }
    else if(insertedNode->ID > root->ID){//If ID is greater than root Node's ID, move right, recurse
        root->right = recursion(insertedNode, root->right); //On second iteration, uses root->right as root in parameter and root->right = NULL
    }
    else { //If Nodes are equal to eachother
        cout << "Unsuccessful" << endl;
        return root;
    }
    return root;
}

BST::Node* BST::insert(string insertedName, int insertedID){ //Initial call, takes in both parameters
    auto* newNode = new BST::Node(insertedName, insertedID); //Creates a new node with said parameters

    if(root == nullptr){
        root = newNode;
        cout << "Successful" << endl;
        return root;
    }
    else {
        root = recursion(newNode, root); //Calls recursion to insert into the tree

        root = balanceFactorOfAllNodes(root); //Calls balanceFactorOfAllNodes() which balances the Tree via findHeight(), findBalanceFactor(), and combines.
        cout << "Successful" << endl;
        return root;
    }
}
//End of Insertion Functions - Start of Removal Functions

BST::Node* BST::findInorderSuccessor(BST::Node* root){
    BST::Node* temp = root->right;
    while (temp && temp->left){
        temp = temp->left;
    }
    return temp;
}

BST::Node* BST::removeRecursive(BST::Node *root, int ID) {
    //List traversal
    if(root->ID == ID){ //Base case for recursion
        //When that node is found, we need to replace a removed node w/  its Inorder Successor
        //The Inorder Successor is the first node greater than ID
        //once the root->ID equals the ID, we need to find the inorder Successor

        //Delete root if the statement reads true before running the code below

        //Case 1: Root has no children
        if(root->left == nullptr && root->right == nullptr){
            delete root;
            root = nullptr;
        }
            //Case 2: Root has one child (right or left)
        else if (root->left == nullptr && root->right != nullptr){
            Node* temp = root;
            root = root->right;

            delete temp;
        }
        else if (root->right == nullptr && root->left != nullptr){
            Node* temp = root;
            root = root->left;

            delete temp;
        }
            //Case 3: Root has two children
        else{ //Might be broken, come back to tomorrow
            Node* successor = findInorderSuccessor(root);
            root->NAME = successor->NAME;
            root->ID = successor->ID;
            root->right = removeRecursive(root->right, successor->ID); //deletes the successor node after replacement
        }
        cout << "Successful" << endl;
    }
    else if(ID > root->ID){
        root->right = removeRecursive(root->right, ID);
    }
    else if(ID < root->ID){
        root->left = removeRecursive(root->left, ID);
    }
    else{ //If the value is not found, is nullptr < ID? Keep in mind when testing this function
        cout << "Unsuccessful" << endl;
    }
    return root;
}

void BST::remove(int ID){
    removeRecursive(root, ID);
}

BST::Node* BST::removeInorderRecursive(BST::Node* root, int N, int count){
    //Do recursive InOrder traversal until count reaches the value of N
    if(root == nullptr){
        return nullptr;
    }
    root->left = removeInorderRecursive(root->left, N, count);
    count++;
    if(count == N) {
        remove(root->ID);
        return root;
    }
    root->right = removeInorderRecursive(root->right, N, count);
}

BST::Node* BST::removeInorder(int N) {
    int count = 0;
    removeInorderRecursive(root, N, count);

    //Below might be obsolete; Wanted to take an iterative approach but looks like it'll be long; Try recursive
    //Keep for reference in-case we need to go back, else just ignore.


    //Node* temp = root;

    //while(count < N){ //Traverse through until count = N
    //Traverse through the left subtree

    //Traverse through the root

    //Traverse through the right subtree
    //}
    //Extrapolate that node and its ID to pass in remove(int ID)


    //Basically the findHeight function, but needs to increment an int value x by 1 each time it goes to a node

    //Above needs to be made into a helper function to traverse the tree
    //Once that incremented value is met, run the remove function on that node
}
