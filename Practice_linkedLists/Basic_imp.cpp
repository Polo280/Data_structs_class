/*
Basic methods for operating with Singly Linked Lists
Jorge 24/09/23 (initial version)
*/

#include <iostream>

// Linked list single node w
struct Node{
    int value; 
    Node *next;  // Pointer type node to next
};

class SingleLinkedList{
    private:
        Node *head;
    public:
        SingleLinkedList() : head(NULL){std::cerr << "Linked list created" << std::endl;}  // Initialize head member to NULL
        void insert_begin(int);
        void insert_mid(int, int);  // One integer for value and another one for index
        void insert_end(int);
        void del(int);
        Node* search(int);
        void display();
};

void SingleLinkedList::insert_begin(int value){
    Node *new_node = new Node;  // Allocate memory for new_node address
    if(new_node == NULL){  // In case memory is full
        std::cerr << "Cannot allocate memory for head node" << std::endl;
        throw; 
    }
    // Assign values to new node created
    new_node->value = value;
    new_node->next = this->head;
    // Update head address to this new node at the beginning
    this->head = new_node;
}

void SingleLinkedList::insert_end(int value){
    Node *end_node = new Node; // Allocate free memory for node
    if(end_node == NULL){      // If address does not exist
        std::cerr << "Cannot allocate memory for end node" << std::endl;
        throw;
    }
    Node *current_node = this->head->next;  // Start with the pointer next in head
    while(current_node->next != NULL){      // while it doesnt point to null
        current_node = current_node->next;  // Update current to next
    }
    // when end of the linked list is reached, point it to another node
    end_node->value = value;
    end_node->next = NULL;          // Set tail next pointer to null
    current_node->next = end_node;  // Point to end
}

void SingleLinkedList::insert_mid(int index, int value){
    Node *current_node = this->head; int count = 1; // Start at the node which head is pointing to (index = 1)
    while(count < index - 1 && current_node != NULL){
        current_node = current_node->next;
        count ++;
    }
    if(current_node == NULL){
        std::cerr << "Index is too large" << std::endl;  // Cerr is unbuffered so its faster than cout
    }
    // when we've reached the specified index
    Node *new_node = new Node;
    new_node->value = value; new_node->next = current_node->next;
    current_node->next = new_node; // Update next to inserted
}

void SingleLinkedList::display(){
    int count = 1; Node *node = this->head->next; // node points to next of current node
    std::cerr << "Node 0: " << this->head->value << " - points to " << this->head->next << std::endl;
    while(node != NULL){
        std::cerr << "Node "<< count << ": " << node->value << " - points to " << node->next << std::endl;
        node = node->next;
        count ++;
    }
} 

Node* SingleLinkedList::search(int value){
    Node* current_node = head;
    while(current_node != NULL && current_node->value != value){  // Traverse the list until item is found
        current_node = current_node->next;
    }
    return current_node; // If item is not found current_node will be NULL
}

void SingleLinkedList::del(int value){
    Node *current_node = head;
    // Check if value is in head 
    if(this->head->value == value){
        head = head->next;
        delete current_node;
        return;  // End function
    }
    // Traverse nodes
    while(current_node->next->value != value && current_node->next != NULL){
        current_node = current_node->next;
    }
    if(current_node->next == NULL){
        std::cerr << "Item not found for deletion" << std::endl;
        return;
    }
    // If value is found (in next node)
    Node *aux_node = current_node->next;
    current_node->next = aux_node->next;
    delete(aux_node);
}

int main(){
    std::cerr << "Program init" << std::endl;
    SingleLinkedList linked_list;
    // Insert tests
    linked_list.insert_begin(8);
    linked_list.insert_begin(7);
    linked_list.insert_end(9);
    linked_list.insert_end(11);
    linked_list.insert_mid(4, 10);
    linked_list.display();
    // Search test
    std::cerr << std::endl << "Search test" << std::endl;
    std::cerr << "Val 9 is in node address: " << linked_list.search(9) << std::endl;
    // Delete test
    std::cerr << std::endl << "Delete test" << std::endl;
    linked_list.del(9);
    linked_list.display();
    linked_list.del(7);  // delete head
    linked_list.display();
    return EXIT_SUCCESS;
}
