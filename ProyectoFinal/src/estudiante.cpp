#include "../include/estudiante.h"
#include "../include/curso.h" 
#include <cstring>
#include <algorithm>

using namespace std;

void Estudiante::mostrarInfo() const {
    cout << "  [ESTUDIANTE] ID: " << id << " | Nombre: " << nombre 
         << " | Carrera: " << carrera << " | Ciclo: " << ciclo << endl;
}

float Estudiante::obtenerCreditosCurso(const std::string& codCurso) const {
    if (!catalogoCursosRef) return 0.0f;

    // Bucle basado en rango (Requerido 3.6)
    for (const auto& curso_ptr : *catalogoCursosRef) {
        if (curso_ptr->getCodigo() == codCurso) {
            return static_cast<float>(curso_ptr->getCreditos());
        }
    }
    return 0.0f;
}

float Estudiante::calcularDesempeño() const {
    if (cursosInscritos.empty() || !catalogoCursosRef) return 0.0f;

    float sumaPonderada = 0.0f;
    int totalCreditos = 0;

    for (const auto& insc : cursosInscritos) {
        float creditos = obtenerCreditosCurso(insc.getCodCurso());
        sumaPonderada += insc.getNotas().calcularPromedio() * creditos;
        totalCreditos += static_cast<int>(creditos);
    }

    if (totalCreditos == 0) return 0.0f;

    return sumaPonderada / totalCreditos;
}

void Estudiante::inscribirCurso(const std::string& codCurso) {
    Inscripcion* insc = buscarInscripcion(codCurso);
    if (insc == nullptr) {
        cursosInscritos.push_back(Inscripcion(codCurso));
    }
}

Inscripcion* Estudiante::buscarInscripcion(const std::string& codCurso) {
    for (auto& insc : cursosInscritos) {
        if (insc.getCodCurso() == codCurso) {
            return &insc;
        }
    }
    return nullptr;
}

// --- Persistencia ---

void Estudiante::escribirBinario(fstream& fs) const {
    Persona::escribirBinario(fs);

    char carrera_arr[MAX_STR] = "";
    strncpy(carrera_arr, carrera.c_str(), MAX_STR - 1);
    fs.write(carrera_arr, MAX_STR);
    fs.write(reinterpret_cast<const char*>(&ciclo), sizeof(ciclo));

    size_t numCursos = cursosInscritos.size();
    fs.write(reinterpret_cast<const char*>(&numCursos), sizeof(size_t));
    for (const auto& insc : cursosInscritos) {
        insc.escribirBinario(fs);
    }
}

void Estudiante::leerBinario(fstream& fs) {
    Persona::leerBinario(fs);

    char carrera_arr[MAX_STR];
    fs.read(carrera_arr, MAX_STR);
    carrera = carrera_arr;
    fs.read(reinterpret_cast<char*>(&ciclo), sizeof(ciclo));

    size_t numCursos;
    fs.read(reinterpret_cast<char*>(&numCursos), sizeof(size_t));
    cursosInscritos.clear();
    for (size_t i = 0; i < numCursos; ++i) {
        Inscripcion insc;
        insc.leerBinario(fs);
        cursosInscritos.push_back(std::move(insc));
    }
}