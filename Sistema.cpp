#include <iostream>
#include <string>
//Autor: Lesly Baltazar Alanoca
using namespace std;
struct Notas{
    float EP;
    float EF;
    float PP;
    float calcularPromedio() const{
        return EP*0.3+EF*0.5+PP*0.2;
    }
    string obtenerEstado() const{
        float prom=calcularPromedio();
        if(prom>=10){
            return "Aprobado";
        }
        else return "Desaprobado";
    }
};
struct Curso{
    string codigo;
    string nombre;
    int creditos;
    string profesor;
    Notas nota;
    void mostrarInformacion() const{
        cout<<"===Informacion del Curso==="<<endl;
        cout<<"Codigo: "<<codigo;
        cout<<"Creditos: "<<creditos;
        cout<<"Profesor: "<<profesor;
        cout<<"Notas: "<<nota.EP<<" "<<nota.EF<<" "<<nota.PP<<endl;
        cout<<"Promedio: "<<nota.calcularPromedio()<<endl;
        cout<<"Estado: "<<nota.obtenerEstado()<<endl;
    }
};
struct Estudiante{
    string cod;
    string nomb;
    string carrera;
    int ciclo;
    Curso cursos[6];
    int cantidadCursos;
    void mostrarDatos(){
        cout<<"Codigo: "<<cod;
        cout<<"Nombre: "<<nomb;
        cout<<"Carrera: "<<carrera;
        cout<<"Ciclo: "<<ciclo;
        for(int i=0;i<cantidadCursos;i++){
            cursos[i].mostrarInformacion();
        }
    }
};
void registrarEstudiante(Estudiante estudiantes[],int &cantidad);
void mostrarEstudiantes(Estudiante estudiantes[], int cantidad);
Estudiante* buscarEstudiante(Estudiante estudiantes[], int cantidad, string codigo);

void matricularCurso(Estudiante &estudiante);
void ingresarNotas(Estudiante &estudiante);
void mostrarCursosEstudiante(const Estudiante &estudiante);

float calcularPromedioPonderado(const Estudiante &estudiante);
int calcularTotalCreditos(const Estudiante &estudiante);
void generarBoleta(const Estudiante &estudiante);

