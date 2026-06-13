#ifndef LOGICA_H
#define LOGICA_H
#include <string>
#include <vector>
#include <deque>
using namespace std;

struct recetas{
    string nombre;
    int personas;
    int cuanto;
    vector<string> lista;
    vector<string> pasos;
};

int validar(string user, string pass);
void crearBase(string nombre, int p, int i, string usuario);
void crearIngredientes(string usuario, string ingrediente, string cantidad, string unidad);
void crearPreparacion(string usuario, string preparacion);
deque<recetas> leerRecetas(string usuario);

#endif