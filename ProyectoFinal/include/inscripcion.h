#ifndef INSCRIPCION_H
#define INSCRIPCION_H

#include "persona.h" 
#include <string>
#include <fstream>
using namespace std;

struct Notas{
    float EP = 0.0f; 
    float EF = 0.0f; 
    float PP = 0.0f; 
    
    float calcularPromedio() const {
        return EP * 0.3f + EF * 0.5f + PP * 0.2f;
    }
    
    string obtenerEstado() const {
        return calcularPromedio() >= 10.5f ? "Aprobado" : "Desaprobado";
    }
    
    void escribirBinario(fstream& fs) const;
    void leerBinario(fstream& fs);
};

class Inscripcion {
private:
    string codCurso;
    Notas notas;

public:
    Inscripcion() {}
    Inscripcion(const string& cod):codCurso(cod) {}

    string getCodCurso() const { return codCurso; }
    Notas& getNotas() { return notas; }
    const Notas& getNotas() const { return notas; }

    void mostrarInfo() const;

    void escribirBinario(fstream& fs) const;
    void leerBinario(fstream& fs);

    static size_t getSizeInFile();
};

#endif // INSCRIPCION_H