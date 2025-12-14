#include "../include/persona.h"
#include <cstring>

using namespace std;

void Persona::escribirBinario(fstream& fs) const {
    char id_arr[MAX_STR] = "";
    strncpy(id_arr, id.c_str(), MAX_STR - 1);
    fs.write(id_arr, MAX_STR);
    
    char nombre_arr[MAX_STR] = "";
    strncpy(nombre_arr, nombre.c_str(), MAX_STR - 1);
    fs.write(nombre_arr, MAX_STR);
}

void Persona::leerBinario(fstream& fs) {
    char id_arr[MAX_STR];
    fs.read(id_arr, MAX_STR);
    id = id_arr;

    char nombre_arr[MAX_STR];
    fs.read(nombre_arr, MAX_STR);
    nombre = nombre_arr;
}