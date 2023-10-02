/*
A basic implementation of a priority queue
Jorge Gonzalez 01/10/23
*/
#include <iostream>

struct Node{
    int value;
    int priority;
};

class PriorityQueue{
    private:
        Node *queueArray;
        int size_index, max_size;
    public:
        PriorityQueue(int n) : max_size(n), size_index(-1), queueArray(new Node[n]){
            std::cout << "A new priority queue was created" << std::endl;
        };
        ~PriorityQueue(){};
        void enqueue(int, int);
        Node dequeue();
        void display();
        void update(int, int, int);
        bool isEmpty();
        bool isFull();
        Node* peek(int);
};

// Time complexity = O(1) constant in all cases
void PriorityQueue::enqueue(int value, int priority){
    if(this->isFull()){std::cout << "\nPriority queue is full, dequeue first to add more elements - value: " << value << std::endl; return;}
    this->size_index ++;
    this->queueArray[size_index].value = value;
    this->queueArray[size_index].priority = priority;
}

// Time complexity = O(n), best case when queue is empty --> O(1)
Node PriorityQueue::dequeue(){
    if(this->isEmpty()){std::cout << "Queue is empty, cannot dequeue" << std::endl;}
    Node aux; aux.priority = 0; int rm_index;
    for(int i=0; i < size_index + 1; i++){        // Search for the node with the highest priority
        if(this->queueArray[i].priority > aux.priority){
            rm_index  = i;
            aux = this->queueArray[i];
        }
    } 
    for(int i = rm_index; i < size_index; i++){   // Update indexes after the value that was removed
        this->queueArray[i] = this->queueArray[i + 1];
    }
    this->size_index --;
    std::cout << "\nDequeued node with value " << aux.value << " and priority of " << aux.priority << std::endl;
    return aux;
}

// Time complexity: O(n), best case when queue is empty --> O(1)
void PriorityQueue::display(){
    if(this->isEmpty()){std::cout << "Priority queue is empty" << std::endl; return;}
    std::cout << "\nShowing in format (value, priority)" << std::endl;
    for(int i=0; i < size_index + 1; i++){
        std::cout << "(" << this->queueArray[i].value << " : " << this->queueArray[i].priority << ") - ";
    }
} 

// Time complexity = O(1) in all cases
bool PriorityQueue::isEmpty(){
    if(this->size_index < 0)
        return true;
    return false;
}

// Time complexity = O(1) in all cases
bool PriorityQueue::isFull(){
    if(this->size_index >= max_size - 1)
        return true;
    return false;
}

// Time complexity = O(1) in all cases
void PriorityQueue::update(int index, int value, int priority){
    if(this->isEmpty()){std::cout << "Cannot update value, queue is empty" << std::endl; return;}
    if(index > size_index){std::cout << "Cannot update value, index out of range" << std::endl; return;}
    this->queueArray[index].value = value;   // Update node in the given index with the corresponding values
    this->queueArray[index].priority = priority;
    std::cout << "\n\nSuccesfully updated node index " << index << " with value " << value << " priority " << priority << std::endl;
}

// Time complexity = O(n), best case when queue is empty = O(1)
Node* PriorityQueue::peek(int value){
    Node *nullp = nullptr;
    if(this->isEmpty()){std::cout << "Queue is empty" << std::endl; return nullp;}
    for(int i=0; i < this->size_index + 1; i++){       // Search the element that matches the given value
        if(this->queueArray[i].value == value){
            std::cout << "\nElement with value " << value << " is stores in memory address " << &queueArray[i] << std::endl;
            return &queueArray[i];      // Return pointer to the location it is stored in
        }
    }
    std::cout << "\nElement with value " << value << " not found" << std::endl;
    return nullp;
}

int main(){
    // Creation of a priority queue
    PriorityQueue pq1(10);
    // Enqueue tests
    pq1.enqueue(1, 2);
    pq1.enqueue(2, 4);
    pq1.enqueue(3, 6);
    pq1.enqueue(4, 8);
    pq1.enqueue(-9, 18);
    pq1.display();
    //Update test
    pq1.update(0, 14, 2);
    pq1.display();
    // Peek test
    Node *mem_address = pq1.peek(-9);
    pq1.display();
    // Dequeue test
    Node test = pq1.dequeue();
    pq1.display();
    return EXIT_SUCCESS;
}