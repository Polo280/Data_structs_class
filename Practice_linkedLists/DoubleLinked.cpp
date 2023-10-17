/*
Basic methods for operating with Doubly Linked Lists
Implementation using methods of the class DoubleLinkedList
Jorge 24/09/23 (initial version)
*/
#include <iostream>

struct Node{
    int value;
    Node *next;
    Node *prev;
};

class DoubleLinkedList{ // Doubly linked list class w
    private:
        Node *head;
    public:
        DoubleLinkedList():head(NULL){std::cerr << "A doubly linked list was created" << std::endl;};
        void insert_begin(int);
        void insert_mid(int, int);
        void insert_end(int);
        Node* search(int); 
        void display();  
        void del(int);
        void deleteAll();  // KABOOOM!    
};

// Complexity - O(1) constant
void DoubleLinkedList::insert_begin(int value){
    // Memory alloca.tion
    Node *new_node = new Node;
    // Set params for new node
    new_node->value = value; 
    new_node->next = this->head;
    new_node->prev = NULL;
    // Update head
    if(head != NULL){  // A null head cannot point
        this->head->prev = new_node;
    }
    head = new_node;
}

// Complexity = O(n) linear
void DoubleLinkedList::insert_end(int value){
    Node *current_node = this->head;
    while(current_node->next != NULL){   // Traverse through all the elements
        current_node = current_node->next;
    }
    Node *tail = new Node;
    tail->value = value; tail->next = NULL; tail->prev = current_node;
    current_node->next = tail;
}

// Complexity = O(n) linear
void DoubleLinkedList::insert_mid(int index, int value){
    Node *current_node = this->head;
    int count = 1;
    while(count < index - 1 && current_node != NULL){
        current_node = current_node->next;
        count ++;
    }
    if(current_node == NULL){
        std::cerr << "Index is too large" << std::endl;  // Cerr is unbuffered so its faster than cout
        return;
    }
    // Update node pointers
    Node *node_aux = new Node;
    node_aux->value = value;
    node_aux->prev = current_node; node_aux->next = current_node->next;
    current_node->next = node_aux; 
    node_aux->next->prev = node_aux;
}

// Complexity = O(n) linear
Node* DoubleLinkedList::search(int value){
    Node *current_node = head;
    while(current_node->value != value && current_node != NULL){
        current_node = current_node->next;
    }
    return current_node;
}

// Complexity = O(n) linear, best = O(1)
// Display in both directions
void DoubleLinkedList::display(){
    if(head == NULL){
        std::cerr << "List is empty" << std::endl;
        return;
    }
    Node *current_node = this->head;
    std::cerr << current_node->value;
    // Recorrer en una direccion
    while(current_node->next != NULL){
        current_node = current_node->next;
        std::cerr << " -> " << current_node->value;
    }
    // Recorrer al reves
    std::cerr << std::endl;
    std::cerr << current_node->value;
    current_node = current_node->prev;
    while(current_node != NULL){
        std::cerr << " <- " << current_node->value;
        current_node = current_node->prev;
    }
}

// Complexity - Best O(1) - worst = O(n)
void DoubleLinkedList::del(int value){
    if(this->head->value == value){
        Node *aux = this->head;
        this->head = this->head->next;
        this->head->prev = aux->prev;
        delete(aux);
        return;
    }else{
        Node *current_node = this->head->next;
        while(current_node->value != value && current_node->next != NULL){
            current_node = current_node->next;
        }
        if(current_node->next == NULL){
            std::cerr << "Element not found for deletion" <<  std::endl;
            return;
        }
        else if(current_node->next->next != NULL){
            current_node->prev->next = current_node->next;  // Double link
            current_node->next->prev = current_node->prev;
            delete(current_node);
            return;
        }else{
            current_node->prev->next = NULL;
            delete(current_node);
            return;
        }
    }
}

 // Complexity = O(n)
void DoubleLinkedList::deleteAll(){
    Node *aux = this->head->next->next;
    // Traverse all elements deleting them
    while(aux->next != NULL){
        delete(aux->prev);      // Deallocate memory
        aux = aux->next;
    }
    delete(aux);
    this->head = NULL;
}

int main(){
    DoubleLinkedList doubleList;
    doubleList.insert_begin(1);
    doubleList.insert_begin(5);
    doubleList.insert_begin(10);
    doubleList.insert_end(20);
    doubleList.insert_end(30);
    doubleList.insert_end(40);
    doubleList.insert_mid(70, 50);  // Index, value
    doubleList.display();
    // Search test
    std::cerr << "\nValue 10 is at memory address: " << doubleList.search(10) << std::endl;
    std::cerr << "Value 40 is at memory address: " << doubleList.search(40) << std::endl;
    // Delete test
    doubleList.del(20);
    std::cerr << "\nDelete number 20" << std::endl;
    doubleList.display();
    std::cerr << "\nDelete number 10" << std::endl;
    doubleList.del(100);
    doubleList.display();
    // Kaboom
    std::cerr << "\n\nAll nodes deletion" << std::endl;
    doubleList.deleteAll();
    doubleList.display();
    return EXIT_SUCCESS;
}