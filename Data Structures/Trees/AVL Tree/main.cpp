#include <iostream>
#include <AVL.h>
#include <Node.h>

int main(){
    AVL tree;
    const int elements = 3;
    const int items[elements] = {25, 30, 36};
    for(int i=0; i < elements; ++i){
        Node* node = new Node;
        node->value = items[i];
        tree.insert(node);
    }
    tree.display();
    return EXIT_SUCCESS;
}