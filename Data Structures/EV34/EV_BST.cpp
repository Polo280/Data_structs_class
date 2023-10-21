/*
Evidencia competencia 3.4 --> Registro de accesos con BST 
*/

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <queue>
#include <map>

struct Node{
    int key;
    int count = 0;
    // IP vector 
    std::vector<std::string> ip;
    std::vector<std::string> messages;
    // Children
    Node *left;
    Node *right;
    // Constructor
    Node() : left(NULL), right(NULL){};
};

// Binary Search Tree class
class BST{
    private:
        int num_nodes;
        Node* root;
        // Recursive methods
        void postOrderPriv(Node *&);
        void insertPriv(Node *&, int &);
        void deletePriv(Node *&);
        Node* searchPriv(Node *&, int &);
        void mostAccessesPriv(Node*&, std::map<int, Node*> &);
    public:
        Node* search(int &key){return searchPriv(this->root, key);};
        void searchMaxAccesses(std::map<int, Node*> &aux_map){mostAccessesPriv(this->root, aux_map);};
        void postOrder(){postOrderPriv(this->root);};
        void displayLevels();
        void insert(Node *&node){insertPriv(this->root, node->key); ++num_nodes;};
        bool isEmpty();
        void deleteAll(){deletePriv(this->root);};
        int getNodeCount();
        // Constructor
        BST() : root(nullptr), num_nodes(0){};
};


void BST::insertPriv(Node *&current, int &key){
    // Correct node is available to insert
    if(current == nullptr){
        current = new Node;
        current->key = key;
        // std::cerr << "Node inserted correctly " << key << " at location " << current << "\n";
        return;
    }
    // Manage recursion
    if(key < current->key){
        insertPriv(current->left, key);
    }
    else if(key > current->key){
        insertPriv(current->right, key);
    }
    return;
}

void BST::displayLevels(){
    std::queue<Node*> q1;
    q1.push(this->root);
    while(!q1.empty()){
        // Check front and add children if they exist
        Node *current = q1.front();
        if(current->left != nullptr){q1.push(current->left);}
        if(current->right != nullptr){q1.push(current->right);}
        // Print and pop
        std::cerr << current->key << " - ";
        q1.pop();
    }
}

void BST::postOrderPriv(Node *&current){
    // Base case
    if(current == nullptr) return;
    // Recursion
    postOrderPriv(current->left);
    postOrderPriv(current->right);
    std::cerr << current->key << " - ";
}

bool BST::isEmpty(){
    return (this->root == nullptr)? true : false;
}

int BST::getNodeCount(){
    return num_nodes;
}

void BST::deletePriv(Node *&current){
    // Set root to nullptr
    if(current == this->root){this->root = nullptr; return;}
    // Base case
    if(current == nullptr){return;}
    // Recursion
    deletePriv(current->left);
    deletePriv(current->right);
    delete(current);
}

Node* BST::searchPriv(Node *&node, int &key){
    // Correct node is available to insert
    if(node == nullptr){
        return nullptr;
    }
    // Manage recursion
    if(key < node->key){
        Node* aux = searchPriv(node->left, key);
        return aux;
    }
    else if(key > node->key){
        Node* aux = searchPriv(node->right, key);
        return aux;
    }
    else{
        return node;
    }
}

void BST::mostAccessesPriv(Node*& current, std::map<int, Node*> &aux_map){
    // Base case
    if(current == nullptr) return;
    // Recursion
    mostAccessesPriv(current->left, aux_map);
    mostAccessesPriv(current->right, aux_map);
    // If map size is less than 5 we can add whatever value to it 
    if(aux_map.size() < 5){
        aux_map[current->count] = current;
    }else if (aux_map.size() >= 5 && current->count > aux_map.begin()->first){  // If current node count is greater than one inside max_ports map
        aux_map.erase(aux_map.begin());
        aux_map[current->count] = current;
    }
}

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
            Node *node = new Node;   
            node->key = num_port;
            node->count = 1;
            node->ip.push_back(ip);
            node->messages.push_back(entry);
            tree.insert(node);
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
    return EXIT_SUCCESS;
}