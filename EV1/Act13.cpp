/* EQUIPO 5
- Ana Valeria Guzman Vazquez    / A01643224
- Clarissa Gardea Coronado      / A01569420
- Jorge Alejandro Gonzalez Diaz / A00344893
*/

#include <iostream>
#include<string>
#include<vector>
#include <fstream>
#include <sstream>
using namespace std;

struct Data{
  string message;
  int month, day, hour, min, sec;
  int score;  // Puntuacion segun datos
};

int binarySearch(vector<Data> vect, int target){ 
    int low = 0; int high = vect.size() - 1; int middle = 0;
    while(low <= high){
        middle = low + ((high - low) / 2);
        if(vect[middle].score + 2592000 * vect[middle].month == target){  // Considerar valor del mes
            return middle;                  // Caso donde se encuentra
        }else if(vect[middle].score + 2592000 * vect[middle].month < target){
            low = middle + 1;
        }else{
            high = middle - 1;
        }
    }
    return middle;  // No se encontro el elemento
}

// Worst -> O(n^2), Best -> O(n)
void bubble_sort(vector<Data> &vect){
    Data aux; bool swapped = false;      // Variable para romper loop cuando este ordenado
    for(int count=0; count < vect.size() - 1; count++){  // Loop primario
        swapped = false; 
        for(int sub_count = 0; sub_count < vect.size() - 1; sub_count++){  // SLoop secundario
            if(vect[sub_count].score > vect[sub_count + 1].score){
                aux = vect[sub_count];
                vect[sub_count] = vect[sub_count + 1];  // SWAP
                vect[sub_count + 1] = aux;
                swapped = true;
            } 
        }
        if(!swapped){break;}  // Si no se hizo swap signific que ya estaba ordenado
    }
}  

void get_inputs(int &mes_inicio, int &dia_inicio, int &hora_inicio, int &min_inicio, int &sec_inicio, int &mes_fin, int &dia_fin, int &hora_fin, int &min_fin, int &sec_fin){
  cerr << "¡Bienvenidos al registro de reportes!" << endl;
  cerr << "INICIO DE BUSQUEDA\n";
  cerr << "Junio = 1 / Julio = 2 / Agosto = 3 / Septiembre = 4 / Octubre = 5\n";
  cerr << "Seleccionar numero de mes (1-5): ";
  cin >> mes_inicio;
  cerr << "Seleccionar numero dia: (1 - 30): ";
  cin >> dia_inicio;
  cerr << "Seleccionar numero de hora: ";
  cin >> hora_inicio;
  cerr << "Seleccionar numero de minuto: ";
  cin >> min_inicio;
  cerr << "Seleccionar numero de segundo: ";
  cin >> sec_inicio;
  
  cerr << "\nFIN DE BUSQUEDA\n";
  cerr << "Seleccionar numero de mes (1-5): ";
  cin >> mes_fin;
  cerr << "Seleccionar numero dia: (1 - 30): ";
  cin >> dia_fin;
  cerr << "Seleccionar numero de hora: ";
  cin >> hora_fin;
  cerr << "Seleccionar numero de minuto: ";
  cin >> min_fin;
  cerr << "Seleccionar numero de segundo: ";
  cin >> sec_fin;
}

