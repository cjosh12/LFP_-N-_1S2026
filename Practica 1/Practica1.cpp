#include <iostream>
#include <vector>
#include <string>
#include <fstream>


#include "Curso.h"
#include "Estudiante.h"
#include "Nota.h"

using namespace std;

vector<string> split(string linea, char delimiter)
{
    vector<string> compuesto;
    string actual = "";
    for (char c : linea)
    {
        if (c == delimiter)
        {
            compuesto.push_back(actual);
            actual = "";
        }
        else
        {
            actual += c;
        }
    }
    compuesto.push_back(actual);
    return compuesto;
}
bool abrirArchivo(string nombreArchivo, ifstream &archivo)
{
    archivo.open(nombreArchivo);
    if (!archivo.is_open())
    {
        cout << "No se pudo abrir el archivo: " << nombreArchivo << endl;
        return false;
    }
    return true;
}

void procesarArchivo(string nombreArchivo, vector<Curso> &cursos, vector<Estudiante> &estudiantes, vector<Nota> &notas)
{
    ifstream archivo;
    if (!abrirArchivo(nombreArchivo, archivo))
    {
        return;
    }
    string linea;
    while (getline(archivo, linea))
    {
        vector<string> datos = split(linea, ',');
        if (nombreArchivo == "cursos.lfp" && datos.size() == 5)
        {
            int id = stoi(datos[0]);
            string nombre = datos[1];
            int creditos = stoi(datos[2]);
            int semestre = stoi(datos[3]);
            string carrera = datos[4];

            Curso c(id, nombre, creditos, semestre, carrera);
            cursos.push_back(c);
        }
        else if (nombreArchivo == "estudiantes.lfp" && datos.size() == 5)
        {
            int carnet = stoi(datos[0]);
            string nombre = datos[1];
            string apellido = datos[2];
            string carrera = datos[3];
            int semestre = stoi(datos[4]);

            Estudiante e(carnet, nombre, apellido, carrera, semestre);
            estudiantes.push_back(e);
        }
        else if (nombreArchivo == "notas.lfp" && datos.size() == 5)
        {
            int carnet = stoi(datos[0]);
            int codigo_curso = stoi(datos[1]);
            float nota = stof(datos[2]);
            string ciclo = datos[3];
            int anio = stoi(datos[4]);

            Nota n(carnet, codigo_curso, nota, ciclo, anio);
            notas.push_back(n);
        }
        else
        {
            cout << "Linea no valida en el archivo: " << linea << endl;
        }
    }
    archivo.close();
}

void reporteTopEstudiantes(string archivoHtml, vector<Estudiante> estudiantes, vector<Nota> notas)
{
    ofstream reporte(archivoHtml);
    if(!reporte.is_open())
    {
        cout << "No se pudo crear el archivo de reporte: " << archivoHtml << endl;
        return;
    }
    vector<pair<Estudiante, float>> promedios;
    for (const Estudiante& e : estudiantes)
    {
        float sumaNotas = 0;
        int contadorNotas = 0;
        for (const Nota& n : notas)
        {
            if (n.getCarnet() == e.getCarnet())
            {
                sumaNotas += n.getNota();
                contadorNotas++;
            }
        }
        float promedio = contadorNotas > 0 ? sumaNotas / contadorNotas : 0;
        promedios.push_back(make_pair(e, promedio));
    }
for(int i = 0; i < promedios.size(); i++)
    {
        for(int j = 0; j < promedios.size() - 1; j++)
        {
            if(promedios[j].second < promedios[j + 1].second)
            {
                swap(promedios[j], promedios[j + 1]);
            }
        }
    }
    reporte << "<html><head><title>Top Estudiantes</title></head><body>";
    reporte << "<h1>Top Estudiantes</h1>";
    reporte << "<table border='1'><tr><th>Carnet</th><th>Nombre</th><th>Apellido</th><th>Carrera</th><th>Semestre</th><th>Promedio</th></tr>";
    for (int i = 0; i < min(10, (int)promedios.size()); i++)
    {
        const Estudiante& e = promedios[i].first;
        float promedio = promedios[i].second;
        reporte << "<tr><td>" << e.getCarnet() << "</td><td>" << e.getNombre() << "</td><td>" << e.getApellido() << "</td><td>" 
        << e.getCarrera() << "</td><td>" << e.getSemestre() << "</td><td>" << promedio << "</td></tr>";
    }
    reporte << "</table></body></html>";
    reporte.close();
    
}

void reporteRendimientoEstudiantes(string archivoHtml, vector<Estudiante> estudiantes, vector<Nota> notas)
{
    ofstream reporte(archivoHtml);
    if(!reporte.is_open())
    {
        cout << "No se pudo crear el archivo de reporte: " << archivoHtml << endl;
        return;
    }

    reporte << "<html><head><title>Rendimiento por Estudiante</title></head><body>";
    reporte << "<h1>Reporte de Rendimiento por Estudiante</h1>";

    for (const Estudiante& e : estudiantes)
    {
        float sumaNotas = 0;
        int contadorNotas = 0;

        reporte << "<h2>Estudiante: " << e.getNombre() << " " << e.getApellido() 
                << " (Carnet: " << e.getCarnet() << ")</h2>";
        reporte << "<p>Carrera: " << e.getCarrera() << " | Semestre: " << e.getSemestre() << "</p>";

        reporte << "<table border='1'><tr><th>Código Curso</th><th>Nota</th><th>Ciclo</th><th>Año</th></tr>";

        for (const Nota& n : notas)
        {
            if (n.getCarnet() == e.getCarnet())
            {
                reporte << "<tr><td>" << n.getCodigoCurso() << "</td><td>" << n.getNota() 
                        << "</td><td>" << n.getCiclo() << "</td><td>" << n.getAnio() << "</td></tr>";
                sumaNotas += n.getNota();
                contadorNotas++;
            }
        }

        reporte << "</table>";

        float promedio = contadorNotas > 0 ? sumaNotas / contadorNotas : 0;
        reporte << "<p><b>Promedio General: " << promedio << "</b></p><hr>";
    }

    reporte << "</body></html>";
    reporte.close();
}

