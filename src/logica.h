#ifndef LOGICA_H
#define LOGICA_H
#include <string>
#include <vector>
#include <deque>
#include "recetas.h"
using namespace std;

int validar(string user, string pass);
void crearBase(string nombre, int p, int i, string usuario);
void crearIngredientes(string usuario, string ingrediente, string cantidad, string unidad, string nutri);
void crearPreparacion(string usuario, string preparacion);
deque<recetas> leerRecetas(string usuario);

#endif