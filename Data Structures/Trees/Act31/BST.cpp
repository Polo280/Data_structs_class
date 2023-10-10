/*
Sample code implementation of Binary search tree
Jorge Gonzalez 9/10/23
*/

#include <iostream>
#include <cmath>
#include <vector>

// Base struct node
struct Node{
    int value;
    Node *left, *right;
    Node (int data) : value(data), left(NULL), right(NULL){}   // Constructor
    Node(){};
};

class Queue{
    private:
        Node *arrayBegin;      // Memory location of the start of the queue array
        int front, rear;       // inndexes of first and last value in queue
        int size;
    public:
        Queue(int n) : front(-1), rear(-1), size(n), arrayBegin(new Node[n]){};  // Constructor
        ~Queue(){};
        void enqueue(Node*);
        Node* dequeue();
        bool checkEmpty();
        void display();
};

// Complexity - O(1) = constant in best, average and worst case 
void Queue::enqueue(Node* aux){
    // Enqueue
    if(this->checkEmpty()){
        *(this->arrayBegin) = *aux;
        this->front ++; this->rear ++;   // Set the indexes to 0
    }else{
        this->rear++; 
        *(this->arrayBegin + this->rear) = *aux;
    }
}

// Time complexity: Best Case = O(1) if stack is empty, otherwise O(n) due to for loop
inline Node* Queue::dequeue(){
    // Check if its empty
    if(this->checkEmpty()){
        std::cout << "Cannot dequeue, queue is empty  "; 
        this->front = -1; this->rear = -1;
        return new Node(0);
    }
    else{
        Node *aux_node = this->arrayBegin;  // Get the first node in queue
        if(this->rear != this->front){
            for(int i=0; i < this->rear; i++){
                (this->arrayBegin + i)->value = (this->arrayBegin + (i + 1))->value;
            }
        }
        this->rear --;
        return aux_node;
    }
}

// Complexity = O(1)
inline bool Queue::checkEmpty(){
    if(rear == -1){
        return true;
    }
    return false;
}

///////////////////////////////////////////////////////////////////////////////////////////////////

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
        void ancestorsPriv(int, Node*&, std::vector<int>&);
    public:
        // Operations to display values (public) only to make initial recursive call
        void inOrder(){inOrderPriv(root);};
        void preOrder(){preOrderPriv(root);};
        void postOrder(){postOrderPriv(root);};
        void levelByLevel();
        // To get other data
        int height(){return heightPriv(root, 0);};
        int whatLevelAmI(int);
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
    Queue queue(pow(2, this->height() - 1));  // Create a queue considering the worst case size
    Node *current;
    queue.enqueue(this->root);
    while(!queue.checkEmpty()){
        current = queue.dequeue();
        std::cerr << current->value << " - ";
        if(current->left != NULL){queue.enqueue(current->left);}
    }
    std::cerr << std::endl;
}

void Bst::visit(int selection){   // Menu type function for choosing display algorithm
    if(this->root == nullptr){std::cerr << "The tree is empty" << std::endl;}
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

int main(){
    Bst tree(25);
    // Insert values
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
    //tree.visit(1);

    std::vector<int> vect;
    tree.ancestors(4, vect);
    for (int i = 0; i < vect.size(); i++) {
        std::cerr << vect[i] << " ";
    }
    tree.deleteAll();

    // Operations
    // tree.preOrder();
    // std::cerr << std::endl;
    // tree.inOrder();
    // std::cerr << std::endl;
    // tree.postOrder();
    // std::cerr << std::endl;
    // tree.levelByLevel();
    // std::cerr << std::endl;
    // std::cerr << tree.height() << std::endl;
    return EXIT_SUCCESS;
}