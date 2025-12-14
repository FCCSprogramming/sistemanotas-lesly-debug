#ifndef PERSONA_H
#define PERSONA_H

#include <string>
#include <iostream>
#include <fstream>
using namespace std;

constexpr size_t MAX_STR = 50;

class Persona {
protected:
    string id;
    string nombre;

public:
    Persona() : id(""), nombre("") {}
    Persona(const std::string& id, const std::string& nombre) : id(id), nombre(nombre) {}

    Persona(const Persona& other) = default;

    std::string getId() const { return id; }
    std::string getNombre() const { return nombre; }

    virtual void mostrarInfo() const = 0; 
    virtual float calcularDesempeño() const { return 0.0f; } 

    virtual ~Persona() = default;

    virtual void escribirBinario(std::fstream& fs) const;
    virtual void leerBinario(std::fstream& fs);
};

#endif // PERSONA_H