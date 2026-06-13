#include "receta.h"
#include "Ingredientes.h"
#include <QString>

receta::receta(std::vector<Ingredientes> listaIngre, std::string nomReceta, int cantBase) :
    listaIngredientes(listaIngre), nombreReceta(nomReceta), cantidadBase(cantBase) {}

float receta::calculoEscala(float escala) {
    return escala / float(cantidadBase);
}

QString receta::recorrerElementos(float escala) {
    float factor = calculoEscala(escala);

    QString resultado = "Receta escalada para " + QString::number(escala) + " personas:\n\n";

    for(size_t i = 0; i < listaIngredientes.size(); i++) {
        QString nombre = QString::fromStdString(listaIngredientes[i].getIngrediente());
        QString unidad = QString::fromStdString(listaIngredientes[i].getMedida());

        float precioEscalado = listaIngredientes[i].precioEscalada(factor);
        float cantidadEscalada = listaIngredientes[i].medidaEscalada(factor);

        resultado += nombre + ": " + QString::number(cantidadEscalada) + " " + unidad +
                     " | Costo: $" + QString::number(precioEscalado) + "\n";
    }
    return resultado;
}
