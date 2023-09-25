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
        DoubleLinkedList():head(NULL){std::cout << "A doubly linked list was created" << std::endl;};
        void insert_begin(int);
        void insert_mid(int, int);
        void insert_end(int);
        Node* search(int); 
        void display();  
        void del(int);
        void deleteAll();  // KABOOOM!    
};

void DoubleLinkedList::insert_begin(int value){
    // Memory allocation
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

void DoubleLinkedList::insert_end(int value){
    Node *current_node = this->head;
    while(current_node->next != NULL){   // Traverse through all the elements
        current_node = current_node->next;
    }
    Node *tail = new Node;
    tail->value = value; tail->next = NULL; tail->prev = current_node;
    current_node->next = tail;
}

void DoubleLinkedList::insert_mid(int index, int value){
    Node *current_node = this->head;
    int count = 1;
    while(count < index - 1 && current_node != NULL){
        current_node = current_node->next;
        count ++;
    }
    if(current_node == NULL){
        std::cerr << "Index is too large" << std::endl;  // Cerr is unbuffered so its faster than cout
    }
    // Update node pointers
    Node *node_aux = new Node;
    node_aux->value = value;
    node_aux->prev = current_node; node_aux->next = current_node->next;
    current_node->next = node_aux; 
    node_aux->next->prev = node_aux;
}

Node* DoubleLinkedList::search(int value){
    Node *current_node = head;
    while(current_node->value != value && current_node != NULL){
        current_node = current_node->next;
    }
    return current_node;
}

// Display in both directions
void DoubleLinkedList::display(){
    if(head == NULL){
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node *current_node = this->head;
    std::cout << current_node->value;
    // Recorrer en una direccion
    while(current_node->next != NULL){
        current_node = current_node->next;
        std::cout << " -> " << current_node->value;
    }
    // Recorrer al reves
    std::cout << std::endl;
    std::cout << current_node->value;
    current_node = current_node->prev;
    while(current_node != NULL){
        std::cout << " <- " << current_node->value;
        current_node = current_node->prev;
    }
}

void DoubleLinkedList::del(int value){
    Node *current_node = this->head;
    while(current_node->value != value && current_node != NULL){
        current_node = current_node->next;
    }
    if(current_node == NULL){
        std::cerr << "Element not found for deletion" <<  std::endl;
        return;
    }
    current_node->prev->next = current_node->next;  // Double link
    current_node->next->prev = current_node->prev;
    delete(current_node);
}

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
    doubleList.insert_begin(6);
    doubleList.insert_begin(5);
    doubleList.insert_begin(4);
    doubleList.insert_end(7);
    doubleList.insert_end(8);
    doubleList.insert_end(10);
    doubleList.insert_mid(6, 9);
    doubleList.display();
    // Search test
    std::cout << "\nValue 4 is at memory address: " << doubleList.search(4) << std::endl;
    std::cout << "Value 7 is at memory address: " << doubleList.search(7) << std::endl;
    // Delete test
    doubleList.del(7);
    std::cout << "\nDeleted number 7" << std::endl;
    doubleList.display();
    // Kaboom
    std::cout << "\n\nList deletion" << std::endl;
    doubleList.deleteAll();
    doubleList.display();
    return EXIT_SUCCESS;
}
