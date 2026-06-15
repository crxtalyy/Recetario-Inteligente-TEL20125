#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logica.h"
#include <QMessageBox>
#include <fstream>
#include <string>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
}

MainWindow::~MainWindow(){
    delete ui;
}
string name;//para guardar nombre
void MainWindow::on_BotonEnter_clicked(){
    string user = ui->UserBox->text().toStdString(); //extraemos campo nombre
    string pass = ui->PassBox->text().toStdString(); //extraemos campo contraseña
    int camino = validar(user,pass); //encontramos el camino
    switch(camino){
    case 0: //ARCHIVO MAL
        QMessageBox::critical(this,"Error","Fallo del Sistema.\nNo se encontro el archivo");
        break;
    case 1: //USUARIO ENCONTRADO
        name = user;
        QMessageBox::information(this,"Ingreso","Usuario Encontrado.\nBienvenid@ nuevamente!!!");
        ui->welcome->setText("Bienvenido a tu recetario " + QString::fromStdString(name));
        cargarRecetas();
        ui->stackedWidget->setCurrentIndex(1);
        ui->UserBox->clear();
        ui->PassBox->clear();
        break;
    case 2: //CONTRASEÑA ERRONEA
        QMessageBox::warning(this,"Error","Contraseña Incorrecta.\nIntente nuevamente");
        ui->PassBox->clear();
        break;
    case 3: //NUEVO USUARIO
        name = user;
        ofstream archivo("recetas_usuarios/recetas_" + user + ".txt", std::ios::app);//creamos recetario del usuario
        if(archivo.is_open()){
            archivo.close();
        }
        QMessageBox::information(this,"Ingreso","Nuevo Usuario Registrado.\nBienvenid@!!!");
        ui->welcome->setText("Bienvenido a tu recetario " + QString::fromStdString(name));
        cargarRecetas();
        ui->stackedWidget->setCurrentIndex(1);
        ui->UserBox->clear();
        ui->PassBox->clear();
        break;
    }
}

void MainWindow::on_crearReceta_clicked(){
    ui->stackedWidget->setCurrentIndex(2);
}

string receta;
int personas;
int ingredientes;
void MainWindow::on_nextF2_clicked(){
    receta = ui->nameReceta->text().toStdString();
    personas = ui->cantPersonas->value();
    ingredientes = ui->cantIngredientes->value();
    crearBase(receta, personas, ingredientes, name);
    ui->nameReceta->clear();
    ui->cantPersonas->clear();
    ui->cantIngredientes->clear();
    ui->stackedWidget->setCurrentIndex(3);
    ui->textoInteractivo->setText("Tienes 0 ingredientes de " + QString::number(ingredientes));
}

int contador = 1;
void MainWindow::on_nextF3_clicked(){
    if(contador<ingredientes){
        string ingre = ui->queEs->text().toStdString();
        string cant = ui->cuantoEs->text().toStdString();
        string medida = ui->unidad->text().toStdString();
        crearIngredientes(name, ingre, cant, medida);
        ui->queEs->clear();
        ui->cuantoEs->clear();
        ui->unidad->clear();
        ui->textoInteractivo->setText("Tienes " + QString::number(contador) + " ingredientes de " + QString::number(ingredientes));
        contador += 1;
    }
    else{
        string ingre = ui->queEs->text().toStdString();
        string cant = ui->cuantoEs->text().toStdString();
        string medida = ui->unidad->text().toStdString();
        crearIngredientes(name, ingre, cant, medida);
        ui->queEs->clear();
        ui->cuantoEs->clear();
        ui->unidad->clear();
        contador = 1;
        ui->stackedWidget->setCurrentIndex(4);
    }
}

void MainWindow::on_home_clicked(){
    string instrucciones = ui->sts->toPlainText().toStdString();
    crearPreparacion(name, instrucciones);
    cargarRecetas();
    ui->stackedWidget->setCurrentIndex(1);
    ui->sts->clear();
}

void MainWindow::on_adios_clicked(){
    auto respuesta = QMessageBox::question(this, "Salir", "¿Estás seguro de abandonar tu Recetario?", QMessageBox::Yes | QMessageBox::No);
    if(respuesta == QMessageBox::Yes){
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::cargarRecetas(){
    ui->listaRecetas->clear();
    deque<recetas> lista;
    lista = leerRecetas(name);
    deque<recetas>::iterator i;
    for(i = lista.begin(); i != lista.end(); i++){
        ui->listaRecetas->addItem(QString::fromStdString(i->getNombre()));
    }
}


