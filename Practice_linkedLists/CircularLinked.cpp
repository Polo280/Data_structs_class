/*
Basic implementation of a circular linked list class
Jorge Gonzalez 25/09/23
*/
#include <iostream>

struct Node{
    int value;
    Node* next;
};

class CircularLinkedList{
    private:
        Node* head;
        Node* last;
    public: 
        CircularLinkedList() : head(NULL), last(NULL){std::cerr << "A circular linked list was created" << std::endl;}
        void insertBegin(int);
        void insertMid(int, int);
        void insertEnd(int);
        Node* search(int);
        void del(int);
        void display();
        void deleteAll();
};

void CircularLinkedList::insertBegin(int value){
    // Memory allocation
    Node *new_node = new Node;
    new_node->value = value; 
    if(this->head == NULL){  // If list is empty link node to itself
        this->head = new_node;
        this->last = new_node;
        new_node->next = this->last;
    }
    else{
        new_node->next = this->head;
        this->head = new_node;
        this->last->next = new_node;
    }
}

void CircularLinkedList::insertEnd(int value){
    Node* new_node = new Node;
    new_node->value = value;
    if(last == NULL){           // Link to itself
        this->head = new_node;
        this->last = new_node;
        new_node->next = new_node;
    }
    new_node->next = this->head;
    this->last->next = new_node;
    this->last = new_node;
}

void CircularLinkedList::insertMid(int index, int value){
        if(this->head == NULL){  // If list is empty link node to itself
            Node *new_node = new Node; new_node->value = value;
            this->head = new_node;
            this->last = new_node;
            new_node->next = this->last;
            std::cerr << "List is empty, inserting element at start" << std::endl;
            return;
        }else{
            Node* current_node = this->head; int count = 1;
            // Traverse elements
            while(count < index - 1){   
                current_node = current_node->next;
                count++;
            }
            // Manage cases if element inserted is in head or last position
            Node *aux = new Node; aux->value = value;
            if(current_node == this->head){
                aux->next = current_node;
                this->last->next = aux;
                head = aux;
            }else if(current_node == this->last){
                aux->next = this->head;
                this->last->next = aux;
                last = aux;
            }else{
                aux->next = current_node->next;
                current_node->next = aux;
            }
        }
}

Node* CircularLinkedList::search(int value){
    if(this->head->value == value){return head;}  // Best case
    Node* current_node = this->head->next;
    while(current_node->value != value && current_node != this->head){
        current_node = current_node->next;
    }
    if(current_node == this->head){
        std::cerr << "Element was not found" << std::endl;
        return NULL;
    }else{
        return current_node;
    }
}

void CircularLinkedList::del(int value){
    if(this->head->value == value){
        this->last->next = this->head->next;   // Remove head
        delete(this->head);
        this->head = last->next;
    }else if(this->last->value == value){      // Remove last
        Node *current_node = this->head;
        while(current_node->next != this->last){
            current_node = current_node->next;
        }
        current_node->next = this->head;
        delete(last); last = current_node;
    }else{  // Remove a mid element
        Node *current_node = this->head->next;
        while(current_node->next->value != value && current_node->next != this->head){
            current_node = current_node->next;
        }
        if(current_node->next != this->head){
            Node *aux = new Node;
            aux = current_node->next;
            current_node->next = current_node->next->next;
            delete(aux);
        }else{
            std::cerr << "Element to remove not found" << std::endl;
            return;
        }
    }
}

void CircularLinkedList::deleteAll(){
    Node *current_node = this->head->next; Node *aux = this->head;
    while(current_node!= this->last){
        delete(aux);
        aux = current_node;
        current_node = current_node->next;
    }
    this->head = NULL; this->last = NULL;
}

void CircularLinkedList::display(){
    if(head == NULL){
        std::cerr << "\nEmpty list - cannot display" << std::endl;
        return;
    }
    Node *current_node = this->head->next;
    std::cerr << this->head->value;
    while(current_node != this->head){
        std::cerr << " -> " << current_node->value;
        current_node = current_node->next;
    }
    std::cerr << std::endl;
}

int main(){
    CircularLinkedList circular_list;
    // Tests insert
    circular_list.insertEnd(3);
    circular_list.insertBegin(2);
    circular_list.insertBegin(1);
    circular_list.insertEnd(4);
    circular_list.insertEnd(6);
    circular_list.insertMid(5, 5);
    // Display list
    circular_list.display();
    // Search test
    std::cerr << "\nValue 4 is at memory address: " << circular_list.search(4) << std::endl;
    std::cerr << "Value 9 is at memory address: " << circular_list.search(9) << std::endl;
    // Delete element
    std::cerr << "\nDelete tests\n";
    circular_list.display();
    circular_list.del(4);
    circular_list.display();
    circular_list.del(1);     // Delete head
    circular_list.display();
    circular_list.del(6);     // Delete last
    circular_list.display();
    // Kaboom
    circular_list.deleteAll();
    circular_list.display();
    return EXIT_SUCCESS;
}
