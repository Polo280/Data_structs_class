/*
A code for the implementation of a class Stack and some of its basic methods
LIFO structure
Author Jorge González 28/09/23
*/
#include <iostream>
#include <cstdlib>    // To use rand function

struct Node{
    int value;
};

class Stack{
    private:
        int top, size;
        Node *stack_begin;
    public:
        Stack(int n) : top(-1), size(n), stack_begin(new Node[n]){};
        ~Stack(){};
        bool isEmpty();
        bool isFull();
        void push(int);
        Node pop();
        Node peek();
        Node* search(int);
        void update(int, int);
        void display();
};

// Time complexity = O(1)
void Stack::push(int value){
    if(this->isFull()){std::cout << "The stack is full, cannot push" << std::endl; return;}
    this->top ++;
    (this->stack_begin + top)->value = value;
}

// Time complexity = O(1)
Node Stack::pop(){
    if(this->isEmpty()){
        Node *null_node = nullptr;
        std::cout << "The stack is empty, cannot pop" << std::endl; 
        return *null_node;
    }
    Node aux = *(this->stack_begin + this->top);
    //delete(this->stack_begin + this->top);
    this->top --;
    return aux;
}

// Time complexity = O(1) in best case, otherwise O(n)
Node* Stack::search(int value){
    // Sequential search
    for(int i=0; i < top + 1; i++){
        if((this->stack_begin + i)->value == value){
            return this->stack_begin + i;
        }
    }
    std::cout << "Cannot find element " << value << " in stack" << std::endl;
    return nullptr;  // Not found
}

// Time complexity = O(1)
Node Stack::peek(){
    if(this->isEmpty()){
        Node *null_node = nullptr;
        return *null_node;
    }
    return *(this->stack_begin + this->top);
}

// Time complexity = O(1)
bool Stack::isEmpty(){
    if(this->top < 0)
        return true;
    return false;
}

// Time complexity = O(1)
bool Stack::isFull(){
    if(this->top >= this->size - 1)
        return true;
    return false;
}

// Complexity = Best case O(1), Otherwise O(n)
void Stack::display(){
    if(this->isEmpty()){std::cout << "The stack is empty" << std::endl; return;}
    for(int i=0; i < top + 1; i++){
        std::cout << (this->stack_begin + i)->value << " -> ";
    }
    std::cout << std::endl;
}

// Complexity = O(1)
void Stack::update(int index, int value){
    if(index > this->top){std::cout << "Index out of limit" << std::endl; return;}
    Node *node = this->stack_begin + index;
    node->value = value;
}

int main(){
    // Create stack
    Stack s1(5);
    s1.display();
    // PUSH
    s1.push(58);
    s1.push(107);
    s1.push(7);
    s1.push(38);
    s1.push(41);
    s1.display();
    // PEEK
    std::cout << "Peek at stack top: " << s1.peek().value <<std::endl;
    // POP
    std::cout << "Pop stack: " << s1.pop().value << std::endl;
    s1.display();
    // SEARCH
    int s = 10;
    std::cout << "Element " << s << " is in memory location " << s1.search(s) << std::endl;
    // UPDATE
    int index = 0; s = 2004;
    s1.update(index, s);
    s1.display();
    return EXIT_SUCCESS;
}