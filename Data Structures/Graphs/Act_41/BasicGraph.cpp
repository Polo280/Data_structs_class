/* A basic implementation for a graph data structure
*/
#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>


class Graph{
    private:
        std::list<int> *adj_list;
        int num_vertex, num_edges;
        bool *visited;
    public:
        // Constructor y destructor 
        Graph(int vertex) : num_vertex(vertex), adj_list(new std::list<int> [vertex]), visited(new bool[vertex]){};
        // Custom functions
        void addEdge(int, int);
        void DFS(int);
        void BFS(int);
        void showGraph();
        void resetVisited();
        // Getters & setters
        void setAdjList(std::list<int> adjList2){*adj_list = adjList2;};
};

void Graph::resetVisited() {
    for (int i = 0; i < num_vertex; i++)
        visited[i] = false;
}

void Graph::addEdge(int n1, int n2){
    this->adj_list[n1].push_back(n2);
}

void Graph::BFS(int startVertex)
{
    visited[startVertex] = true;
    std::list<int> queue;
    queue.push_back(startVertex);

    while (!queue.empty())
    {
        int currVertex = queue.front();
        std::cout << currVertex << " ";
        queue.pop_front();

        for (auto i : this->adj_list[currVertex])
        {
            if (!visited[i])
            {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}

void Graph::DFS(int vertex) {
    this->visited[vertex] = true;
    std::list<int> adjVertex = this->adj_list[vertex];
    std::cout << vertex << " ";
    for (auto i : adjVertex) {
        if (!this->visited[i]) {
            DFS(i);
        }
    }
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
        for(int k = 0; k < connections; ++k){ // set random number of edges on that node
            bool exists = false;
            int* connection = node_vect[rand() % nodes];
            while(connection == &(adjList + i)->front()){
                connection = node_vect[rand() % nodes]; // To not connect it to itself
            }
            for(auto it : *(adjList + i)){
                if (it == *connection){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                (adjList + i)->push_back(*connection);
                ++current_edges;
            }
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

    Graph g1(num_vertex);
    g1.setAdjList(*adjList);
    // g1.DFS(34);

    std::cout << "\n";
    return EXIT_SUCCESS;
}