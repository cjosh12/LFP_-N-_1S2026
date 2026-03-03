#ifndef NOTA_H
#define NOTA_H


#include <iostream>
#include <string>

class Nota
{
private:
    int carnet;
    int codigo_curso;
    float nota;
    std::string ciclo;
    int anio;
public:
    Nota(int carnet, int codigo_curso, float nota, std::string ciclo, int anio)
    {
        this->carnet = carnet;
        this->codigo_curso = codigo_curso;
        this->nota = nota;
        this->ciclo = ciclo;
        this->anio = anio;
    }   
    int getCarnet()
    {
        return carnet;
    }   
    int setCarnet(int carnet)
    {
        this->carnet = carnet;
    }
    int getCodigoCurso()
    {
        return codigo_curso;
    }
    int setCodigoCurso(int codigo_curso)
    {
        this->codigo_curso = codigo_curso;
    }
    float getNota()
    {
        return nota;
    }
    float setNota(float nota)
    {
        this->nota = nota;
    }
    std::string getCiclo()
    {
        return ciclo;
    }
    std::string setCiclo(std::string ciclo)
    {
        this->ciclo = ciclo;
    }
    int getAnio()
    {
        return anio;
    }
    int setAnio(int anio)
    {
        this->anio = anio;
    }
};

#endif