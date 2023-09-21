#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <sstream>

using namespace std;

// Complejidad bubble sort
// Worst -> O(n^2), Best -> O(n)
void ordena_burbuja(vector<int> &vect){
    int aux; bool swapped = false;      // Variable para romper loop cuando este ordenado
    for(int count=0; count < vect.size() - 1; count++){  // Loop primario
        swapped = false; 
        for(int sub_count = 0; sub_count < vect.size() - 1; sub_count++){  // Loop secundario
            if(vect[sub_count] > vect[sub_count + 1]){
                aux = vect[sub_count];
                vect[sub_count] = vect[sub_count + 1];  // Swap values
                vect[sub_count + 1] = aux;
                swapped = true;
            } 
        }
        if(!swapped){break;}  // Si no hubo swap significa que los valores ya estaban ordenados
    }
}   

// Complejidad seleccion
// Worst -> O(n^2), Best -> O(n^2)
void ordena_seleccion(vector<int> &vect){
    int aux; int min_index;                                 // Indice de vector para el numero mas pequeno
    for(int count = 0; count < vect.size(); count++){   // Loop primario
        min_index = count;
        for(int sub_count = count; sub_count < vect.size(); sub_count++){  // Loop secundario
            if(vect[sub_count] < vect[min_index]){
                min_index = sub_count;      // Tomar indice del menor en el set
            }
            aux = vect[count];
            vect[count] = vect[min_index];  // Swap
            vect[min_index] = aux;
        }
    }
}

// Complejidad insercion
// Worst -> O(n^2), Best -> O(n)
void ordena_insercion(vector<int> &vect){
    int aux; int sub_count; int key;
    for(int count = 1; count < vect.size(); count ++){
        sub_count = count - 1;
        key = vect[count];     // Guardar la key antes de asignar otro valor a esa posicion
        while(sub_count >= 0 && vect[sub_count] > key){
            vect[sub_count + 1] = vect[sub_count];
            sub_count --;
        }
        vect[sub_count + 1] = key;  // Aactualizar

    }
}

/*
void combinar(vector<int> &vect, int inf, int mid, int sup){
    int size1 = mid - inf + 1;
    int size2 = sup - mid; 
    // Hacer arreglos nuevos
    vector<int> l1, l2;
    // Llenar los arreglos
    for(int i = 0; i < size1 - 1; i++){
        l1[i] = vect[i];
    }
    for(int j = size1; j < size2 - 1; j++){
        l2[j] = 
    }

}
*/

void ordena_merge(vector<int> &vect, int inf, int sup){
   // Partir el vector en series de 2
   int mid = (sup + inf) / 2;
}

int busq_secuencial(vector<int> vect, int target){
    for(int i: vect){       // Iterar sobre cada uno de los elementos
        if(i == target){    // Si se encuentra retornarlo
            return i;   
        }
    }
    return -1;      // No se encontro el elemento
}

int busq_binaria(vector<int> vect, int target){  // Metodo iterativo
    int low = 0; int high = vect.size() - 1; int middle = 0;
    while(low <= high){
        middle = low + ((high - low) / 2);
        if(vect[middle] == target){
            return middle;                  // Caso donde se encuentra el dato
        }else if(vect[middle] < target){    // Si no, hacer un ajuste de limites
            low = middle + 1;
        }else{
            high = middle - 1;
        }
    }
    return -1;  // No se encontro el elemento
}

// Metodo recursivo
int busq_binaria_recur(vector<int> vect, int target, int low, int high){
    if(low > high){ return -1;}             // Caso en el que el elemento no fue encontrado
    int middle = low + (high - low) / 2;    // Valor medio
    if(vect[middle] == target){   
        return middle;                      // Si elemento ffue encontrado no hacer llamada recursiva
    }else if (vect[middle] < target){       // Llamadas recursivas segun limites
        low = middle + 1;
        return(busq_binaria_recur(vect, target, low, high));
    }else{
        high = middle - 1;
        return(busq_binaria_recur(vect, target, low, high));
    }
}

int main() {
    vector <int> vect {128, 321, 23, 12, 1, 24, 76, 43, 66};        
    cout << "Ordenamiento por seleccion" << endl;
    cout << "Array original: " ;
    for(int i: vect){
        cout << i << ", ";
    }
    cout << endl;
    ordena_seleccion(vect);
    cout << "Array ordenado: " ;
    for(int i: vect){
        cout << i << ", ";
    }
    return 0;
}