#ifndef CURSO_H
#define CURSO_H


#include <iostream>
#include <string>

class Curso
{   
private:
    int codigo;
    std::string nombre;
    int creditos;
    int semestre;
    std::string carrera;
public:
    Curso(int codigo, std::string nombre, int creditos, int semestre, std::string carrera)
    {
        this->codigo = codigo;
        this->nombre = nombre;
        this->creditos = creditos;
        this->semestre = semestre;
        this->carrera = carrera;
    }
    int getCodigo() const
    {
        return codigo;
    }
    
    std::string getNombre() const
    {
        return nombre;
    }
   
    int getCreditos() const
    {
        return creditos;
    }
    
    int getSemestre() const
    {
        return semestre;
    }
    
    std::string getCarrera() const
    {
        return carrera;
    }
    

};
#endif