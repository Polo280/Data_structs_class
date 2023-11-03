/* A basic implementation for a graph data structure
Author = Jorge Gonzalez
*/
#include <iostream>
#include <cstdlib>

struct Node
{
    int value;
};


class Graph{
    private:
        Node ** node_list;
        int num_vertex, num_edges;
    public:
        // Constructor y destructor 
        Graph(int vertex, int edges) : num_vertex(vertex), num_edges(edges){loadGraph(vertex, edges);};
        // Custom functions
        void loadGraph(int, int);
        void DFS();
        void showGraph();
};

/**
@brief Function to generate automatically random values for graph
@param nodes number of nodes to store in the graph
@param edges number of edges in the graph
*/
void Graph::loadGraph(int nodes, int edges){
    // Generate random nodes
    *this->node_list = new Node;
    for(int i=0; i < nodes; ++i){
        (*node_list + 1)->value = rand() % 100;  // Generate numbers 0-100
    }
}

/**
@brief Function to display adjacency list
@param None
*/
void Graph::showGraph(){
    Node* aux = *this->node_list;  // List starts here
    for(int i=0; i < this->num_vertex; ++i){
        std::cout << (aux + i)->value << "\n";
        ++ aux;
    }
}

int main(){
    Graph g1(5, 7);
    g1.showGraph();
    return EXIT_SUCCESS;
}