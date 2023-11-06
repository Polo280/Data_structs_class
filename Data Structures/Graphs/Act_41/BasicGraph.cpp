/* A basic implementation for a graph data structure
*/
#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <queue>


class Graph{
    private:
        std::list<int> *adj_list;
        int num_vertex, num_edges;
    public:
        // Constructor y destructor 
        Graph(int vertex) : num_vertex(vertex), adj_list(new std::list<int> [vertex]){};
        // Custom functions
        void addEdge(int, int);
        void DFS(int);
        void BFS(int);
        void showGraph();
        // Getters & setters
        void setAdjList(std::list<int> adjList2){*adj_list = adjList2;};
};

void Graph::BFS(int startVertex) {
    std::vector<bool> visited(num_vertex, false);
    std::queue<int> queue;

    visited[startVertex] = true;
    queue.push(startVertex);

    while (!queue.empty()) {
        int currentVertex = queue.front();
        queue.pop();

        std::cout << "Visited: " << currentVertex << " ";
        for (std::list<int>::iterator i = adj_list[currentVertex].begin(); i != adj_list[currentVertex].end(); ++i) {
            int adjVertex = *i;
            if (!visited[adjVertex]) {
                visited[adjVertex] = true;
                queue.push(adjVertex);
            }
        }
    }
    std::cout << std::endl;
}

void Graph::DFS(int startVertex) {
    static std::vector<bool> visited(num_vertex, false);

    visited[startVertex] = true;
    std::cout << "Visited: " << startVertex << " ";

    for (std::list<int>::iterator i = adj_list[startVertex].begin(); i != adj_list[startVertex].end(); ++i) {
        int adjVertex = *i;
        if (!visited[adjVertex]) {
            DFS(adjVertex);
        }
    }
}

// Add an edge between two nodes
void Graph::addEdge(int n1, int n2){
    this->adj_list[n1].push_back(n2);
}


/**
@brief Function to generate automatically random values for graph
@param nodes number of nodes to store in the graph
@param edges number of edges in the graph
*/
void loadGraph(int nodes, int edges, std::list<int> *&adjList){
    std::vector<int*> node_vect;
    // Add vertex at start of every list
    for(int i=0;i < nodes; ++i){
        int val = rand() % 50;
        (adjList + i)->push_back(val);
        node_vect.push_back(&(adjList + i)->front());
    }
    int current_edges = 0;
    // Add edges randomly
    for(int i=0; i < nodes; ++i){
        int connections = 0;
        if(i >= nodes - 1){
            connections = edges - current_edges;
        }else{
            connections = rand() % (edges - current_edges);
        }
        for(int k = 0; k < connections; ++k){
            int* connection = node_vect[rand() % nodes];
            while(connection == &(adjList + i)->front()){
                connection = node_vect[rand() % nodes]; // To not connect it to itself
            }
            (adjList + i)->push_back(*connection);
            ++current_edges;
        }
    }
}


int main(){
    const int num_vertex = 5; const int edges = 10;
    std::list<int> *adjList = new std::list<int>[num_vertex];
    loadGraph(num_vertex, edges, adjList); 
    
    std::cout << "Graph nodes are: ";
    for(int i=0; i < num_vertex; ++i){
        std::cout << (adjList + i)->front() << " - ";
    }
    std::cout << "\nGraph edges are: \n";
    for(int i=0; i < num_vertex; ++i){
        for(auto it : *(adjList +  i)){
            std::cout << it << " - ";
        }
        std::cout << "\n";
    }

    std::cout << "\n";
    return EXIT_SUCCESS;
}