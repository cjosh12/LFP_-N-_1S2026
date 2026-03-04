#include <iostream>
#include <vector>
#include <string>
#include <fstream>
#include <cmath>

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
    if (!reporte.is_open())
    {
        cout << "No se pudo crear el archivo de reporte: " << archivoHtml << endl;
        return;
    }
    vector<pair<Estudiante, float>> promedios;
    for (const Estudiante &e : estudiantes)
    {
        float sumaNotas = 0;
        int contadorNotas = 0;
        for (const Nota &n : notas)
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
    for (int i = 0; i < promedios.size(); i++)
    {
        for (int j = 0; j < promedios.size() - 1; j++)
        {
            if (promedios[j].second < promedios[j + 1].second)
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
        const Estudiante &e = promedios[i].first;
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
    if (!reporte.is_open())
    {
        cout << "No se pudo crear el archivo de reporte: " << archivoHtml << endl;
        return;
    }

    reporte << "<html><head><title>Rendimiento por Estudiante</title></head><body>";
    reporte << "<h1>Reporte de Rendimiento por Estudiante</h1>";

    for (const Estudiante &e : estudiantes)
    {
        float sumaNotas = 0;
        int contadorNotas = 0;

        reporte << "<h2>Estudiante: " << e.getNombre() << " " << e.getApellido()
                << " (Carnet: " << e.getCarnet() << ")</h2>";
        reporte << "<p>Carrera: " << e.getCarrera() << " | Semestre: " << e.getSemestre() << "</p>";

        reporte << "<table border='1'><tr><th>Código Curso</th><th>Nota</th><th>Ciclo</th><th>Año</th></tr>";

        for (const Nota &n : notas)
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

void reporteEstadisticas(string archivoHtml, vector<Curso> cursos, vector<Nota> notas)
{
    ofstream reporte(archivoHtml);
    if (!reporte.is_open())
    {
        cout << "No se pudo crear el archivo de reporte: " << archivoHtml << endl;
        return;
    }

    reporte << "<html><head><title>Estadísticas por Curso</title></head><body>";
    reporte << "<h1>Reporte de Estadísticas por Curso</h1>";

    for (const Curso &c : cursos)
    {
        vector<float> notasCurso;
        for (const Nota &n : notas)
        {
            if (n.getCodigoCurso() == c.getCodigo())
            {
                notasCurso.push_back(n.getNota());
            }
        }
        if (notasCurso.empty())
            continue;
        for (int i = 0; i < notasCurso.size(); i++)
        {
            for (int j = 0; j < notasCurso.size() - 1; j++)
            {
                if (notasCurso[j] < notasCurso[j + 1])
                {
                    float temp = notasCurso[j];
                    notasCurso[j] = notasCurso[j + 1];
                    notasCurso[j + 1] = temp;
                }
            }
        }

        float suma = 0;
        for (float nota : notasCurso)
        {
            suma += nota;
        }
        float promedio = suma / notasCurso.size();

        float mediana;
        int tamano = notasCurso.size();
        if (tamano % 2 == 0)
        {
            mediana = (notasCurso[tamano / 2 - 1] + notasCurso[tamano / 2]) / 2;
        }
        else
        {
            mediana = notasCurso[tamano / 2];
        }

        float sumaCuadrados = 0;
        for (float nota : notasCurso)
        {
            sumaCuadrados += (nota - promedio) * (nota - promedio);
        }
        float desviacionEstandar = sqrt(sumaCuadrados / notasCurso.size());

        float p25 = notasCurso[(int)round(0.25 * (notasCurso.size() - 1))];
        float p50 = notasCurso[(int)round(0.50 * (notasCurso.size() - 1))];
        float p75 = notasCurso[(int)round(0.75 * (notasCurso.size() - 1))];

        reporte << "<h2>Curso: " << c.getNombre() << " (Código: " << c.getCodigo() << ")</h2>";
        reporte << "<p>Carrera: " << c.getCarrera() << " | Semestre: " << c.getSemestre() << " | Créditos: " << c.getCreditos() << "</p>";
        reporte << "<ul>";
        reporte << "<li>Promedio: " << promedio << "</li>";
        reporte << "<li>Mediana: " << mediana << "</li>";
        reporte << "<li>Desviación estándar: " << desviacionEstandar << "</li>";
        reporte << "<li>Percentil 25: " << p25 << "</li>";
        reporte << "<li>Percentil 50: " << p50 << "</li>";
        reporte << "<li>Percentil 75: " << p75 << "</li>";
        reporte << "</ul><hr>";
    }
    reporte << "</body></html>";
    reporte.close();
}
void reporteReprobados(vector<Estudiante> estudiantes, vector<Nota> notas, string archivoHtml)
{
    ofstream reporte(archivoHtml);
    if (!reporte.is_open())
    {
        cout << "No se pudo crear el archivo de reporte: " << archivoHtml << endl;
        return;
    }

    reporte << "<html><head><title>Reporte de Reprobados</title></head><body>";
    reporte << "<h1>Reporte de Estudiantes Reprobados</h1>";

    for (const Estudiante &e : estudiantes)
    {
        bool reprobado = false;
        float sumaNotas = 0;
        int contadorNotas = 0;

        for (const Nota &n : notas)
        {
            if (n.getCarnet() == e.getCarnet())
            {
                if (n.getNota() < 61)
                {
                    reprobado = true;
                    break;
                }
                sumaNotas += n.getNota();
                contadorNotas++;
            }
        }

        if (reprobado)
        {
            float promedio = contadorNotas > 0 ? sumaNotas / contadorNotas : 0;
            reporte << "<h2>" << e.getNombre() << " (Carnet: " << e.getCarnet() << ")</h2>";
            reporte << "<p>Carrera: " << e.getCarrera() << " | Semestre: " << e.getSemestre() << "</p>";
            reporte << "<p>Promedio General: " << promedio << "</p><hr>";
        }
    }

    reporte << "</body></html>";
    reporte.close();
}

void reporteAnalisisCarrera(vector<Estudiante> estudiantes, vector<Nota> notas, string archivoHtml)
{
    ofstream reporte(archivoHtml);
    if (!reporte.is_open())
    {
        cout << "No se pudo crear el archivo de reporte: " << archivoHtml << endl;
        return;
    }

    reporte << "<html><head><title>Análisis de Carrera</title></head><body>";
    reporte << "<h1>Análisis por carrera</h1>";

    vector<string> carreras;
    for (int i = 0; i < estudiantes.size(); i++)
    {
        string carrera = estudiantes[i].getCarrera();
        bool existe = false;
        for (int j = 0; j < carreras.size(); j++)
        {
            if (carreras[j] == carrera)
            {
                existe = true;
                break;
            }
        }
        if (!existe)
            carreras.push_back(carrera);
    }

    for (const string &carrera : carreras)
    {
        reporte << "<h2>Carrera: " << carrera << "</h2>";
        for (const Estudiante &e : estudiantes)
        {
            if (e.getCarrera() == carrera)
            {
                float sumaNotas = 0;
                int contadorNotas = 0;

                reporte << "<h2>" << e.getNombre() << " " << e.getApellido() << " (Carnet: " << e.getCarnet() << ")</h2>";
                reporte << "<p>Semestre: " << e.getSemestre() << "</p>";

                vector<string> carreras;
                for (int i = 0; i < estudiantes.size(); i++)
                {
                    string carrera = estudiantes[i].getCarrera();
                    bool existe = false;
                    for (int j = 0; j < carreras.size(); j++)
                    {
                        if (carreras[j] == carrera)
                        {
                            existe = true;
                            break;
                        }
                    }
                    if (!existe)
                        carreras.push_back(carrera);
                }
                for (int i = 0; i < carreras.size(); i++)
                {
                    string carrera = carreras[i];
                    vector<float> notasCarrera;
                    for (int j = 0; j < notas.size(); j++)
                    {
                        Nota n = notas[j];
                        for (int k = 0; k < estudiantes.size(); k++)
                        {
                            if (estudiantes[k].getCarnet() == n.getCarnet() && estudiantes[k].getCarrera() == carrera)
                            {
                                notasCarrera.push_back(n.getNota());
                            }
                        }
                    }
                    if (notasCarrera.empty())
                        continue;
                    for (int a = 0; a < notasCarrera.size(); a++)
                    {
                        for (int b = 0; b < notasCarrera.size() - 1; b++)
                        {
                            if (notasCarrera[b] > notasCarrera[b + 1])
                            {
                                float temp = notasCarrera[b];
                                notasCarrera[b] = notasCarrera[b + 1];
                                notasCarrera[b + 1] = temp;
                            }
                        }
                    }

                    float suma = 0;
                    for (float nota : notasCarrera)
                    {
                        suma += nota;
                    }
                    float promedio = suma / notasCarrera.size();
                    float mediana;
                    int tamano = notasCarrera.size();
                    if (tamano % 2 == 0)
                    {
                        mediana = (notasCarrera[tamano / 2 - 1] + notasCarrera[tamano / 2]) / 2;
                    }
                    else
                    {
                        mediana = notasCarrera[tamano / 2];
                    }
                    float sumaCuadrados = 0;
                    for (float nota : notasCarrera)
                    {
                        sumaCuadrados += (nota - promedio) * (nota - promedio);
                    }
                    float desviacionEstandar = sqrt(sumaCuadrados / notasCarrera.size());
                    float p25 = notasCarrera[(int)round(0.25 * (notasCarrera.size() - 1))];
                    float p50 = notasCarrera[(int)round(0.50 * (notasCarrera.size() - 1))];
                    float p75 = notasCarrera[(int)round(0.75 * (notasCarrera.size() - 1))];

                    int reprobados = 0;
                    for (float nota : notasCarrera)
                    {
                        if (nota < 61)
                        {
                            reprobados++;
                        }
                    }

                    reporte << "<h3>Estadísticas de la Carrera: " << carrera << "</h3>";
                    reporte << "<p>Promedio: " << promedio << "</p>";
                    reporte << "<p>Mediana: " << mediana << "</p>";
                    reporte << "<p>Desviación Estándar: " << desviacionEstandar << "</p>";
                    reporte << "<p>Percentil 25: " << p25 << "</p>";
                    reporte << "<p>Percentil 50: " << p50 << "</p>";
                    reporte << "<p>Percentil 75: " << p75 << "</p>";
                    reporte << "<p>Reprobados: " << reprobados << "</p>";
                }
            }
        }
        reporte << "</body></html>";
        reporte.close();
    }
}
int main()
{
    vector<Curso> cursos;
    vector<Estudiante> estudiantes;
    vector<Nota> notas;
    int opcion;
    do
    {
        std::cout << "Sistema de Analisis Academico" << std::endl;
        std::cout << "-------------------------------------------------------" << std::endl;
        std::cout << "1. Cargar archivo de estudiantes" << std::endl;
        std::cout << "2. Cargar archivo de cursos" << std::endl;
        std::cout << "3. Cargar archivo de notas" << std::endl;
        std::cout << "4. Generar Reporte: Estadistica por Cursos" << std::endl;
        std::cout << "5. Generar Reporte: Rendimiento por Estudiante" << std::endl;
        std::cout << "6. Generar Reporte: Top 10 Estudiantes" << std::endl;
        std::cout << "7. Generar Reporte: Cursos con Mayor Tasa de Reprobados" << std::endl;
        std::cout << "8. Generar Reporte: Analisis por Carrera" << std::endl;
        std::cout << "9. Salir" << std::endl;
        std::cout << "Seleccione una opcion: " << std::endl;

        std::cin >> opcion;

        switch (opcion)
        {
        case 1:
            procesarArchivo("estudiantes.lfp", cursos, estudiantes, notas);
            break;
        case 2:
            procesarArchivo("cursos.lfp", cursos, estudiantes, notas);
            break;
        case 3:
            procesarArchivo("notas.lfp", cursos, estudiantes, notas);
            break;
        case 4:
            reporteEstadisticas("reporte_estadisticas.html", cursos, notas);
            break;
        case 5:
            reporteRendimientoEstudiantes("reporte_rendimiento_estudiantes.html", estudiantes, notas);
            break;
        case 6:
            reporteTopEstudiantes("reporte_top_estudiantes.html", estudiantes, notas);
            break;
        case 7:
            reporteReprobados(estudiantes, notas, "reporte_reprobados.html");
            break;
        case 8:
            reporteAnalisisCarrera(estudiantes, notas, "reporte_analisis_carrera.html");
            break;
        case 9:
            std::cout << "Saliendo del programa..." << std::endl;
            break;
        default:
            std::cout << "Opcion no valida, por favor intente de nuevo." << std::endl;
            break;
        }
    } while (opcion != 9);
    return 0;
}
