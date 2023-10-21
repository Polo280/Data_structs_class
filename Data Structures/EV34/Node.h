#pragma once
#include <iostream>
#include <vector>
#include <string>

struct Node{
    int key;
    int count;
    std::string message;
    // IP vector 
    std::vector<std::string> ip;
    // Children
    Node *left;
    Node *right;
    // Constructor
    Node() : left(NULL), right(NULL){};
};

