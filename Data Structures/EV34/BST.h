#include <iostream>
#include <queue>
#include "Node.h"

class BST{
    private:
        int num_nodes;
        Node* root;
        // Recursive methods
        void postOrderPriv(Node *&);
        void insertPriv(Node *&, int &);
        void deletePriv(Node *&);
        Node* searchPriv(Node *&, int &);
    public:
        Node* search(int &key){return searchPriv(this->root, key);};
        void postOrder(){postOrderPriv(this->root);};
        void displayLevels();
        void insert(Node *&node){insertPriv(this->root, node->key); ++num_nodes;};
        bool isEmpty();
        void deleteAll(){deletePriv(this->root);};
        int getNodeCount();
        // Constructor
        BST() : root(nullptr), num_nodes(0){};
};


void BST::insertPriv(Node *&current, int &key){
    // Correct node is available to insert
    if(current == nullptr){
        current = new Node;
        current->key = key;
        // std::cerr << "Node inserted correctly " << key << " at location " << current << "\n";
        return;
    }
    // Manage recursion
    if(key < current->key){
        insertPriv(current->left, key);
    }
    else if(key > current->key){
        insertPriv(current->right, key);
    }
    return;
}

void BST::displayLevels(){
    std::queue<Node*> q1;
    q1.push(this->root);
    while(!q1.empty()){
        // Check front and add children if they exist
        Node *current = q1.front();
        if(current->left != nullptr){q1.push(current->left);}
        if(current->right != nullptr){q1.push(current->right);}
        // Print and pop
        std::cerr << current->key << " - ";
        q1.pop();
    }
}

void BST::postOrderPriv(Node *&current){
    // Base case
    if(current == nullptr) return;
    // Recursion
    postOrderPriv(current->left);
    postOrderPriv(current->right);
    std::cerr << current->key << " - ";
}

bool BST::isEmpty(){
    return (this->root == nullptr)? true : false;
}

int BST::getNodeCount(){
    return num_nodes;
}

void BST::deletePriv(Node *&current){
    // Set root to nullptr
    if(current == this->root){this->root = nullptr; return;}
    // Base case
    if(current == nullptr){return;}
    // Recursion
    deletePriv(current->left);
    deletePriv(current->right);
    delete(current);
}

Node* BST::searchPriv(Node *&node, int &key){
    // Correct node is available to insert
    if(node == nullptr){
        return nullptr;
    }
    // Manage recursion
    if(key < node->key){
        Node* aux = searchPriv(node->left, key);
        return aux;
    }
    else if(key > node->key){
        Node* aux = searchPriv(node->right, key);
        return aux;
    }
    else{
        return node;
    }
}