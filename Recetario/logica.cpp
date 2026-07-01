#include <iostream>
#include <string>
#include <fstream>
#include <vector>
#include <deque>
#include "logica.h"
#include "recetas.h"
using namespace std;

int validar(string user, string pass){
    ifstream leer("usuarios.txt");//para leer el archivo
    string p, q;
    const char key = 4;
    bool existe = false;//asumimos que usuario no existe
    if(leer.is_open()){
        while(leer >> p >> q){ //extraigo archivo por espacio y \n
            if(p == user){//vemos si existe el usuario
                existe = true;//corroboramos que existe
                string descifrado = "";
                for(int i = 0; i<q.size(); i++){
                    descifrado += (q[i]^key);
                }
                if(descifrado == pass){//vemos si coincide la contraseña
                    leer.close();
                    return 1; //1: USUARIO ENCONTRADO
                }
                else{
                    leer.close();
                    return 2;//2: CONTRASEÑA INCORRECTA
                }
            }
        }
        leer.close();
    }
    if(!existe){
    //llave pues si encontramos usuario se salta el if y si nunca encontramos usuario entra al if
        ofstream escribir("usuarios.txt", std::ios::app);
        string cifrado = "";
        for(int i = 0; i<pass.size(); i++){
            cifrado += (pass[i]^key);
        }
        if(escribir.is_open()){
            escribir << user << " " << cifrado << endl;//agregamos al archivo los nuevos usuarios
            escribir.close();
            return 3;//NUEVO USUARIO
        }
        else{
            return 0;
        }
    }
    return 0;//ERROR DE ARCHIVO
}

void crearBase(string nombre, int p, int i, string usuario){
    ofstream archivo("recetas_usuarios/recetas_" + usuario + ".txt", std::ios::app);
    if(archivo.is_open()){
        archivo << "//" << endl;//usamos doble slash para iniciar una receta
        archivo << nombre << endl; //escribimos nombre de receta
        archivo << p << endl;//cantidad de personas
        archivo << i << endl;//cantidad de ingredientes
        archivo << "Ingredientes: " << endl;
        archivo.close();
    }
}

void crearIngredientes(string usuario, string ingrediente, string cantidad, string unidad, string nutri){
    ofstream archivo("recetas_usuarios/recetas_" + usuario + ".txt", std::ios::app);
    if(archivo.is_open()){
        archivo << cantidad + " " + unidad + " de " + ingrediente + " (" + nutri+ ")" << endl;//lista
        archivo.close();
    }
}

void crearPreparacion(string usuario, string preparacion){
    ofstream archivo("recetas_usuarios/recetas_" + usuario + ".txt", std::ios::app);
    if(archivo.is_open()){
        archivo << "Preparación: " << endl;
        archivo << preparacion << endl;//lista
        archivo << "FIN" << endl;
        archivo.close();
    }
}

deque<recetas> leerRecetas(string usuario){
    ifstream archivo("recetas_usuarios/recetas_" + usuario + ".txt");
    string line;//lectora de lineas
    string ignorar;//descarta lineas
    int per = 0;//temporal
    int cant = 0;//temporal
    deque<recetas> all;//el retorno
    if(archivo.is_open()){
        while(getline(archivo, line)){//while que lee el archivo
            if(line == "//"){//buscamos comienzo de una receta
                recetas nueva;//creamos una variable de nuestro struct
                vector<string> ing;//temporal
                vector<string> pre;//temporal
                getline(archivo, line);//guardamos nombre
                nueva.setNombre(line);
                archivo >> per >> cant;//guardamos los numeros en temporal
                nueva.setPersonas(per);
                nueva.setCuanto(cant);
                archivo.ignore();//borramos el salto de linea
                getline(archivo, ignorar);//descartamos linea "Ingredientes:"
                for(int i = 0; i<nueva.getCuanto(); i++){//recorremos la lista de ingredientes
                    getline(archivo,line);
                    ing.push_back(line);//agregamos a la temporal
                }
                nueva.setLista(ing);//guardamos la lista
                getline(archivo, ignorar);//descartamos linea "Preparacion: "
                while(getline(archivo,line)){//recorremos preparacion
                    if(line == "FIN"){//si encontramos el fin terminamos el bucle
                        break;
                    }
                    pre.push_back(line);//añadimos en la temporal
                }
                nueva.setPasos(pre);//guardamos paso a paso
                all.push_back(nueva);//agregamos recetas al vector
            }
        }
        archivo.close();//cerramos archivo
    }
    return all;//retornamos todas las recetas
}