void mostrarMejorPromedio(const Estudiante estudiantes[], int cantidad);
void estudiantesAprobadosCurso(const Estudiante estudiantes[], int cantidad, string codigoCurso);
void reporteGeneral(const Estudiante estudiantes[], int cantidad);
int main(){
    int opcion;
    Estudiante estudiantes[50];
    int cantidad=0;
    Estudiante student;
    string codCurso;
    string codigo;
    do{
        cout<<"\n=== SISTEMA DE GESTION ACADEMICA UNI ==="<<endl;
        cout<<"1. Registrar estudiante"<<endl;
        cout<<"2. Matricular curso a estudiante"<<endl;
        cout<<"3. Ingresar notas de curso"<<endl;
        cout<<"4. Mostrar informacion de estudiante"<<endl;
        cout<<"5. Generar boleta de notas"<<endl;
        cout<<"6. Mostrar menor promedio"<<endl;
        cout<<"7. Estudiantes aprobados por curso"<<endl;
        cout<<"8. Reporte general"<<endl;
        cout<<"9. Salir"<<endl;
        cout<<"Seleccione una opcion: ";
        cin>>opcion;
        cin.ignore();
        switch(opcion){
            case 1: registrarEstudiante(estudiantes,cantidad);break;
            case 2: 
            cout<<"Ingrese el codigo del estudiante: ";
            getline(cin,codigo);
            if(Estudiante* e = buscarEstudiante(estudiantes, cantidad, codigo)){
                matricularCurso(*e);
            }else{
                cout<<"Estudiante no registrado"<<endl;
            }
            break;
            case 3:
            cout << "Ingrese el código del estudiante: ";
            getline(cin, codigo);
            if(Estudiante* e = buscarEstudiante(estudiantes, cantidad, codigo)){
            ingresarNotas(*e);
            }else{
                cout << "Estudiante no encontrado." << endl;
                break;
            }
            case 4:
                mostrarEstudiantes(estudiantes,cantidad);
                break;
            case 5:
                cout<<"Ingrese el código del estudiante: ";
                getline(cin,codigo);
                if(Estudiante* e=buscarEstudiante(estudiantes,cantidad,codigo))
                    generarBoleta(*e);
                else
                    cout<<"Estudiante no encontrado."<< endl;
                break;
            case 6:
                mostrarMejorPromedio(estudiantes,cantidad);
                break;
            case 7:
                cout<<"Ingrese el código del curso: ";
                getline(cin, codCurso);
                estudiantesAprobadosCurso(estudiantes,cantidad,codCurso);
                break;
            case 8:
                reporteGeneral(estudiantes,cantidad);
                break;
        }
    }while(opcion!=9);
    return 0;
}
void registrarEstudiante(Estudiante estudiantes[],int &cantidad){
    cout<<"\n=== Registro de estudiantes ==="<<endl;
    cout<<"Codigo: ";
    getline(cin, estudiantes[cantidad].cod);
    cout << "Nombre: ";
    getline(cin, estudiantes[cantidad].nomb);
    cout << "Carrera: ";
    getline(cin, estudiantes[cantidad].carrera);
    cout << "Ciclo: ";
    cin >> estudiantes[cantidad].ciclo;
    estudiantes[cantidad].cantidadCursos = 0;
    cantidad++;
    cin.ignore();
}
void mostrarEstudiantes(Estudiante estudiantes[], int cantidad){
    if(cantidad==0){
        cout<<"\nNo hay alumnos registrados";
    }else{
        for(int i=0;i<cantidad;i++){
            estudiantes[i].mostrarDatos();
        }
    }
}
Estudiante* buscarEstudiante(Estudiante estudiantes[], int cantidad, string codigo){
    for(int i=0;i<cantidad;i++){
        if(estudiantes[i].cod==codigo){
            return &estudiantes[i];
        }
    }
    return nullptr;
}
void matricularCurso(Estudiante &student){
     cout<<"\n===Matricula de Cursos==="<<endl;
     cout<<"Ingrese el numero de cursos: ";
     cin>>student.cantidadCursos;
     for(int i=0;i<student.cantidadCursos;i++){
        cout<<"Codigo: ";
        getline(cin,student.cursos[i].codigo);
        cin.ignore();
        cout<<"Nombre: ";
        getline(cin,student.cursos[i].nombre);
        cout<<"Creditos: ";
        cin>>student.cursos[i].creditos;
        cout<<"Profesor: ";
        cin.ignore();
        getline(cin,student.cursos[i].profesor);
        student.cursos[i].nota.EP=0;
        student.cursos[i].nota.EF=0;
        student.cursos[i].nota.PP=0;
     }
}
void ingresarNotas(Estudiante &estudiante){
    cout<<"\n===Ingreso de notas==="<<endl;
    for (int i=0;i<estudiante.cantidadCursos;i++) {
        cout<<"Curso: " <<estudiante.cursos[i].nombre << endl;
        cout<<"PP: ";
        cin>>estudiante.cursos[i].nota.PP;
        cout<<"EP: ";
        cin>>estudiante.cursos[i].nota.EP;
        cout<<"EF: ";
        cin>>estudiante.cursos[i].nota.EF;
    }
}
void mostrarCursosEstudiante(const Estudiante &estudiante){
    cout<<"\n=== Cursos matriculados por "<<estudiante.nomb<<" ===\n";
    
    if(estudiante.cantidadCursos==0){
        cout<<"No tiene cursos matriculados.\n";
        return;
    }

    for(int i=0;i<estudiante.cantidadCursos;i++){
        cout<<"\nCurso "<<i + 1<<":\n";
        estudiante.cursos[i].mostrarInformacion();
        cout << endl;
    }
}

