/*
A basic implementation of an algorithm which represents  bnary tree
Jorge Gonzalez 28/09/23
*/

#include <iostream>

struct Node{
    int value;
    Node* left; Node* right;
};

class BinaryTree{
    private:
        Node* root;
    public:
        BinaryTree() : root(NULL){};
        ~BinaryTree(){};
      
};

int main(){
    return EXIT_SUCCESS;
}