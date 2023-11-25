#include <iostream>
#include <list>
#include <cmath>

using namespace std;

struct Item{
    int key;
    int index;
};

class HashTable {
private:
    int max_size;
    list<Item*> *table;
    int collisions = 0;
    // For quadratic hashing 
    const int c1 = 0;
    const int c2 = 2;
public:
    HashTable(int V) {
        this->max_size = getPrime(V);
        table = new list<Item*>[max_size];
    }
    ~HashTable(void) {
        delete[] table;
    }
    bool isPrime(int n);
    int getPrime(int n);
    void insertNewChaining(int key);
    void insertQuadratic(int key);
    void deleteItem(int key);
    int hashFunction(int key);
    int quadraticHash(int key, int i);
    void displayHash();
};

/**
 * @brief A function that helps to get hash through quadratic probing to avoid collisions
 * Complexity: O(1) because it performs a single instruction
*/
int HashTable::quadraticHash(int key, int i){
    // Hash function (quadratic)
    return (hashFunction(key)+ this->c1 * i + this->c2 * i * i) % this->max_size;
}

/**
 * @brief A function to check whether a number is prime through brute force
 * Complexity: Linear O(n) because it runs in a single loop
*/
bool HashTable::isPrime(int n) {
    if (n == 1 || n == 0){return false;}   // Base case

    int sqr_root = sqrt(n); // Check integers until square root of number because possible factors are in a symmetric distribution
    for (int i = 2; i <= sqr_root; i++) {
        if (n % i == 0)
            return false;
    }
    return true;
}

/**
 * @brief A function to find the nearest bigger prime to the specified number
 * Complexity: Linear O(n) because it runs inside a single loop
*/
int HashTable::getPrime(int n) {
    // Automatically discard even numbers
    if (n % 2 == 0){n++;}

    // Check odd numbers until a prime is found 
    while (!isPrime(n)) {
        n += 2;
    }
    return n;
}

/**
 * @brief A function to generate a hash based on the key and the capacity of the hash table
 * Complexity: Constant O(1) because it performs a single operation
*/
int HashTable::hashFunction(int key) {
    // The hash function is based on modulus
    return (key % max_size);
}

/**
 * @brief A functrion to insert a new element into the hash table managing the collisions through chaining
 * Complexity: Constant O(1) since it only appends the element at the end of the desired cell without checking anything
*/
void HashTable::insertNewChaining(int data) {
    // Create new struct
    Item* element = new Item;
    element->key = data;

    // Calculate in which position to store according to the hash function
    int index = hashFunction(data);
    element->index = index;

    // Collisions are managed automatically adding a new item at the back of the corresponding linked list 
    table[element->index].push_back(element);
}

/**
 * @brief A function to delete an item with an specified key inside the hash
 * Complexity: Linear O(n) since it has to traverse the whole list where the element can be found 
*/
void HashTable::deleteItem(int key) {
    // Get the index to delete
    int index = hashFunction(key);

    // Traverse the lists searching for the value 
    for (auto it = table[index].begin(); it != table[index].end(); ++it) {
        if ((*it)->key == key) {
            delete *it;
            it = table[index].erase(it);
            break;
        }
    }
}

/**
 * @brief A function to display the hash contents
 * Compelxity: Quadratic O(n^2) in the worst case since it traverses each cell and then each element in that cell
*/
void HashTable::displayHash() {
    // Traverse each list inside the main hash table list and print values
    for (int i = 0; i < max_size; ++i) {
        cout << "table[" << i << "]";
        for (auto x : table[i]){
            if(x != table[i].front()){
                ++this->collisions;
            }
            cout << " --> " << x->key;
        }
        cout << "\n";
    }
    cout << "Total number of collisions: " << this->collisions;
}

/**
 * @brief A function to insert a new element into the hash table managing collisions with quadratic probing 
 * Complexity: Linear O(n) since it runs in a single loop which generates new hashes until the selected cell size is 0 (empty list)
*/
void HashTable::insertQuadratic(int key){
    int i = 1;
    int index = quadraticHash(key, i);
    int prev_hash = index;
    while(this->table[index].size() > 0){
        index = quadraticHash(key, i);
        ++i;
        prev_hash = index; 
    }

    // Insert item into desired slot
    Item* it = new Item;
    it->index = index; it->key = key;
    this->table[index].push_back(it);
}

int main() {
    // Data and size of the array
    int dataset[] = {230, 248, 332, 353, 429};
    int size = sizeof(dataset) / sizeof(dataset[0]);
    
    // Create hash table
    HashTable h(size);
    
    // Add items
    for (auto i : dataset) {
        h.insertNewChaining(i);
    }
    
    cout << "Hash table chaining test\n";
    h.displayHash();
    
    // new hash table to test quadratic probing
    HashTable h2(size);

    // Add items
    for (auto i : dataset) {
        h2.insertQuadratic(i);
    }
    
    cout << "\n\nHash table quadratic probing test\n";
    h2.displayHash();
}