float calcularPromedioPonderado(const Estudiante &estudiante){
    float sumaPonderada = 0;
    int totalCreditos = 0;
    for(int i=0;i<estudiante.cantidadCursos;i++) {
        float prom=estudiante.cursos[i].nota.calcularPromedio();
        sumaPonderada+=prom*estudiante.cursos[i].creditos;
        totalCreditos+=estudiante.cursos[i].creditos;
    }
    return totalCreditos ? (sumaPonderada / totalCreditos) : 0;
}
int calcularTotalCreditos(const Estudiante &estudiante){
    int total = 0;
    for(int i=0;i<estudiante.cantidadCursos;i++) {
        total+=estudiante.cursos[i].creditos;
    }
    return total;
}
void generarBoleta(const Estudiante &estudiante){
    cout<<"\n=== Boleta de Notas ===\n";
    cout<<"Estudiante: "<<estudiante.nomb<<" ("<< estudiante.cod << ")\n";
    cout<<"Carrera: "<<estudiante.carrera<<" Ciclo: "<<estudiante.ciclo << "\n";
    cout<<"\nCursos:\n";

    for(int i=0;i<estudiante.cantidadCursos;i++) {
        const Curso &c=estudiante.cursos[i];
        cout<<c.codigo<<" - "<<c.nombre<<" | "<< "EP: "<<c.nota.EP<< " EF: "<< c.nota.EF<<" PP: "<< c.nota.PP<< " | Promedio: "<<c.nota.calcularPromedio()<< " | Estado: "<<c.nota.obtenerEstado()<<endl;
    }

    cout<<"\nPromedio ponderado: "<< calcularPromedioPonderado(estudiante)<<endl;
    cout<<"Total de créditos: "<<calcularTotalCreditos(estudiante)<<endl;
}

void mostrarMejorPromedio(const Estudiante estudiantes[], int cantidad){
    if(cantidad==0){
        cout<<"\nNo hay estudiantes registrados.\n";
        return;
    }

    float mejorPromedio = -1;
    string mejorEstudiante;

    for(int i=0; i<cantidad;i++){
        float promedio=calcularPromedioPonderado(estudiantes[i]);
        if(promedio>mejorPromedio){
            mejorPromedio=promedio;
            mejorEstudiante=estudiantes[i].nomb;
        }
    }

    cout<<"\n=== Estudiante con Mejor Promedio ===\n";
    cout<<"Nombre: "<<mejorEstudiante<<endl;
    cout<<"Promedio ponderado: "<<mejorPromedio<<endl;
}
void estudiantesAprobadosCurso(const Estudiante estudiantes[], int cantidad, string codigoCurso) {
    if(cantidad==0) {
        cout<<"\nNo hay estudiantes registrados.\n";
        return;
    }

    cout<<"\n=== Estudiantes Aprobados en el Curso "<<codigoCurso<<"===\n";
    bool hayAprobados=false;

    for(int i = 0;i<cantidad;i++){
        for(int j=0;j<estudiantes[i].cantidadCursos;j++) {
            if(estudiantes[i].cursos[j].codigo==codigoCurso&&estudiantes[i].cursos[j].nota.calcularPromedio() >= 10){
                cout<<"Nombre: "<<estudiantes[i].nomb<<" | Promedio: "<<estudiantes[i].cursos[j].nota.calcularPromedio()<<endl;
                hayAprobados=true;
            }
        }
    }

    if (!hayAprobados)
        cout << "Ningun estudiante aprobo el curso.\n";
}

void reporteGeneral(const Estudiante estudiantes[], int cantidad) {
    if(cantidad==0){
        cout<<"\nNo hay estudiantes registrados.\n";
        return;
    }

    cout<<"\n=== Reporte General de Estudiantes ===\n";
    for(int i = 0; i < cantidad; i++){
        cout<<"\nEstudiante: " << estudiantes[i].nomb << " (" << estudiantes[i].cod << ")\n";
        cout<<"Promedio ponderado: " << calcularPromedioPonderado(estudiantes[i]) << endl;
        cout<<"Total de creditos: " << calcularTotalCreditos(estudiantes[i]) << endl;
        cout<<"Estado general: "<<(calcularPromedioPonderado(estudiantes[i])>= 10 ? "Aprobado" : "Desaprobado")<< endl;
    }
}