#ifndef ESTUDIANTE_H
#define ESTUDIANTE_H


#include <iostream>
#include <string>


class Estudiante
{
private:
    int carnet;
    std::string nombre;
    std::string apellido;
    std::string carrera;
    int semestre;

public:
    Estudiante(int carnet, std::string nombre, std::string apellido, std::string carrera, int semestre)
    {
        this->carnet = carnet;
        this->nombre = nombre;
        this->apellido = apellido;
        this->carrera = carrera;
        this->semestre = semestre;
    }
    int getCarnet() const
    {
        return carnet;
    }
    
    std::string getNombre() const
    {
        return nombre;
    }
    
    std::string getApellido() const
    {
        return apellido;
    }
    
    std::string getCarrera() const
    {
        return carrera;
    }
    
    int getSemestre() const
    {
        return semestre;
    }
   

};
#endif