#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <list>
#include <unordered_map>

struct Node{
    int value;
    int out_degree;
    bool visited;
    Node() : out_degree(0){};
};


class Graph{
    private:
        std::unordered_map<int, std::list<Node*>> adjacencyList; 
        std::vector<Node*> visit_stack;
        Node* max_out_degree[10];
    public:
        Graph(){};
        void addNode(int);
        void addEdge(int, int);
        void DFS(Node*);
        void resetAll(void);
        bool node_exists(int);
};

/**
 * @brief Function used to check whether a node exists inside the graph 
 * @param value The node value to search
*/
bool Graph::node_exists(int value){
    // If its not an iterator to the end it means that it was found 
    if(this->adjacencyList.find(value) != this->adjacencyList.end()){
        return true;
    }
    return false;
}

/**
 * @brief A function to perform DFS algorithm to search for the Node with a given value
 * @param None
*/
void Graph::DFS(Node* current_node){
    // If current node is already visited dont do anything 
    if (current_node->visited){return;}

    current_node->visited = true;
    this->visit_stack.pop_back();
    
}

/**
 * @brief Call this function whenever you need to add a new Node - Node directional connection in the graph
 * @param val1 Node which is making the connection
 * @param val2 Node to connect
*/
void Graph::addEdge(int val1, int val2){
    // Check if any of the nodes doesnt exist
    if(!node_exists(val1)){addNode(val1);}
    if(!node_exists(val2)){addNode(val2);}

    // Get the singular adjacency list for node 1
    auto it = this->adjacencyList.find(val1);
    // Update out degree counter 
    it->second.front()->out_degree ++;

    // Insert node 2
    auto it2 = this->adjacencyList.find(val2);
    Node* node2 = it->second.front();   // Get node 2 with that key value memory address so we can edge Node - Node correctly 

    // Edge
    it->second.push_back(node2);
}

/**
 * @brief Call this function whenever you want to add a ned node into the adjacency list
 * @param value Node value (taken from IP)
*/
void Graph::addNode(int value){
    // Allocate memory for new node
    Node* new_node = new Node;
    new_node->value = value;

    // Create new list
    std::list<Node*> new_list;
    new_list.push_back(new_node);

    // Insert into adjacency list map
    this->adjacencyList[value] = new_list;
}

/**
* @brief Call this function whenever you need to reset visited status and visited stack during Node traversal
* @param None
*/
void Graph::resetAll(void){
    // Reset visited status
    for(int i=0; i < this->adjacencyList.size(); ++i){
        this->adjacencyList[i].front()->visited = false;
    }
    // Reset stack if its not empty
    while(this->visit_stack.size() > 0){
        this->visit_stack.pop_back();
    }
}


void mergeSort(Node** &node_array, ){

}

int main(){
    Graph ip_graph();
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
    }
    
    // Print info of nodes with most port accesses
    OutputFile << "PORTS WITH MOST ACCESSES\n";
    
    //tree.postOrder();
    InputFile.close();
    OutputFile.close();


    return EXIT_SUCCESS;
}