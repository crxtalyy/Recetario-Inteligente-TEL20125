#include "Ingredientes.h"
#include<string>

Ingredientes::Ingredientes(std::string ingre,std::string medida,float precio,float cantI):
    ingrediente(ingre), uMedida(medida), precioIgrediente(precio),cantidadIngrediente(cantI){}



std::string Ingredientes::getIngrediente(){
    return ingrediente;
}
std::string Ingredientes::getMedida(){
    return uMedida;
}
float Ingredientes::getPrecio(){
    return precioIgrediente;
}
float Ingredientes::getCantidadIngrediente(){
    return cantidadIngrediente;
}

//Calcula y retorna la escala deseada para el precio
float Ingredientes::precioEscalada(float escala){
    return escala*precioIgrediente;
}
//Calcula y retorna la escala deseada para la cantidad de un ingrediente
float Ingredientes::medidaEscalada(float escala){
    return escala*cantidadIngrediente;
}
