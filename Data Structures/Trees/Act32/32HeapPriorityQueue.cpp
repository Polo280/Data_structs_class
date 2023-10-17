/*
Priority queue implementation using heap
Jorge Gonzalez 16/10/23
*/

#include <iostream>
#include <vector>

struct Node{
    int value; 
};

class PriorityQueue{
    private:
        std::vector<Node*> arr; 
        void heapify(std::vector<Node*>&, int);
    public:
        PriorityQueue(){};
        int size();     //Returns size of Queue
        bool empty();   //Returns if empty
        Node* top();    //Returns top Node
        void deleteAll();
        // Manage recursive calls   
        Node pop(); //Returns cero element of queue
        void push(int);
        // Display
        void display();
};

// Time complexity = O(n log(n)) because 
void PriorityQueue::heapify(std::vector<Node*>&heap, int index){
    if(index < 0){return;}
    int size = heap.size();
    int largest = index; 
    int l = 2 * index + 1;
    int r = 2 * index + 2;
    if(l < size && heap[l]->value > heap[largest]->value){
        largest = l;
    }
    if(r < size && heap[r]->value > heap[largest]->value){
        largest = r;
    }
    if(largest != index){
        std::swap(heap[index], heap[largest]);
        heapify(heap, largest);
    }
}

Node PriorityQueue::pop(){
    Node aux = *this->arr[0];  // Get the root
    // Replace root with last value
    arr[0] = arr[arr.size()-1];
    arr.pop_back();
    // Heapify
    int index = arr.size()/2 - 1;
    for(int i = index; i >= 0; i--){
        heapify(arr, i);
    }
    return aux;
}

void PriorityQueue::push(int data){
    // Prepare node to insert
    Node* aux_node = new Node;
    aux_node->value = data;
    // Insert
    arr.push_back(aux_node);
    // Heapify
    int index = arr.size()/2 - 1;
    for(int i = index; i >= 0; i--){
        heapify(arr, i);
    }
}

// Time complexity = constant O(1) because it only returns array size independently of the input
int PriorityQueue::size(){ // Get priority queue size
    return arr.size();
}

// Time complexity = constant O(1) because it only returns if the data structure is empty
bool PriorityQueue::empty(){ // Check if empty
    return (arr.size() < 1);
}

// Time complexity = constant O(1) because it only returns the first element in the array whichever the input is
Node* PriorityQueue::top(){  // Return highest priority node
    return arr[0];
}

void PriorityQueue::display(){ // Display the queue
    if(this->size() == 0){
        std::cerr << "Priority queue is empty\n";
    }
    for(int i=0; i < this->size(); i++){
        std::cerr << arr[i]->value << " - ";
    }
    std::cerr << std::endl;
}

void PriorityQueue::deleteAll(){
    while(!this->empty()){
        arr.pop_back();
    }
std::cerr << "Priority queue was deleted succesfully\n";
}

int main(){
    PriorityQueue q1;
    q1.push(25);
    q1.push(14);
    q1.push(786);
    q1.push(102);
    q1.push(5);
    q1.push(193);
    q1.display();
    // Pop
    std::cerr << "Pop root, element: " << q1.pop().value << "\n";
    q1.display();
    // Get size
    std::cerr << "The size of the priority queue is: " << q1.size() << std::endl;
    // Top
    std::cerr << "The top element in the priority queue is: " << q1.top()->value << std::endl;
    // Delete
    q1.deleteAll();
    q1.display();
    return EXIT_SUCCESS;
}