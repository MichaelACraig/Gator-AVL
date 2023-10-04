//
// Created by Michael Craig on 9/25/23.
//
#ifndef PROJECT1_NODE_H
#define PROJECT1_NODE_H

#include <iostream>
#include <vector>

using namespace std;
struct BST{

    struct Node{
        Node* left;
        Node* right;
        Node* parent; //Possibnly need? Idk since we have recursion and it'll catch the BF as soon as it sees 2

        string NAME;
        int ID;
        //int balanceFactor;

        Node(string x, int y) : NAME(x), ID(y), left(nullptr), right(nullptr), parent(nullptr) {}
        //~Node();
    };

    //All "temp" values for rotation functions. Probably need to deallocate those to null in removal
    Node* root = nullptr;
    Node* grandchild = nullptr;
    Node* parent = nullptr;
    Node* newParent = nullptr;

    void masterFunction();

    //Search Functions
    void search(string NAME);
    Node* searchNAMERecurse(Node* root, string NAME);
    void search(int ID);
    Node* searchIDRecurse(Node* root, int ID);

    //Print functions with their helpers
    void printPreorder();
    Node* printPreorderRecursive(Node* root);
    void printInorder();
    Node* printInorderRecursive(Node* root);
    void printPostorder();
    Node* printPostorderRecursive(Node* root);
    void printLevelCount();

    //Rotation functions
    Node* rotateLeft(Node*& root);
    Node* rotateRight(Node*& root);
    Node* rotateLeftRight(Node*& root);
    Node* rotateRightLeft(Node*& root);

    //Insertion and balancing functions
    Node* insert(string NAME, int ID);
    Node* recursion(Node* insertionNode, Node* root);

    int findHeight(Node* root);

    int findBalanceFactor(Node* root);
    Node* balanceFactorOfAllNodes(Node* root);

    //Removal Functions
    void remove(int ID);
    Node* removeRecursive(Node* root, int ID);
    Node* findInorderSuccessor(Node* root);
    Node* removeInorder(int N);
    Node* removeInorderRecursive(Node* root, int N, int count);
};

#endif //PROJECT1_NODE_H
