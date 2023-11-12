/*
Complementary algorithms for graphs
Jorge Gonzalez
*/

#include <iostream>
#include <list>
#include <vector>
#include <cstdlib>
#include <algorithm>

struct Node{
    int value; 
    bool visited;
    Node(int val) : value(val), visited(false){};
};

class Graph{
    private:
        int num_vertex = 0;
        int num_edges = 0;
        bool is_DAG = false;
        Node* root;
        std::vector<std::list<Node*>> adjacencyList;
        std::vector<Node*> visited;
        std::vector<Node*> node_stack;
        void loadGraph(void);
    public:
        Graph(int vertex, int edges) : num_vertex(vertex), num_edges(edges){
            // while(!this->is_DAG){
                // Feed current time to random number generator seed
                srand((unsigned int) time(NULL));
                loadGraph();
                this->node_stack.push_back(this->root);
                checkDAG(this->root);
                resetVisited();
            // }
            std::cout << "Is dag: " << this->is_DAG << "\n";
        };  // Create and load graph
        void display(void);
        void checkDAG(Node*);
        void resetVisited(void);
};

/**
 * @brief A function to reset all values used in DFS and BFS.
 * Time complexity -> Grows linearly with input size since it has to reset each vertex = O(V)
 * @param None
*/
void Graph::resetVisited(void){
    while(this->visited.size() > 0){
        Node* back = this->visited.back();
        back->visited = false;
        this->visited.pop_back();
    }
}

/**
 * @brief A function to display the adjacency list. Time complexity: Linear since it prints each vertex = O(V)
 * @param None
*/
void Graph::display(void){
    // Display the graph
    for(int l=0; l < this->adjacencyList.size(); ++l){
        std::cout << "List " << l << ": ";
        for(Node* n : this->adjacencyList[l]){
            std::cout << n->value << " - ";
        }
        std::cout << "\n";
    }
}

void Graph::loadGraph(void){
    // Load random nodes
    for(int vertex=0; vertex < this->num_vertex; ++vertex){
        Node *node = new Node(rand() % 50);
        std::list<Node*> current_list;
        current_list.push_back(node);
        this->adjacencyList.push_back(current_list);
    }

    // Ensure the creation of a DAG
    int root_index = (rand() % this->num_vertex);
    Node* root_node = this->adjacencyList[root_index].front();
    this->root = root_node;
    std::cout << "New graph with root " << this->root->value << " created in list number " << root_index << "\n";

    // Load random edges
    for(int edge=0; edge < this->num_edges; edge++){
        // Ensure that root has at least one connection
        if(adjacencyList[root_index].size() <= 1){
            Node* node_to_edge = adjacencyList[rand() %  this->num_vertex].front();
            while(node_to_edge == this->root){
                Node* node_to_edge = adjacencyList[rand() %  this->num_vertex].front();
        }
            this->adjacencyList[root_index].push_back(node_to_edge);  // Add connection to root 
        }else{
            int list_index;
            Node* node_to_edge;
            do {
                // Check if it's not connecting to itself, if the connection doesn't exist, and it's not the root
                list_index = rand() % this->num_vertex; // Randomly select a list
                node_to_edge = adjacencyList[rand() % this->num_vertex].front(); // Randomly select a node to connect

            } while(node_to_edge == adjacencyList[list_index].front() || (std::find(adjacencyList[list_index].begin(), adjacencyList[list_index].end(), node_to_edge) != adjacencyList[list_index].end()) || node_to_edge == this->root);
            // Add the connection
            adjacencyList[list_index].push_back(node_to_edge);
        }
    }
}

void Graph::checkDAG(Node* current_node){  // Asume root is already in node stack
    // Check if stack is already empty
    if(current_node == nullptr || current_node == NULL){
        this->is_DAG = true;
        return;
    }

    // Check if the current node was already visited, in case it is the graph isnt a DAG 
    if(current_node->visited == true){
        this->is_DAG = false;
        return;
    }
    // Mark as visited 
    current_node->visited = true;
    this->visited.push_back(current_node);
    this->node_stack.pop_back();  // Eliminate this node from stack
    
    // Get the current node adjacency list & add all the nodes in it to the aux stack to keep track of nodes to visit
    for(int list_aux = 0; list_aux < adjacencyList.size(); ++list_aux){
        // Find in which list is the current node
        if(current_node == adjacencyList[list_aux].front()){
            // Iterate through individual nodes inside the list
            for(auto node : adjacencyList[list_aux]){
                if(node != current_node){    // Add all the nodes except for the first one(which is only an indicator)
                    this->node_stack.push_back(node);
                }
            }
        }
    }
    // Send last element
    checkDAG(this->node_stack.back());
    return;
}

int main(void){
    // Create a new graph and load
    int num_vertex = 5; 
    int num_edges = 10;
    Graph graph(num_vertex, num_edges);
    graph.display();
    return EXIT_SUCCESS;
}