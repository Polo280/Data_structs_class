#pragma once
#include <iostream>
#include <vector>
#include <string>
struct Node{
    int key;
    int count = 0;
    // IP vector 
    std::vector<std::string> ip;
    std::vector<std::string> messages;
    // Children
    Node *left;
    Node *right;
    // Constructor
    Node() : left(NULL), right(NULL){};
};

