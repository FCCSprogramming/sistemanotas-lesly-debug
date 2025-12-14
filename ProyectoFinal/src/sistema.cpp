#include "../include/sistema.h"
#include <iostream>
#include <limits> 
#include <sstream>
#include <algorithm>
#include <memory>

using namespace std;

Sistema::Sistema() {
}

void Sistema::actualizarReferencias() {
    for (auto& est_ptr : listaEstudiantes) {
        est_ptr->setCatalogoRef(&catalogoCursos);
    }
}

void Sistema::registrarEstudiante() {
    string id, nombre, carrera;
    int ciclo;
    cout << "\n--- Registrar Estudiante ---\n";
    cout << "ID/Codigo: "; getline(cin, id);
    if (buscarEstudiante(id)) {
        cout << "Error: Ya existe un estudiante con ese ID.\n";
        return;
    }
    cout << "Nombre: "; getline(cin, nombre);
    cout << "Carrera: "; getline(cin, carrera);
    cout << "Ciclo: "; cin >> ciclo;
    cin.ignore(numeric_limits<streamsize>::max(), '\n');

    listaEstudiantes.push_back(
        make_unique<Estudiante>(id, nombre, carrera, ciclo)
    );
    listaEstudiantes.back()->setCatalogoRef(&catalogoCursos); 

    cout << "Estudiante " << nombre << " registrado exitosamente.\n";
}

void Sistema::listarEstudiantes() const {
    cout << "\n--- Listado de Estudiantes ---\n";
    if (listaEstudiantes.empty()) {
        cout << "No hay estudiantes registrados.\n";
        return;
    }
    
    // Uso de Polimorfismo: llama a Estudiante::mostrarInfo() (Requerido 3.3)
    for (const auto& est_ptr : listaEstudiantes) { 
        est_ptr->mostrarInfo();
        cout << "  Desempeño (PP): " << est_ptr->calcularDesempeño() << endl;
        cout << "------------------------------\n";
    }
}

const string BINARY_FILE = "../data/bd_academica.dat";
const string TEXT_FILE = "../data/aprobados.txt";

void Sistema::guardarDatosBinario() const {
    fstream fs(BINARY_FILE, ios::out | ios::binary | ios::trunc); 
    if (!fs.is_open()) {
        cerr << "Error al abrir el archivo binario para escritura.\n";
        return;
    }

    size_t numEstudiantes = listaEstudiantes.size();
    fs.write(reinterpret_cast<const char*>(&numEstudiantes), sizeof(size_t));
    for (const auto& est_ptr : listaEstudiantes) {
        est_ptr->escribirBinario(fs);
    }

    size_t numCursos = catalogoCursos.size();
    fs.write(reinterpret_cast<const char*>(&numCursos), sizeof(size_t));
    for (const auto& curso_ptr : catalogoCursos) {
        curso_ptr->escribirBinario(fs);
    }

    fs.close();
    cout << "\n[PERSISTENCIA] Base de datos guardada en archivo binario '" << BINARY_FILE << "'.\n";
}

void Sistema::cargarDatosBinario() {
    fstream fs(BINARY_FILE, ios::in | ios::binary);
    if (!fs.is_open()) {
        cout << "\n[PERSISTENCIA] Archivo binario no encontrado o vacío. Iniciando base de datos vacía.\n";
        return;
    }

    listaEstudiantes.clear();
    catalogoCursos.clear();

    size_t numEstudiantes = 0;
    fs.read(reinterpret_cast<char*>(&numEstudiantes), sizeof(size_t));

    for (size_t i = 0; i < numEstudiantes; ++i) {
        auto est_ptr = make_unique<Estudiante>();
        est_ptr->leerBinario(fs);
        listaEstudiantes.push_back(std::move(est_ptr));
    }

    size_t numCursos = 0;
    fs.read(reinterpret_cast<char*>(&numCursos), sizeof(size_t));

    for (size_t i = 0; i < numCursos; ++i) {
        auto curso_ptr = make_unique<Curso>();
        curso_ptr->leerBinario(fs);
        catalogoCursos.push_back(std::move(curso_ptr));
    }

    fs.close();
    actualizarReferencias(); 
    cout << "\n[PERSISTENCIA] Datos cargados exitosamente desde '" << BINARY_FILE << "'.\n";
}

void Sistema::exportarAprobadosATexto() const {
    ofstream archivo(TEXT_FILE); // Archivo de texto (Requerido 3.5)
    if (!archivo.is_open()) {
        cerr << "Error al crear el archivo de texto.\n";
        return;
    }

    archivo << "--- Listado de Estudiantes con Promedio Ponderado Satisfactorio (>= 10.5) ---\n";
    
    for (const auto& est_ptr : listaEstudiantes) { 
        float promedioPonderado = est_ptr->calcularDesempeño();
        if (promedioPonderado >= 10.5f) {
            archivo << "ID: " << est_ptr->getId()<< " | Nombre: " << est_ptr->getNombre()<< " | Carrera: " << est_ptr->getCarrera()<< " | Promedio Ponderado: " << promedioPonderado << "\n";
        }
    }

    archivo.close();
    cout << "\n[PERSISTENCIA] Estudiantes aprobados exportados a '" << TEXT_FILE << "'.\n";
}

void Sistema::accesoAleatorioRegistro() {
    string codCurso;
    cout << "\n--- Acceso Aleatorio (Directo) a Curso ---\n";
    cout << "Ingrese el código del curso a buscar: ";
    getline(cin, codCurso);
    
    fstream fs_cursos("../data/cursos.dat", ios::out | ios::binary | ios::trunc);
    if (!fs_cursos.is_open()) {
        cerr << "Error: No se pudo crear el archivo temporal de cursos.\n";
        return;
    }
    
    for(const auto& curso_ptr : catalogoCursos) {
        curso_ptr->escribirBinario(fs_cursos);
    }
    fs_cursos.close();

    size_t registroEncontrado = -1;
    for(size_t i = 0; i < catalogoCursos.size(); ++i) {
        if (catalogoCursos[i]->getCodigo() == codCurso) {
            registroEncontrado = i;
            break;
        }
    }
    
    if (registroEncontrado != (size_t)-1) {
        size_t tamRegistro = Curso::getSizeInFile();
        long posicion = (long)registroEncontrado * tamRegistro;
        
        fstream fs_read("../data/cursos.dat", ios::in | ios::binary);
        fs_read.seekg(posicion, ios::beg); // Función seekg (Requerido 3.5)

        Curso cursoLeido;
        cursoLeido.leerBinario(fs_read);
        fs_read.close();

        cout << "\n[ACCESO ALEATORIO EXITOSO] Posición (bytes): " << posicion << endl;
        cursoLeido.mostrarInfo();
    } else {
        cout << "Curso con código " << codCurso << " no encontrado.\n";
    }
}