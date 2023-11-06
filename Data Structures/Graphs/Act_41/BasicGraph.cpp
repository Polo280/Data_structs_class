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
        Graph(int vertex, int edges) : num_vertex(vertex), adj_list(new std::list<int> [vertex]), visited(new bool[vertex]){loadGraph(vertex, edges);};
        // Custom functions
        void loadGraph(int, int);
        void addEdge(int, int);
        void DFS(int);
        void BFS(int);
        void showGraph();
        void resetVisited();
};

void Graph::showGraph(){
    std::cout << "Graph nodes are: ";
    for(int i=0; i < num_vertex; ++i){
        std::cout << (adj_list + i)->front() << " - ";
    }
    std::cout << "\nGraph edges are: \n";
    for(int i=0; i < num_vertex; ++i){
        for(auto it : *(adj_list +  i)){
            std::cout << it << " - ";
        }
        std::cout << "\n";
    }
}

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
void Graph::loadGraph(int nodes, int edges){
    std::vector<int*> node_vect;
    // Add vertex at start of every list
    for(int i=0;i < nodes; ++i){
        int val = rand() % 50;
        (adj_list + i)->push_back(val);
        node_vect.push_back(&(adj_list + i)->front());
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
            while(connection == &(adj_list + i)->front()){
                connection = node_vect[rand() % nodes]; // To not connect it to itself
            }
            for(auto it : *(adj_list + i)){
                if (it == *connection){
                    exists = true;
                    break;
                }
            }
            if(!exists){
                (adj_list + i)->push_back(*connection);
                ++current_edges;
            }
        }
    }
}


int main(){
    const int num_vertex = 5; const int edges = 10;
    Graph g1(num_vertex, edges);
    g1.showGraph();
    // g1.DFS(34);

    std::cout << "\n";
    return EXIT_SUCCESS;
}