#include <iostream>
#include <queue>
#include <map>
#include "Node.h"

// Binary Search Tree class
class BST{
    private:
        int num_nodes;
        Node* root;
        // Recursive methods
        void postOrderPriv(Node *&);
        void insertPriv(Node *&, Node *&);
        void deletePriv(Node *&);
        Node* searchPriv(Node *&, int &);
        void mostAccessesPriv(Node*&, std::map<int, Node*> &);
    public:
        Node* search(int &key){return searchPriv(this->root, key);};
        void searchMaxAccesses(std::map<int, Node*> &aux_map){mostAccessesPriv(this->root, aux_map);};
        void postOrder(){postOrderPriv(this->root);};
        void displayLevels();
        void insert(Node *&node){insertPriv(this->root, node); ++num_nodes;};
        bool isEmpty();
        void deleteAll(){deletePriv(this->root);};
        int getNodeCount();
        // Constructor
        BST() : root(nullptr), num_nodes(0){};
};


void BST::insertPriv(Node *&current, Node *& node){
    // Correct node is available to insert
    if(current == nullptr){
        current = node;
        // std::cerr << "Node inserted correctly " << key << " at location " << current << "\n";
        return;
    }
    // Manage recursion
    if(node->key < current->key){
        insertPriv(current->left, node);
    }
    else if(node->key > current->key){
        insertPriv(current->right, node);
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

void BST::mostAccessesPriv(Node*& current, std::map<int, Node*> &aux_map){
    // Base case
    if(current == nullptr) return;
    // Recursion
    mostAccessesPriv(current->left, aux_map);
    mostAccessesPriv(current->right, aux_map);
    // If map size is less than 5 we can add whatever value to it 
    if(aux_map.size() < 5){
        aux_map[current->count] = current;
    }else if (aux_map.size() >= 5 && current->count > aux_map.begin()->first){  // If current node count is greater than one inside max_ports map
        aux_map.erase(aux_map.begin());
        aux_map[current->count] = current;
    }
}