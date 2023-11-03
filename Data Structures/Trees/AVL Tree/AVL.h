#include <iostream>
#include "Node.h"

class AVL{
    private:
        Node* root;
        void insertPriv(Node* root, Node*);
        void postOrder(Node*);
    public:
        void insert(Node* node){insertPriv(this->root, node);};
        void display(){};
        AVL();
};

void AVL::insertPriv(Node* current, Node* node){
    
}