int main(){
  // Clear console
  system("cls");

  // Vectores
  vector<string> v; // Vector para almacenar mensajes de bitacora
  vector<vector<Data>> mainVect;
  vector<Data> id_jun, id_jul, id_aug, id_sep, id_oct;  // Organizar segun mes en diferentes vectores

  // Variables
  string month_str, time_str, ip_str, day_str;  

  // Almacenar el archivo de datos en objeto tipo ifstream
  ifstream InputFile("bitacora.txt");
  // Abrir archivo de output
  ofstream OutputFile("bitacoraSort.txt");  
  
  // Checar si hay error al abrir archivo
  if (!InputFile)
  {
    cerr<<"Error opening the input file."<<endl;
    return 0;
  }

  // Almacenar cada linea del archivo y agregarla a vector v
  string entry;
  while(InputFile)
    {
      getline(InputFile, entry);
      v.push_back(entry);        // Agregar string a vector
      stringstream SS(entry);  
      SS >> month_str >> day_str >> time_str >> ip_str;  // Split String

      int month;
      if(month_str == "Jun"){
        month = 1;
      }
      else if(month_str == "Jul"){
        month = 2;
      }
      else if(month_str == "Aug"){
        month = 3;
      }
      else if(month_str == "Sep"){
        month = 4;
      }
      else if(month_str == "Oct"){
        month = 5;
      }

      // Añadir al vector de datos un struct por cada nuevo mensaje
      Data dato = {entry, month, stoi(day_str),  // Mensaje, mes, dia
                    stoi(time_str.substr(0, 2)),  // Hora
                    stoi(time_str.substr(3, 2)),  // Minuto
                    stoi(time_str.substr(6, 2))}; // Segundos

      int total_segs = dato.day * 86400 + dato.hour * 3600 + dato.min * 60 + dato.sec;  // Sacar una puntuacion
      dato.score = total_segs;  // Update score
      
      // INICIA PARTE DE SORTING
      switch(dato.month){
        case 1:
          id_jun.push_back(dato);
          break;
        case 2:
          id_jul.push_back(dato);
          break;
        case 3:
          id_aug.push_back(dato);
          break;
        case 4:
          id_sep.push_back(dato);
          break;
        case 5:
          id_oct.push_back(dato);
          break;
      }
    } // End while
  
    // El vector master
    mainVect.push_back(id_jun);
    mainVect.push_back(id_jul);
    mainVect.push_back(id_aug);
    mainVect.push_back(id_sep);
    mainVect.push_back(id_oct);

    //Bubble sort para cada vector (de cada mes individualmente)
    bubble_sort(mainVect[0]);
    bubble_sort(mainVect[1]);
    bubble_sort(mainVect[2]);
    bubble_sort(mainVect[3]);
    bubble_sort(mainVect[4]);
  
  // INPUT DE USUARIO
  int mes_inicio, dia_inicio, hora_inicio, min_inicio, sec_inicio;
  int mes_fin, dia_fin, hora_fin, min_fin, sec_fin;

  get_inputs(mes_inicio, dia_inicio, hora_inicio, min_inicio, sec_inicio, 
            mes_fin, dia_fin, hora_fin, min_fin, sec_fin);

  //Calculo de puntuaciones
  int score_start = mes_inicio * 2592000 + dia_inicio * 86400 + hora_inicio * 3600 + min_inicio * 60 + sec_inicio;
  int score_end = mes_fin * 2592000 + dia_fin * 86400 + hora_fin * 3600 + min_fin * 60 + sec_fin;

  // BUSQUEDA BINARIA
  int found1 = 0; int found2 = 0;  // Indice del valor inicial y final encontrados
  vector<Data> unificado;
  for(int i = 0; i < mainVect.size(); i++){ // Unificar datos
    for(Data d : mainVect[i]){
      unificado.push_back(d);  //Este vector tiene todos los datos ordenados
    }
  }
  vector<Data> final; // Vector con datos ordenados y filtrados
  found1 = binarySearch(unificado, score_start);
  found2 = binarySearch(unificado, score_end);

  // Adaptar
  if(unificado[found1].score + 2592000 * unificado[found1].month < score_start){
    found1 ++;
  }
  if (unificado[found2].score + 2592000 * unificado[found2].month > score_end){
    found2 --;
  }

  // VECTOR FINAL FILTRADO
  for(int i = found1; i < found2 + 1; i++){
    final.push_back(unificado[i]);
  }
  cerr << found2 - found1 << endl;
  for(Data k : final){
    OutputFile << k.message << endl;
  }
  cerr << "\nProgram exited correctly";
  // Cerrar archivos
  OutputFile.close();
  InputFile.close();
  return 0;
}