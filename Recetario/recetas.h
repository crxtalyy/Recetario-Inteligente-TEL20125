#ifndef RECETAS_H
#define RECETAS_H
#include <string>
#include <vector>
using namespace std;

class recetas{
public:
    recetas();
    string getNombre() const;
    void setNombre(string nuevoN);
    int getPersonas() const;
    void setPersonas(int nuevoPe);
    int getCuanto() const;
    void setCuanto(int nuevoC);
    vector<string> getLista() const;
    void setLista(vector<string> nuevoL);
    vector<string> getPasos() const;
    void setPasos(vector<string> nuevoPa);
private:
    string nombre;
    int personas;
    int cuanto;
    vector<string> lista;
    vector<string> pasos;
};

#endif // RECETAS_H
