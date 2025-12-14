#include "../include/inscripcion.h"
#include <cstring>

using namespace std;

void Notas::escribirBinario(fstream& fs) const {
    fs.write(reinterpret_cast<const char*>(&EP), sizeof(EP));
    fs.write(reinterpret_cast<const char*>(&EF), sizeof(EF));
    fs.write(reinterpret_cast<const char*>(&PP), sizeof(PP));
}

void Notas::leerBinario(fstream& fs) {
    fs.read(reinterpret_cast<char*>(&EP), sizeof(EP));
    fs.read(reinterpret_cast<char*>(&EF), sizeof(EF));
    fs.read(reinterpret_cast<char*>(&PP), sizeof(PP));
}

void Inscripcion::escribirBinario(fstream& fs) const {
    char cod_arr[MAX_STR] = "";
    strncpy(cod_arr, codCurso.c_str(), MAX_STR - 1);
    fs.write(cod_arr, MAX_STR);

    notas.escribirBinario(fs);
}

void Inscripcion::leerBinario(fstream& fs) {
    char cod_arr[MAX_STR];
    fs.read(cod_arr, MAX_STR);
    codCurso = cod_arr;

    notas.leerBinario(fs);
}

size_t Inscripcion::getSizeInFile() {
    return MAX_STR + 3 * sizeof(float);
}