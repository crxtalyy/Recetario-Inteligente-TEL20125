#include <string>
#include <vector>
#include "recetas.h"

recetas::recetas(): nombre(""), personas(0), cuanto(0){ }//programacion de constructor

string recetas::getNombre() const{//programacion de los metodos
    return nombre;
}

void recetas::setNombre(string nuevoN){
    nombre = nuevoN;
}

int recetas::getPersonas() const{
    return personas;
}

void recetas::setPersonas(int nuevoPe){
    personas = nuevoPe;
}

int recetas::getCuanto() const{
    return cuanto;
}

void recetas::setCuanto(int nuevoC){
    cuanto = nuevoC;
}

vector<string> recetas::getLista() const{
    return lista;
}

void recetas::setLista(vector<string> nuevoL){
    lista = nuevoL;
}

vector<string> recetas::getPasos() const{
    return pasos;
}

void recetas::setPasos(vector<string> nuevoPa){
    pasos = nuevoPa;
}
