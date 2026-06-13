#ifndef INGREDIENTES_H
#define INGREDIENTES_H
#include<string>

class Ingredientes{
public:
    Ingredientes(std::string ingre,std::string medida,float precio,float cantI);
//Getters
    std::string getIngrediente();
    std::string getMedida();
    float getPrecio();
    float getCantidadIngrediente();
//Metodos de escala
    float cantidadEscalda(float cantidadEscala);
    float precioEscalada(float cantidadEscala);
    float medidaEscalada(float cantidadEscala);
protected:
    std::string ingrediente;
    std::string uMedida;
    float cantidadIngrediente;
    float precioIgrediente;
};

#endif // INGREDIENTES_H