#ifndef RECETA_H
#define RECETA_H

#include "Ingredientes.h"
#include <vector>
#include <QString>

class receta {
public:
    receta(std::vector<Ingredientes> listaIngres, std::string nombreReceta, int cantidadBase);

    QString recorrerElementos(float escala);

    float calculoEscala(float escala);

protected:
    std::string nombreReceta;
    std::vector<Ingredientes> listaIngredientes;
    int cantidadBase;
};

#endif // RECETA_H
