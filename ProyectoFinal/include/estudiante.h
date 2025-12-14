#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H

#include "persona.h"
#include "inscripcion.h"
#include <vector>
#include <memory> 
#include <numeric>
using namespace std;

class Curso;

class Estudiante : public Persona { 
private:
    string carrera;
    int ciclo;
    vector<Inscripcion> cursosInscritos; 

    const vector<unique_ptr<Curso>>* catalogoCursosRef; 

public:
    // Constructores
    Estudiante() : Persona(), carrera(""), ciclo(0), catalogoCursosRef(nullptr) {}
    Estudiante(const string& id, const string& nombre, const string& carrera, int ciclo)
        : Persona(id, nombre), carrera(carrera), ciclo(ciclo), catalogoCursosRef(nullptr) {
            cout << "[INFO] Constructor con this usado para ID: " << this->id <<endl;
        }
    
    Estudiante(const Estudiante& other) = default; 

    void setCatalogoRef(const std::vector<std::unique_ptr<Curso>>* ref) { catalogoCursosRef = ref; }

    const std::vector<Inscripcion>& getCursosInscritos() const { return cursosInscritos; }

    void inscribirCurso(const std::string& codCurso);
    Inscripcion* buscarInscripcion(const std::string& codCurso);

    void mostrarInfo() const override; 
    float calcularDesempeño() const override;

    void escribirBinario(std::fstream& fs) const override;
    void leerBinario(std::fstream& fs) override;

    static size_t getSizeInFile();

private:
    float obtenerCreditosCurso(const string& codCurso) const;
};

#endif // ESTUDIANTE_H