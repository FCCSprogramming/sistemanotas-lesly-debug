#include "../include/curso.h"
#include <cstring>

using namespace std;

void Curso::mostrarInfo() const {
    cout << "  [CURSO] Codigo: " << codigo << " | " << nombre << " | Creditos: " << creditos << " | Profesor: " << profesor << endl;
}

void Curso::escribirBinario(fstream& fs) const {
    char cod_arr[MAX_STR] = "";
    strncpy(cod_arr, codigo.c_str(), MAX_STR - 1);
    fs.write(cod_arr, MAX_STR);

    char nom_arr[MAX_STR] = "";
    strncpy(nom_arr, nombre.c_str(), MAX_STR - 1);
    fs.write(nom_arr, MAX_STR);

    fs.write(reinterpret_cast<const char*>(&creditos), sizeof(creditos));
    
    char prof_arr[MAX_STR] = "";
    strncpy(prof_arr, profesor.c_str(), MAX_STR - 1);
    fs.write(prof_arr, MAX_STR);
}

void Curso::leerBinario(fstream& fs) {
    char cod_arr[MAX_STR];
    fs.read(cod_arr, MAX_STR);
    codigo = cod_arr;

    char nom_arr[MAX_STR];
    fs.read(nom_arr, MAX_STR);
    nombre = nom_arr;

    fs.read(reinterpret_cast<char*>(&creditos), sizeof(creditos));

    char prof_arr[MAX_STR];
    fs.read(prof_arr, MAX_STR);
    profesor = prof_arr;
}

size_t Curso::getSizeInFile() {
    return MAX_STR * 3 + sizeof(int);
}