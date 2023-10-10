/*
Basic implementation of Queue structure and methods
Jorge Gonzalez 27/09/23
*/
#include <iostream>
#include <cstdlib>    // To use rand function

namespace queueSpace{    // Using a namespace to prevent errors for having the same structure Node with different implementations
    struct Node
    {
        int value;
    };

    class Queue{
        private:
            Node *arrayBegin;      // Memory location of the start of the queue array
            int front, rear;       // inndexes of first and last value in queue
            int size;
        public:
            Queue(int n) : front(-1), rear(-1), size(n), arrayBegin(new Node[n]){};  // Constructor
            ~Queue(){};
            void enqueue(int);
            Node dequeue();
            Node* search(int);
            void update(int, int);
            void display();
            bool checkEmpty();
            bool checkFull();
    };

    // Complexity - O(1) = constant in best, average and worst case 
    void Queue::enqueue(int value){
        // Check if its not full
        if(this->checkFull()){
            std::cout << "Queue is full, cannot add " << value << std::endl;
            return;
        }
        // Enqueue
        if(this->checkEmpty()){
            (this->arrayBegin) ->value = value;
            this->front ++; this->rear ++;   // Set the indexes to 0
        }else{
            this->rear++; 
            (this->arrayBegin + this->rear )->value = value;
        }
    }

    // Time complexity: Best Case = O(1) if stack is empty, otherwise O(n) due to for loop
    inline Node Queue::dequeue(){
        // Check if its empty
        if(this->checkEmpty()){
            std::cout << "Cannot dequeue, queue is empty  "; 
            this->front = -1; this->rear = -1;
            return *new Node;
        }
        else{
            Node aux_node = *this->arrayBegin;  // Get the first node in queue
            if(this->rear != this->front){
                for(int i=0; i < this->rear; i++){
                    (this->arrayBegin + i)->value = (this->arrayBegin + (i + 1))->value;
                }
            }
            this->rear --;
            return aux_node;
        }
    }

    // Complexity = O(1)
    inline bool Queue::checkEmpty(){
        if(rear == -1){
            return true;
        }
        return false;
    }

    // Complexity = O(1)
    inline bool Queue::checkFull(){
        if(this->front == 0 && rear == size - 1){
            return true;
        }
        return false;
    }

    // Time complexity = O(n)
    inline Node* Queue::search(int value){
        // Sequential search
        for(int i=0; i < this->rear + 1; i++){
            if((this->arrayBegin + i)->value == value){
                return (this->arrayBegin + i);
            }
        }
        return nullptr;
    }

    // Time complexity = O(1)
    inline void Queue::update(int index, int value){
        if(index > this->rear){std::cout << "Index too large" << std::endl; throw index;}
        Node *aux = this->arrayBegin + index; // Get the desired location to update
        aux->value = value;
    }

    // Time complexity: Best case when queue is empty O(1), worst case O(n) due to loop
    inline void Queue::display(){
        if(this->checkEmpty()){std::cout << "The queue is empty" << std::endl;}
        else{
            for(int i=0; i < this->rear; i++){
                std::cout << (this->arrayBegin + i)->value << " -> " ;
            }
            std::cout << (this->arrayBegin + this->size - 1)->value << std::endl;
        }
    }
}