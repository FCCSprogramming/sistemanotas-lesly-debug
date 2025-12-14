#ifndef CURSO_H
#define CURSO_H

#include <string>
#include <iostream>
#include <fstream>
#include "persona.h"
using namespace std;
class Curso{
private:
    string codigo;
    string nombre;
    int creditos;
    string profesor;

public:
    Curso() : codigo(""), nombre(""), creditos(0), profesor("") {}
    Curso(const string& cod, const string& nom, int cred, const string& prof)
        : codigo(cod), nombre(nom), creditos(cred), profesor(prof) {}
    
    Curso(const Curso& other) = default;

    string getCodigo() const { return codigo; }
    string getNombre() const { return nombre; }
    int getCreditos() const { return creditos; }
    string getProfesor() const { return profesor; }

    void mostrarInfo() const;

    void escribirBinario(fstream& fs) const;
    void leerBinario(fstream& fs);

    static size_t getSizeInFile();
};

#endif // CURSO_H