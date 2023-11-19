/* EQUIPO 5
- Ana Valeria Guzman Vazquez    / A01643224
- Clarissa Gardea Coronado      / A01569420
- Jorge Alejandro Gonzalez Diaz / A00344893
*/

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
        std::vector<Node*> maxOuts;
    public:
        Graph(){};
        void addNode(int);
        void addEdge(int, int);
        void DFS(Node*);
        void resetAll(void);
        bool node_exists(int);
        void showGraph(void);
        void checkOutDegree(std::ofstream &);
};


/**
 * @brief A function which displays the adjacency list of the graph
 * @param None
*/
void Graph::showGraph(void){
    int count = 0;
    // Print each one of the lists in the unordered map
    for(auto &pair : this->adjacencyList){
        std::cout << "Node " << count << ": ";
        // Iterate in this particular adjacency list
        for(auto &item : pair.second){
            std::cout << item->value << " - ";
        }
        ++count;
        std::cout << "\n";
    }
}

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

    // Delete this node from stack and add its adjacents
    std::cout << current_node->value << " - ";  // Print its value
    current_node->visited = true;
    this->visit_stack.pop_back();

    // Find the adjacency list of the node
    for(auto &it : this->adjacencyList){
        if(it.first == current_node->value){
            for(int i=1; i < it.second.size(); ++i){
                // Add each one of adjacents into stack
                this->visit_stack.push_back(*it.second.begin() + i);
            }
        }
    }
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

    // Get node 2 address
    auto it2 = this->adjacencyList.find(val2);
    Node* node2 = it2->second.front();   // Get node 2 with that key value memory address so we can edge Node - Node correctly 

    // Check if edge already exists and update flag
    bool flag = false;
    for(auto l_iter : it->second){
        if(l_iter->value == node2->value){flag = true;}
    }

    // If it doesnt exists make the edge
    if(!flag){
        // Edge
        it->second.push_back(node2);
        // Update out degree counter of first node
        it->second.front()->out_degree ++;
    }
    return;
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

/**
 * @brief A merge sort function to ensure the vector containing the nodes with max out degrees is always sorted 
 * @param array The vector containing the nodes with more out-degrees
 * @param left Left limit to sort 
 * @param right Right limit to sort 
*/
void mergeSort(std::vector<Node*> &array, int left, int right){
    // Management of base case
    if(left >= right){return;}

    // Get in the middle of the array
    int mid = left + (right - left) / 2;

    // Recursion to divide 
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);

    // Merge section
    int s1 = mid - left + 1;
    int s2 = right - mid;
    std::vector<Node*> left_vect(s1), right_vect(s2);
    
    // Add values to vectors
    for(int i=0; i < s1; ++i){
        left_vect[i] = array[left + i];
    }
    for(int i=0; i < s2; ++i){
        right_vect[i] = array[mid + i + 1];
    }

    // Finally sort them in the original array (only if the 2 conditions occur it enters in the loop)
    int count1 = 0, count2 = 0; int array_index = left;
    while(count1 < s1 && count2 < s2){
        if(left_vect[count1]->out_degree < right_vect[count2]->out_degree){
            array[array_index] = left_vect[count1];
            ++count1;
        }else{
            array[array_index] = right_vect[count2];
            ++count2;
        }
        ++array_index;
    }

    // Add the ones which werent added to array
    while(count1 < s1){
        array[array_index] = left_vect[count1];
        ++count1;
        ++array_index;
    }
    while(count2 < s2){
        array[array_index] = right_vect[count2];
        ++count2;
        ++array_index;
    }

}

/**
 * @brief A function to check all nodes and store the top 10 nodes with the largest out degrees in a vector. After this, it
 * writes them into an Output File passed by reference to the function
 * @param OutputFile File to write top 10 IP sections with largest out-degrees
*/
void Graph::checkOutDegree(std::ofstream &OutputFile){
    for(auto &pair : this->adjacencyList){
        // Ensure its sorted always
        mergeSort(this->maxOuts, 0, this->maxOuts.size() - 1);
        if(this->maxOuts.size() < 10){
            // If size is less than 10 add whichever node
            this->maxOuts.push_back(pair.second.front());
        }else{
            // If this element is larger than smallest element maxOuts vector replace it
            if(pair.second.front()->out_degree < this->maxOuts[0]->out_degree){
                this->maxOuts[0] = pair.second.front();
            }
        }
    }

    // Show max out degree items
    for(auto &it : this->maxOuts){
        OutputFile << "IP segment: " << it->value << " - Out Degree Value: " << it->out_degree << "\n";
    }
}

int main(){
    Graph ip_graph;
    std::ifstream InputFile("bitacora.txt");
    std::ofstream OutputFile("Output.txt");
    if(!InputFile || !OutputFile){std::cerr << "Error opening files\n"; return EXIT_FAILURE;}
    
    // Declare strings to read input file
    std::string date, time, ip, port, entry;
    std::string aux;
    while(InputFile){
        // Reset variables
        ip = port = date = time = "";

        // Split 
        getline(InputFile, entry);
        std::stringstream ss(entry);

        // Update time and date
        ss >> date >> aux;
        date += aux;
        ss >> time >> aux;

        // Manage ip/port division
        std::string aux2 = "";
        std::vector<int> ip_vals;   // To get ips for nodes
        int delimiter_index = aux.find(".");

        // Check for valid ip sections and ignore ports
        for(int i=0; i < aux.length(); ++i){
            if(aux[i] == '.' || aux[i] == ':'){
                // Add int ip to vector to add them to graph later
                ip_vals.push_back(std::stoi(aux2));
                aux2 = "";  // Reset
            }else if(aux[i] != '.' && aux[i] != ':'){
                aux2 += aux[i];
            }else if(aux[i] == ':'){break;}  // Ignore from port and after
        }

        // Edge values to the adjacent ip component inside the graph
        for(int i=0; i < ip_vals.size() - 1; ++i){
            ip_graph.addEdge(ip_vals[i], ip_vals[i + 1]);
        }
    }
    
    // Print info of nodes with most port accesses
    OutputFile << "PORTS WITH MOST ACCESSES\n";
    ip_graph.checkOutDegree(OutputFile);
    
    std::cout << "Successfully writen results to Output.txt file\n";
    InputFile.close();
    OutputFile.close();

    return EXIT_SUCCESS;
}