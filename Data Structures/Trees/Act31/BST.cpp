/*
Sample code implementation of Binary search tree
Jorge Gonzalez 9/10/23
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <queue>
#include <random>

// Base struct node
struct Node{
    int value;
    Node *left, *right;
    Node (int data) : value(data), left(NULL), right(NULL){}   // Constructor
    Node(){};
};

class Bst{
    private:
        Node *root;
        int num_elements = 1;   // Track the current number of elements in the tree
        void insertPrivate(int&, Node*&);
        // Operations to display values (private)
        void preOrderPriv(Node*&);
        void inOrderPriv(Node*&);
        void postOrderPriv(Node*&);
        // Other functions
        int heightPriv(Node*&, int);
        void deleteAllPriv(Node*);
        void ancestorsPriv(int, Node *&, std::vector<int>&, bool&);
        int whatLevelPriv(int, Node *&, int level);
    public:
        // Operations to display values (public) only to make initial recursive call
        void inOrder(){inOrderPriv(root);};
        void preOrder(){preOrderPriv(root);};
        void postOrder(){postOrderPriv(root);};
        void levelByLevel();
        // To get other data
        int height(){return heightPriv(root, 0);};
        int whatLevelAmI(int value){return whatLevelPriv(value, root, 1);};
        int getNumItems(); 
        void visit(int);
        void ancestors(int data, std::vector<int>& vect, bool& state){ancestorsPriv(data, this->root, vect, state);};
        // Insert
        void insert(int value){insertPrivate(value, root);}
        void deleteAll(){deleteAllPriv(this->root);};
        // Constructor & destruct
        Bst(int root_num){
            this->root = new Node(root_num);
        };
        ~Bst(){};
};

// Time complexity --> O(1) the complexity is constant in all cases
int Bst::getNumItems(){   
    return this->num_elements;
}

// Time complexity --> O(n) the time consumption increases linearly the more elements we have in the tree
void Bst::insertPrivate(int &data, Node *&current){   // Recursive function
    if(current == NULL){
        current = new Node(data);  // If pointer is not taken insert new value
        this->num_elements ++;
        //std::cerr << "Element inserted succesfully, element: " << data << std::endl;
    }else{
        if(data < current->value){
            insertPrivate(data, current->left);  
        }else if (data > current->value){
            insertPrivate(data, current->right);
        }else{
            std::cerr << "Repeated elements not allowed" << std::endl;
        }
    }
}

// Time complexity --> O(n) recursive calls increase linearly the more elements we have
void Bst::preOrderPriv(Node *&current){   // Display in PreOrder
    if(current == NULL){
        return;
    }
    std::cerr << current->value << " - ";
    preOrderPriv(current->left);
    preOrderPriv(current->right);
}

// Time complexity --> O(n) recursive calls increase linearly the more elements we have
void Bst::inOrderPriv(Node *&current){
    if(current == NULL){     // End recursion
        return;
    }
    inOrderPriv(current->left);
    std::cerr << current->value << " - ";
    inOrderPriv(current->right);
}

// Time complexity --> O(n) recursive calls increase linearly the more elements we have
void Bst::postOrderPriv(Node *&current){
    if(current == NULL){
        return;
    }
    postOrderPriv(current->left);
    postOrderPriv(current->right);
    std::cerr << current->value << " - ";
}

// Time complexity --> O(n) because what this function do is basically take each node, print its value and then add its existing children to a queue, the process repeats and time consumption increases linearly with the number of nodes we have
void Bst::levelByLevel(){
    if(this->root == NULL){
        std::cerr << "The BST is empty, cannot display" << std::endl;
        return;
    }
    std::queue<Node*> q1;
    q1.push(this->root);

    Node *aux;
    while(!q1.empty()){
        q1.push(NULL);

        aux = q1.front();
        while(aux != NULL){
            std::cerr << aux->value << " ";
            if(aux->left != NULL){q1.push(aux->left);}
            if(aux->right != NULL){q1.push(aux->right);}
            q1.pop();
            aux = q1.front();
        }
        q1.pop();
        std::cerr << std::endl;
    }
}

// Time complexity --> O(1), the function is just a switch and if statement which calls other functions, so time complexity is constant
void Bst::visit(int selection){   // Menu type function for choosing display algorithm
    if(this->root == NULL){std::cerr << "The tree is empty" << std::endl;}
    switch (selection)
    {
    case 1:
        this->preOrder();
        break;
    case 2:
        this->inOrder();
        break;
    case 3:
        this->postOrder();
        break;
    case 4:
        this->levelByLevel();
        break;
    }
}

// Tiem complexity --> O(n), time consumption increases linearly the more levels we have
int Bst::heightPriv(Node *&current, int count){
    int counts[2];
    if(current != NULL){  // Base case
        // Recursive calls
        counts[0] = heightPriv(current->left, count) + 1;
        counts[1] = heightPriv(current->right, count) + 1;
        if(counts[0] >= counts[1]){return counts[0];} else{return counts[1];}  // Return max subtree height
    }else{
        return 0;
    }
}

// Time Complexity --> O(n) because time consumption incrceases linearly the more elements we have, it traverses one each time the requirements are met (if statement)
void Bst::ancestorsPriv(int data, Node *&current, std::vector<int> &vect, bool& state){
    if(current == NULL){
    }else{
        if(data < current->value){
            ancestorsPriv(data, current->left, vect, state);  
            vect.push_back(current->value);
        }else if (data > current->value){
            ancestorsPriv(data, current->right, vect, state);
            vect.push_back(current->value);
        }else{
            state = true;
            return;
        }
    }
    return;
}

// Time Complexity -> O(n) beacuse it has to delete each one of the nodes
void Bst::deleteAllPriv(Node* current){
    if(current == NULL){
        this->root = NULL;
        return;
    }
    deleteAllPriv(current->left);
    deleteAllPriv(current->right);
    delete(current);
}

// Time complexity --> O(n), time increases linearly with the number of elements. It iterates through them once each time the specifications are met
int Bst::whatLevelPriv(int value, Node *&currentNode, int level){
     if (currentNode != NULL){
        if (value == currentNode->value)
            return level;
        else if (value < currentNode->value)
            return whatLevelPriv(value, currentNode->left, level + 1);
        else if (value > currentNode->value)
            return whatLevelPriv(value, currentNode->right, level + 1);
    }
    return -1;
}

void insertVals(Bst &tree){
    for(int i=0; i < rand() % 35; i++){
        tree.insert(rand() % 35);
    }
}

int main(){
    // Create a new tree
    Bst tree(25);
    // Insert values
    insertVals(tree);
    // Visits
    std::cerr << "Show in preOrder" << std::endl;
    tree.visit(1);
    std::cerr << "`\nShow inOrder" << std::endl;
    tree.visit(2);
    std::cerr << "\nShow in postOrder" << std::endl;
    tree.visit(3);
    std::cerr << "\nShow in order level by level" << std::endl;
    tree.visit(4);
    // What level am I test
    int element = rand() % 10;
    std::cerr << "Element " << element << " is in level " << tree.whatLevelAmI(element) << std::endl;
    // Tree height
    std::cerr << "The height of the tree is " << tree.height() << std::endl;
    // Element ancestors
    element = 9;
    std::cerr << "The ancestors of the element " << element << " are : ";
    std::vector<int> ancestors;   // Vector for getting the ancestors
    bool exists = false;
    tree.ancestors(element, ancestors, exists);
    if(exists){
        for(auto it = ancestors.begin(); it != ancestors.end(); ++it){
            std::cerr << *it << " - ";
        }
    }else{std::cerr << "Element does not exist" << std::endl;}
    std::cerr << std::endl;
    // Delete all
    std::cerr << "Delete All Test" << std::endl;
    tree.deleteAll();
    tree.visit(1);   // Test that its now empty
    return EXIT_SUCCESS;
}