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
    int getCarnet()
    {
        return carnet;
    }
    int setCarnet(int carnet)
    {
        this->carnet = carnet;
    }
    std::string getNombre()
    {
        return nombre;
    }
    std::string setNombre(std::string nombre)
    {
        this->nombre = nombre;
    }
    std::string getApellido()
    {
        return apellido;
    }
    std::string setApellido(std::string apellido)
    {
        this->apellido = apellido;
    }
    std::string getCarrera()
    {
        return carrera;
    }
    std::string setCarrera(std::string carrera)
    {
        this->carrera = carrera;
    }
    int getSemestre()
    {
        return semestre;
    }
    int setSemestre(int semestre)
    {
        this->semestre = semestre;
    }

};
#endif