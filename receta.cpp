#include "receta.h"
#include"Ingredientes.h"
#include<iostream>
receta::receta(std::vector<Ingredientes>listaIngre, std::string nomReceta,int cantBase):
    listaIngredientes(listaIngre),nombreReceta(nomReceta), cantidadBase(cantBase) {}
// Vector: [nombre ingrediente(0),unidad de medida(1), precio(2), cantidad del Ingrediente(3), cantidad de Personas(4)]
float receta::calculoEscala(float escala){

    return escala/float(cantidadBase);
}

void receta::recorrerElementos(float escala){

    float factor= calculoEscala(escala);

    for(int i=0;i<listaIngredientes.size();i++){
        std::string nombreIngrediente=listaIngredientes[i].getIngrediente();
        std::string unidadMedida=listaIngredientes[i].getMedida();

        float precioEscalado=listaIngredientes[i].precioEscalada(factor);
        float cantidadEscalada=listaIngredientes[i].medidaEscalada(factor);

        std::cout<<nombreIngrediente<<" "<<unidadMedida<<" $"<<precioEscalado<<" "<<cantidadEscalada<<std::endl;
    }
}