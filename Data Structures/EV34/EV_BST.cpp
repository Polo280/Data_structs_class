#include <iostream>
#include <fstream>
#include <sstream>
#include <map>
#include "Node.h"
#include "BST.h"

int main(){
    BST tree;
    std::ifstream InputFile("bitacora.txt");
    std::ofstream OutputFile("Output.txt");
    if(!InputFile || !OutputFile){std::cerr << "Error opening files\n"; return EXIT_FAILURE;}
    
    // Declare strings to read input file
    std::string date, time, ip, port, entry;
    std::string aux;
    while(InputFile){
        // Reset variables and split entry
        ip = port = "";
        getline(InputFile, entry);
        std::stringstream ss(entry);
        ss >> date >> aux;
        date += aux;
        ss >> time >> aux;

        // Manage ip/port division
        const int delimiter_index = aux.find(":");
        for(int i=0; i < aux.length(); ++i){
            if(i < delimiter_index){ip += aux[i];
            }else if (i > delimiter_index){port += aux[i];}
        }

        // Check whether port value exists in the tree and add new node if not
        int num_port = std::stoi(port);
        Node *aux_ptr = tree.search(num_port);
        if(aux_ptr == nullptr){
            aux_ptr = new Node;   
            aux_ptr->key = num_port;
            aux_ptr->count = 1;
            aux_ptr->ip.push_back(ip);
            aux_ptr->messages.push_back(entry);
            tree.insert(aux_ptr);
        }else{ // Element already exists
            aux_ptr->count = ++aux_ptr->count;
            aux_ptr->messages.push_back(entry);
            aux_ptr->ip.push_back(ip);
        }
    }
    // Tree is ready, search for the ports with most accesses
    std::map<int, Node*> max_ports;
    tree.searchMaxAccesses(max_ports);
    
    // Print info of nodes with most port accesses
    OutputFile << "PORTS WITH MOST ACCESSES\n";
    for(const auto &it : max_ports){
        OutputFile << "Port: " << it.second->key << "\n";
        OutputFile << "Times Accessed: " << it.first << "\n";
        OutputFile << "MESSAGES \n";
        for(const auto &it2 : it.second->messages){
            OutputFile << it2 << "\n";
        }
        OutputFile << "\n\n";
    }

    //tree.postOrder();
    InputFile.close();
    OutputFile.close();
    return EXIT_SUCCESS;
}