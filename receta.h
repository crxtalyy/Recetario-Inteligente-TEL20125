#ifndef RECETA_H
#define RECETA_H
#include"Ingredientes.h"
#include<vector>
class receta{

public:
    receta(std::vector<Ingredientes>listaIngres,std::string nombreReceta,int cantidadBase);
    void recorrerElementos(float escala);
    float calculoEscala(float escala);



protected:
std::string nombreReceta;
std::vector<Ingredientes>listaIngredientes;
int cantidadBase;
};
#endif // RECETA_H
