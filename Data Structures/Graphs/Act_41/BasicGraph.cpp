/* A basic implementation for a graph data structure
Jorge Gonzalez
*/
#include <iostream>
#include <cstdlib>
#include <list>
#include <vector>
#include <algorithm>

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

// Time complexity : O(n^2) because it has a nested loop in which time increases exponentially with the input size
void Graph::showGraph(){
    for (int i = 0; i < this->num_vertex; i++)
    {
        std::cout << "\nVertex " << i << ":";
        for (auto x : this->adj_list[i])
            std::cout << " -> " << x;
    }
    std::cout << "\n";
}

// Time complexity = O(n) because its a loop which increases with the number of vertex
void Graph::resetVisited() {
    for (int i = 0; i < num_vertex; i++)
        visited[i] = false;
}

// Time complexity: O(1) complexity is constant in every case
void Graph::addEdge(int n1, int n2){
    this->adj_list[n1].push_back(n2);
    this->adj_list[n2].push_back(n1);
}

// Time complexity : O(V + E) 
void Graph::BFS(int startVertex) {
    std::list<int> queue;
    visited[startVertex] = true;
    queue.push_back(startVertex);
    while (!queue.empty()) {
        int currVertex = queue.front();
        std::cout << currVertex << " ";
        queue.pop_front();
        for (auto i : adj_list[currVertex]) {
            if (!visited[i]) {
                visited[i] = true;
                queue.push_back(i);
            }
        }
    }
}

// Time complexity: O(V + E) because its very similar to BFS
void Graph::DFS(int vertex) {
    visited[vertex] = true;
    std::cout << vertex << " ";
    for (auto i : adj_list[vertex]) {
        if (!visited[i]) {
            DFS(i);
        }
    }
}

// 
void Graph::loadGraph(int nodes, int edges) {
    // Init each vertex adj list
    for (int i = 0; i < nodes; ++i) {
        adj_list[i] = std::list<int>();
    }
    for (int i = 0; i < edges; ++i) {
        int n1 = rand() % this->num_vertex; 
        int n2 = rand() % this->num_vertex; 
        // Verify that edge doesnt exist yet, if it exists keep generating values
        while (n1 == n2 || std::find(adj_list[n1].begin(), adj_list[n1].end(), n2) != adj_list[n1].end()) {
            n1 = rand() % this->num_vertex;
            n2 = rand() % this->num_vertex;
        }
        // Create edge (undirected)
        addEdge(n1, n2);
    }
}


int main(){
    int num_vertex; int edges;
    // Inputs
    std::cout << "Pruebas Grafos\n";
    std::cout << "Numero de vertices (nodos): ";
    std::cin >> num_vertex;
    std::cout << "Numero de aristas: ";
    std::cin >> edges;

    Graph g1(num_vertex, edges);
    g1.showGraph();
    std::cout << "Depht First Search = ";
    g1.DFS(rand() % num_vertex);
    g1.resetVisited();
    std::cout << "\n";
    std::cout << "Breadth First Search = ";
    g1.BFS(rand() % num_vertex);
    g1.resetVisited();
    std::cout << "\n";

    return EXIT_SUCCESS;
}