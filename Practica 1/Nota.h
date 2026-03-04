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
    int getCarnet() const
    {
        return carnet;
    }   
    
    int getCodigoCurso() const
    {
        return codigo_curso;
    }
   
    float getNota() const
    {
        return nota;
    }
    
    std::string getCiclo() const
    {
        return ciclo;
    }
    
    int getAnio() const
    {
        return anio;
    }
    
};

#endif