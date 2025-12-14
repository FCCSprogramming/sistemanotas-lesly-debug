#include "../include/sistema.h"
#include <iostream>
#include <limits> 
#include <string>

using namespace std;

void mostrarMenu() {
    cout << "\n=== SISTEMA DE GESTION ACADEMICA UNI (POO) ===\n";
    cout << "1. Registrar Estudiante\n";
    cout << "2. Registrar Curso\n";
    cout << "3. Inscribir Estudiante a Curso\n";
    cout << "4. Registrar Notas Parciales\n";
    cout << "------------------------------------------\n";
    cout << "5. Listar Estudiantes (Reporte Polimórfico)\n";
    cout << "6. Generar Boleta de Notas (por ID)\n";
    cout << "7. Exportar Aprobados a Archivo de Texto\n";
    cout << "------------------------------------------\n";
    cout << "8. Guardar Datos (Binario)\n";
    cout << "9. Cargar Datos (Binario)\n";
    cout << "10. Acceso Aleatorio a Registro (Directo)\n";
    cout << "0. Salir\n";
    cout << "Seleccione una opción: ";
}

int main() {
    Sistema sistema;
    int opcion;
    string id;

    sistema.cargarDatosBinario(); 

    do {
        mostrarMenu();
        if (!(cin >> opcion)) {
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            opcion = -1; 
            continue;
        }
        cin.ignore(numeric_limits<streamsize>::max(), '\n'); 

        switch (opcion) {
            case 1: sistema.registrarEstudiante(); break;
            case 2: sistema.registrarCurso(); break;
            case 3: sistema.inscribirEstudianteACurso(); break;
            case 4: sistema.registrarNotas(); break;
            case 5: sistema.listarEstudiantes(); break;
            case 6: 
                cout << "Ingrese el ID del estudiante para la boleta: ";
                getline(cin, id);
                sistema.generarBoleta(id);
                break;
            case 7: sistema.exportarAprobadosATexto(); break;
            case 8: sistema.guardarDatosBinario(); break;
            case 9: sistema.cargarDatosBinario(); break;
            case 10: sistema.accesoAleatorioRegistro(); break;
            case 0: 
                cout << "Saliendo del sistema. Guardando datos...\n";
                sistema.guardarDatosBinario(); 
                break;
            default: cout << "Opción no válida. Intente de nuevo.\n";
        }
    } while (opcion != 0);

    return 0;
}