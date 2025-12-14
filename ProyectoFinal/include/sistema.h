#ifndef SISTEMA_H
#define SISTEMA_H

#include "estudiante.h"
#include "curso.h"
#include <vector>
#include <memory> 
#include <fstream>

class Sistema{
private:
    std::vector<std::unique_ptr<Estudiante>> listaEstudiantes;
    std::vector<std::unique_ptr<Curso>> catalogoCursos;

public:
    Sistema();
    ~Sistema() = default; 

    void registrarEstudiante();
    void registrarCurso();
    Estudiante* buscarEstudiante(const std::string& id);
    Curso* buscarCurso(const std::string& codigo);

    // 2. Gestión de Inscripciones y Notas
    void inscribirEstudianteACurso();
    void registrarNotas();

    // 3. Reportes
    void listarEstudiantes() const;
    void listarCursos() const;
    void generarBoleta(const std::string& id);
    void exportarAprobadosATexto() const; // Archivo de texto (Requerido 3.5)

    // 4. Persistencia (Requerido 3.5)
    void guardarDatosBinario() const; 
    void cargarDatosBinario();       
    void accesoAleatorioRegistro();  // Acceso directo (Random Access)

private:
    void actualizarReferencias();
};

#endif // SISTEMA_H