/*
Actividad integral estructura de datos lineales (Act 2.3)
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  
#include <vector>
using namespace std;

struct Node{
    // Pointers to next and previous nodes
    Node *next; Node *prev; 
    // Data to be stored
    unsigned long ip_index;
    string message;
};

class DoublyLinkedSorted{
    private:
        Node *head;
    public:
        DoublyLinkedSorted() : head(NULL){};
        ~DoublyLinkedSorted(){};
        void insert(Node);
        void search(int);
        void display();
};

void DoublyLinkedSorted::insert(Node node){
    // Create a new pointer to a node and assign values
    Node *new_node = new Node; 
    new_node->ip_index = node.ip_index;
    new_node->message = node.message;
    // Manage different cases
    if(this->head == NULL){    // Case where linked list is empty
        new_node->prev = NULL; 
        new_node->next = NULL;
        this->head = new_node;
        return;
    }else{
        // Traverse linked list to know where element goes sorted
        Node *iter_node = this->head; Node *aux_node;
        while(iter_node != NULL){
            if(iter_node->ip_index > new_node->ip_index){    // Current element index is greater than the node we want to insert
                if(iter_node != this->head){    // If element is not the smallest
                    new_node->prev = iter_node->prev;
                    new_node->next = iter_node;
                    iter_node->prev->next = new_node;
                    iter_node->prev = new_node;
                }else{
                   new_node->prev = NULL;       // Otherwise put it at the beginning of the list and update head pointer
                   new_node->next = head;
                   head->prev = new_node;
                   head = new_node; 
                }
                return;
            }
            if(iter_node->next == NULL){aux_node = iter_node;} // Store last element
            iter_node = iter_node->next;   // Update node to traverse
        }
        // If this section occurs, it means the element to insert has the highest value
        aux_node->next = new_node;
        new_node->prev = aux_node;
        new_node->next = NULL;
    }
}

void DoublyLinkedSorted::display(){
    if(head == NULL){
        std::cout << "List is empty" << std::endl;
        return;
    }
    Node *current_node = this->head;
    std::cout << current_node->ip_index;
    // Recorrer en una direccion
    while(current_node->next != NULL){
        current_node = current_node->next;
        std::cout << " -> " << current_node->ip_index;
    }
    std::cout << std::endl;
}

int main(){
    DoublyLinkedSorted reg_list;
    // Clear console
    // system("cls");
    // File management
    ifstream InputFile("bitacora.txt");
    ifstream OutputFile("bitacoraSort.txt");
    // Check errors opening files
    if(!InputFile){std::cerr << "Error opening the input file" << std::endl; return 0;}
    if(!OutputFile){std::cerr << "Error opening the output file" << std::endl; return 0;}
    // Read input file (bitacora)
    string entry; string message;
    while(InputFile){
        // Read line from file
        getline(InputFile, entry);
        // Store message
        message = entry;
        // Do operations with string line
        stringstream ss(entry);
        for(int i=0; i < 3; i++){   // Read elements until we reach ip info
            string aux; 
            ss >> aux;
        }
        // Get Ip's
        string ip_string;
        ss >> ip_string;
        // Replace '.' and ':' in ip format for blank spaces
        // std::string::iterator iter_aux;
        for(std::string::iterator iter_aux = ip_string.begin(); iter_aux != ip_string.end(); iter_aux ++){
            if(*iter_aux == '.' || *iter_aux == ':'){
                *iter_aux = ' ';  // Replace
            }
        }
        // Convert to string stream
        stringstream ss2(ip_string);
        int ip_value = 0;
        //  Read until blank spaces
        for(int i=5; i > 0; i--){
            ss2 >> ip_string;
            try{
                ip_value = ip_value + stoi(ip_string);
            } catch (std::invalid_argument){
                break;
            }
        }
        std::cerr << ip_value << std::endl;
        // Start creating a node and assigning values
        Node data;
        data.message = message;
    }
    std::cerr << "\nProgram exited correctly";
    // Cerrar archivos
    OutputFile.close();
    InputFile.close();
    return EXIT_SUCCESS;
}