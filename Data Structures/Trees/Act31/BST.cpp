/*
Sample code implementation of Binary search tree
Jorge Gonzalez 9/10/23
*/

#include <iostream>
#include <cmath>
#include <vector>
#include <queue>

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
        void ancestorsPriv(int, Node *&, std::vector<int>&);
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
        void ancestors(int data, std::vector<int>& vect){ancestorsPriv(data, this->root, vect);};
        // Insert
        void insert(int value){insertPrivate(value, root);}
        void deleteAll(){deleteAllPriv(this->root);};
        // Constructor & destruct
        Bst(int root_num){
            this->root = new Node(root_num);
        };
        ~Bst(){};
};

int Bst::getNumItems(){   
    return this->num_elements;
}

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

void Bst::preOrderPriv(Node *&current){   // Display in PreOrder
    if(current == NULL){
        return;
    }
    std::cerr << current->value << " - ";
    preOrderPriv(current->left);
    preOrderPriv(current->right);
}

void Bst::inOrderPriv(Node *&current){
    if(current == NULL){     // End recursion
        return;
    }
    inOrderPriv(current->left);
    std::cerr << current->value << " - ";
    inOrderPriv(current->right);
}

void Bst::postOrderPriv(Node *&current){
    if(current == NULL){
        return;
    }
    postOrderPriv(current->left);
    postOrderPriv(current->right);
    std::cerr << current->value << " - ";
}

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

int Bst::heightPriv(Node *&current, int count){
    int counts[2];
    if(current == NULL){  // Base case
        return count;
    }
    // Recursive calls
    counts[0] = heightPriv(current->left, count + 1);
    count = 0;
    counts[1] = heightPriv(current->right, count + 1);
    if(counts[0] >= counts[1]){return counts[0];} else{return counts[1];}  // Return max subtree height
}

void Bst::ancestorsPriv(int data, Node *&current, std::vector<int> &vect){
    if(current == NULL){
    }else{
        if(data < current->value){
            ancestorsPriv(data, current->left, vect);  
            vect.push_back(current->value);
        }else if (data > current->value){
            ancestorsPriv(data, current->right, vect);
            vect.push_back(current->value);
        }else{
            return;
        }
    }
}

void Bst::deleteAllPriv(Node* current){
    if(current == NULL){
        std::cerr << "The BST is now empty" << std::endl;
        return;
    }
    deleteAllPriv(current->left);
    deleteAllPriv(current->right);
    delete(current);
}

int Bst::whatLevelPriv(int value, Node *&currentNode, int level){
     if (currentNode == NULL)
        return -1;
     else{
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
    tree.insert(15);
    tree.insert(50);
    tree.insert(10);
    tree.insert(22);
    tree.insert(35);
    tree.insert(70);
    tree.insert(4);
    tree.insert(12);
    tree.insert(18);
    tree.insert(24);
    tree.insert(31);
    tree.insert(44);
    tree.insert(66);
    tree.insert(90);
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
    int element = 4;
    std::cerr << "Element " << element << " is in level " << tree.whatLevelAmI(element) << std::endl;
    // Tree height
    std::cerr << "The height of the tree is " << tree.height() << std::endl;
    // Element ancestors
    element = 12;
    std::cerr << "The ancestors of the element " << element << " are : ";
    std::vector<int> ancestors;   // Vector for getting the ancestors
    tree.ancestors(element, ancestors);
    for(std::vector<int>::iterator it = ancestors.begin(); it != ancestors.end(); it ++){
        std::cerr << *it << " - ";
    }
    std::cerr << std::endl;
    // Delete all
    tree.deleteAll();
    return EXIT_SUCCESS;
}