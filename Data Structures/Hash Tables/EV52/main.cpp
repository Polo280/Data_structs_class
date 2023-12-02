/*
Evidencia 5.2 Uso de Hash Tables
*/
#include <iostream>
#include <fstream>
#include <sstream> 
#include <list>
#include <vector>
#include <utility>
#include <cmath>

struct Data{
    int port;
    int num_accesses;
    std::vector<std::string> entries;
    Data() : num_accesses(1){};
};

class HashTable{
    private:
        // Hash table skeleton
        int capacity = 100;
        std::vector<std::list<Data>> table;
    public:
        void insertItem(Data);
        void displayTable(void);
        int hashFunction(int);
        bool isPrime(int n);
        int getPrime(int n);
        // Constructor 
        HashTable(int);
 };

HashTable::HashTable(int size) : capacity(getPrime(size)), table(capacity){
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

int HashTable::hashFunction(int port){
    // Hash the port number 
    return (port % this->capacity);
}

void HashTable::insertItem(Data data){
    bool exists = false;
    int key = data.port;
    // Get the hash to access
    int hashed_val = hashFunction(key);
    // Check whether item already exists
    Data *current;
    for(auto it : this->table[hashed_val]){
        current = &it;
        if(it.port == key){
            exists = true;
            break;
        }
    }

    if(!exists){
        // Insert in table
        this->table[hashed_val].push_back(data);
    }else{
        current->num_accesses++;
        std::string entry = data.entries[0];
    }
}

void HashTable::displayTable(void) {
    for(int i=0; i < this->table.size(); ++i){
        std::cout << "Table [" << i << "] - " ;
        for(auto it : this->table[i]){
            std::cout << it.port << " - ";
        } 
        std::cout << "\n";
    }
}

int main(){
    // Create hash table 
    HashTable ht1(10);

    std::ifstream InputFile("bitacora.txt");
    std::ofstream OutputFile("Output.txt");
    if(!InputFile || !OutputFile){std::cerr << "Error opening files\n"; return EXIT_FAILURE;}
    
    // Declare strings to read input file
    std::string date, time, ip, port, entry;
    std::string aux;
    while(InputFile){
        // Reset variables and split entry
        ip = port = "";
        getline(InputFile, entry);
        std::stringstream ss(entry);
        ss >> date >> aux;
        date += aux;
        ss >> time >> aux;

        // Manage ip/port division
        const int delimiter_index = aux.find(":");
        for(int i=0; i < aux.length(); ++i){
            if(i < delimiter_index){ip += aux[i];
            }else if (i > delimiter_index){port += aux[i];}
        }

        // Get port
        int num_port = std::stoi(port);
        // Create Data type struct
        Data access_data;
        access_data.port = num_port;
        access_data.entries.push_back(entry);
        // Add to hash table
        ht1.insertItem(access_data);
    }

    ht1.displayTable();
    std::cout << "Successfully writen results to Output.txt file\n";
    InputFile.close();
    OutputFile.close();

    return EXIT_SUCCESS;
}