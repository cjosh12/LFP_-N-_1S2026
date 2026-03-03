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
    int getCodigo()
    {
        return codigo;
    }
    int setCodigo(int codigo)
    {
        this->codigo = codigo;
    }
    std::string getNombre()
    {
        return nombre;
    }
    std::string setNombre(std::string nombre)
    {
        this->nombre = nombre;
    }
    int getCreditos()
    {
        return creditos;
    }
    int setCreditos(int creditos)
    {
        this->creditos = creditos;
    }
    int getSemestre()
    {
        return semestre;
    }
    int setSemestre(int semestre)
    {
        this->semestre = semestre;
    }
    std::string getCarrera()
    {
        return carrera;
    }
    std::string setCarrera(std::string carrera)
    {
        this->carrera = carrera;
    }

};
#endif