/*
Actividad integral estructura de datos lineales (Act 2.3)
*/

#include <iostream>
#include <string>
#include <fstream>
#include <sstream>  
#include <cmath>
using namespace std;

struct Node{
    // Pointers to next and previous nodes
    Node *next; Node *prev; 
    // Data to be stored
    long long ip_index;
    string message;
};

class DoublyLinkedSorted{
    private:
        Node *head;
    public:
        DoublyLinkedSorted() : head(NULL){};
        ~DoublyLinkedSorted(){};
        void insert(Node);
        void display();
        Node* getHead();
        Node* search(long long*);
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

Node* DoublyLinkedSorted::search(long long *ip_val){
    Node *loop_node = this->head;
    while(loop_node->ip_index < *ip_val && loop_node != NULL){
        loop_node = loop_node->next;
    }
    if(loop_node == NULL){
        return NULL;
    }else{
        return loop_node->prev;
    }
}

Node* DoublyLinkedSorted::getHead(){
    return head;
}

long long* userInputs(){  // Returns a pointer to the start of an array containing the start and the end values to search
    std::cout << " BIENVENIDO AL SISTEMA DE REGISTRO DE ACCESOS\n";
    std::cout << "---------------------------------------------\n";
    std::cout << "Favor de ingresar direcciones ip de inicio y fin para la búsqueda, formato (###.###.###.###)\n";
    std::cout << "Direccion de inicio: ";
    // Array declared static to use it outside the function call
    static long long input_values[2];
    static long long ip_val_start, ip_val_end;         // Aux to store the value of the ip
    string input_start, input_end;   // Variable to store the user inputs
    
    // Get and prepare string inputs
    std::cin >> input_start;
    std::cout << "Direccion final: ";
    std::cin >> input_end;
    for(std::string::iterator it = input_start.begin(); it != input_start.end(); it++){  // Start
        if(*it == '.'){*it = ' ';}   // Replace . with blank spaces to use operators >> in stringstream
    }
    for(std::string::iterator it = input_end.begin(); it != input_end.end(); it++){  // End
        if(*it == '.'){*it = ' ';}   // Replace . with blank spaces to use operators >> in stringstream
    }
    // Create stringstreams
    stringstream ss(input_start);
    stringstream ss2(input_end);
    // Remove '.'s
    for(int i=9; i >= -3; i=i-3){
        ss >> input_start;
        ss2 >> input_end;
        try{
            if(i >= 0){
                ip_val_start = ip_val_start + stoi(input_start) * pow(10, i);  // Adding ip elements according to priority
                ip_val_end = ip_val_end + stoi(input_end) * pow(10, i);
            }
        }catch (std::invalid_argument){
            std::cerr << "One of the arguments is invalid, try again" << std::endl;
            break;
        }
    }
    // Add ip values to static array
    input_values[0] = ip_val_start;
    input_values[1] = ip_val_end;
    return &input_values[0];   // return the location of the first element in the array
}

int main(){
    DoublyLinkedSorted reg_list;
    // File management
    ifstream InputFile("bitacora.txt");
    ofstream OutputFile("bitacoraSort.txt");
    ofstream OutputFinal("bitacoraSearch.txt");
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
        for(std::string::iterator iter_aux = ip_string.begin(); iter_aux != ip_string.end(); iter_aux ++){
            if(*iter_aux == '.' || *iter_aux == ':'){
                *iter_aux = ' ';  // Replace
            }
        }
        // Convert to string stream
        stringstream ss2(ip_string);
        long long ip_value = 0;
        //  Read ip values
        for(int i=9; i >= -3; i=i-3){
            ss2 >> ip_string;
            try{
                if(i >= 0){
                    ip_value = ip_value + stoi(ip_string) * pow(10, i);  // Adding ip elements according to priority
                }
            } catch (std::invalid_argument){
                break;
            }
        }
        // Start creating a node and assigning values
        Node data;
        data.message = message;
        data.ip_index = ip_value;
        //std::cerr<< ip_value;
        reg_list.insert(data);  // Insert each node to linked list
    }
    // Write sorted items to bitacoraSort
    Node *aux_node = reg_list.getHead();
    while(aux_node != NULL){
        OutputFile << aux_node->message << std::endl;
        aux_node = aux_node->next;
    }
    // GET INPUTS
    long long *ptr = userInputs();  // Get the pointer where array with user values are stored starts
    Node* start = reg_list.search(ptr);
    OutputFinal << start->message;
    // Write to sorted search
    // while(start != NULL){
    //     OutputFinal << start->message << std::endl;
    //     start = start->next;
    // }
    // Cerrar archivos
    OutputFile.close();
    InputFile.close();
    OutputFinal.close();
    // Exit
    std::cerr << "\nProgram exited correctly\n";
    return EXIT_SUCCESS;
}