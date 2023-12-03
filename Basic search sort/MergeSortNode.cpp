#include <iostream>
#include <vector>

struct Node{
    int value;
    int out_degree;
    bool visited;
    Node() : out_degree(0){};
};

void mergeSort(std::vector<Node*> &array, int left, int right){
    // Management of base case
    if(left >= right){return;}

    // Get in the middle of the array
    int mid = left + (right - left) / 2;

    // Recursion to divide 
    mergeSort(array, left, mid);
    mergeSort(array, mid + 1, right);

    // Merge section
    int s1 = mid - left + 1;
    int s2 = right - mid;
    std::vector<Node*> left_vect(s1), right_vect(s2);
    
    // Add values to vectors
    for(int i=0; i < s1; ++i){
        left_vect[i] = array[left + i];
    }
    for(int i=0; i < s2; ++i){
        right_vect[i] = array[mid + i + 1];
    }

    // Finally sort them in the original array (only if the 2 conditions occur it enters in the loop)
    int count1 = 0, count2 = 0; int array_index = left;
    while(count1 < s1 && count2 < s2){
        if(left_vect[count1]->value < right_vect[count2]->value){
            array[array_index] = left_vect[count1];
            ++count1;
        }else{
            array[array_index] = right_vect[count2];
            ++count2;
        }
        ++array_index;
    }

    // Add the ones which werent added to array
    while(count1 < s1){
        array[array_index] = left_vect[count1];
        ++count1;
        ++array_index;
    }
    while(count2 < s2){
        array[array_index] = right_vect[count2];
        ++count2;
        ++array_index;
    }

}

int main(){
    std::vector<Node*> nodes;
    int arr[11] = {3, 5, 1, 0, 32, 14, 22, 75, 378, 88, 445};

    // Create nodes
    for(int i=0; i < 11; ++i){
        Node* new_node = new Node;
        new_node->value = arr[i];
        nodes.push_back(new_node);
    }

    // Merge sort
    mergeSort(nodes, 0, nodes.size() - 1);
    //Print
    for(auto &it : nodes){
        std::cout << it->value << " - ";
    }
    std::cout << "\n";
    return EXIT_SUCCESS;
}