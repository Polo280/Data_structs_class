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
    Node(int val) : value(val){};
};

class Graph{
    private:
        int num_vertex = 0;
        int num_edges = 0;
        Node* root;
        std::vector<std::list<Node*>> adjacencyList;
        void loadGraph();
    public:
        Graph(int vertex, int edges) : num_vertex(vertex), num_edges(edges){loadGraph();};  // Create and load graph
        void display();
};

void Graph::loadGraph(){
    // Feed current time to random number generator seed
    srand((unsigned int) time(NULL));

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
            int list_index = rand() % this->num_vertex;
            std::list<Node*> selected_list = adjacencyList[list_index];   // Selected list to establish an edge with its first node
            Node* node_to_edge = adjacencyList[rand() %  this->num_vertex].front();   // Node to edge

            // Check if node isnt linking to itself and if the connection already exists or if the chosen node is the root
            while(node_to_edge == adjacencyList[list_index].front() || std::find(adjacencyList[list_index].begin(), adjacencyList[list_index].end(), node_to_edge) != adjacencyList[list_index].end() || node_to_edge == this->root){
                node_to_edge = adjacencyList[rand() %  this->num_vertex].front();
            }
            adjacencyList[list_index].push_back(node_to_edge);
            // std::cout << "Established a connection node " << selected_list.front()-> value << "- " << node_to_edge->value << "\n";
        }
    }
}

void Graph::display(){
    // Display the graph
    for(int l=0; l < this->adjacencyList.size(); ++l){
        std::cout << "List " << l << ": ";
        for(Node* n : this->adjacencyList[l]){
            std::cout << n->value << " - ";
        }
        std::cout << "\n";
    }
}

int main(void){
    // Create a new graph and load
    int num_vertex = 8; 
    int num_edges = 10;
    Graph graph(num_vertex, num_edges);
    graph.display();

    return EXIT_SUCCESS;
}