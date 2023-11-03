#pragma once
struct Node{
    int value;
    int balance_factor;
    Node* left;
    Node* right;
    Node() : left(nullptr), right(nullptr), balance_factor(0){};
};