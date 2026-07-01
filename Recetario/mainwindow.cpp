#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include "logica.h"
#include <QMessageBox>
#include <fstream>
#include <string>
#include "recetas.h"
#include <QtCharts/QChartView>
#include <QtCharts/QPieSeries>
#include <QtCharts/QPieSlice>
using namespace std;

MainWindow::MainWindow(QWidget *parent): QMainWindow(parent), ui(new Ui::MainWindow){
    ui->setupUi(this);
    ui->BotonEnter->setEnabled(false);
    ui->nextF2->setEnabled(false);
    ui->nextF3->setEnabled(false);
    ui->home->setEnabled(false);
    ui->newaccount->setEnabled(false);
    QString estiloCuadricula =
        "QListWidget {"
        "   background-color: #1a1a1a;"
        "   border: none;"
        "}"
        "QListWidget::item {"
        "   background-color: #2b2b2b;"
        "   border: 2px solid #444444;"
        "   border-radius: 8px;"
        "   width: 140px;"
        "   height: 90px;"
        "}"
        "QListWidget::item:hover {"
        "   background-color: #353535;"
        "   border-color: #0078d4;"
        "}"
        "QListWidget::item:selected {"
        "   background-color: #005a9e;"
        "   border-color: #0078d4;"
        "   color: white;"
        "}";
    ui->listaRecetas->setStyleSheet(estiloCuadricula);
}

MainWindow::~MainWindow(){
    delete ui;
}


//CODIGOS PARA ACTIVAR BOTONES
void MainWindow::activarLogin(){
    bool us = !(ui->UserBox->text().isEmpty());
    bool pass = !(ui->PassBox->text().isEmpty());
    ui->BotonEnter->setEnabled(us && pass);
}
void MainWindow::on_UserBox_textChanged(const QString &arg1){
    activarLogin();
}
void MainWindow::on_PassBox_textChanged(const QString &arg1){
    activarLogin();
}

void MainWindow::activarF1(){
    bool nom = !(ui->nameReceta->text().isEmpty());
    bool per = (ui->cantPersonas->value() > 0.0);
    bool ing = (ui->cantIngredientes->value() > 0.0);
    ui->nextF2->setEnabled(nom && per && ing);
}
void MainWindow::on_nameReceta_textChanged(const QString &arg1){
    activarF1();
}
void MainWindow::on_cantPersonas_valueChanged(int arg1){
    activarF1();
}
void MainWindow::on_cantIngredientes_valueChanged(int arg1){
    activarF1();
}

void MainWindow::activarF2(){
    bool nom = !(ui->queEs->text().isEmpty());
    bool what = (ui->cuantoEs->value() > 0.0);
    bool uni = (ui->unidad->currentIndex() != 0);
    bool nutri = (ui->nutriente->currentIndex() != 0);
    ui->nextF3->setEnabled(nom && what && uni && nutri);
}
void MainWindow::on_queEs_textChanged(const QString &arg1){
    activarF2();
}
void MainWindow::on_cuantoEs_valueChanged(double arg1){
    activarF2();
}
void MainWindow::on_unidad_currentIndexChanged(int index){
    activarF2();
}
void MainWindow::on_nutriente_currentIndexChanged(int index){
    activarF2();
}

void MainWindow::activarF3(){
    bool tex = !(ui->sts->toPlainText().trimmed().isEmpty());
    ui->home->setEnabled(tex);
}
void MainWindow::on_sts_textChanged(){
    activarF3();
}

void MainWindow::activarSignin(){
    bool us = !(ui->usuarioBox->text().isEmpty());
    bool pass = !(ui->contraBox->text().isEmpty());
    ui->newaccount->setEnabled(us && pass);
}
void MainWindow::on_usuarioBox_textChanged(const QString &arg1){
    activarSignin();
}
void MainWindow::on_contraBox_textChanged(const QString &arg1){
    activarSignin();
}
//FIN DE ACTIVACION DE BOTONES


//CAMBIOS EN LA INTERFAZ
string name;//para guardar nombre
void MainWindow::on_BotonEnter_clicked(){ //valida cuenta existente
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
        QMessageBox::warning(this,"Error","El usuario no existe.\nIntente nuevamente");
        ui->UserBox->clear();
        ui->PassBox->clear();
        break;
    }
}
void MainWindow::on_newaccount_clicked(){ //valida nueva cuenta
    string user = ui->usuarioBox->text().toStdString(); //extraemos campo nombre
    string pass = ui->contraBox->text().toStdString(); //extraemos campo contraseña
    int camino = validar(user,pass); //encontramos el camino
    switch(camino){
    case 0: //ARCHIVO MAL
        QMessageBox::critical(this,"Error","Fallo del Sistema.\nNo se encontro el archivo");
        break;
    case 1: //USUARIO ENCONTRADO
        QMessageBox::warning(this,"Error","El usuario ya existe.\nIntente nuevamente");
        ui->usuarioBox->clear();
        ui->contraBox->clear();
        break;
    case 2: //CONTRASEÑA ERRONEA
        QMessageBox::warning(this,"Error","Contraseña Incorrecta.\nIntente nuevamente");
        ui->contraBox->clear();
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
        ui->usuarioBox->clear();
        ui->contraBox->clear();
        break;
    }
}

void MainWindow::on_crearReceta_clicked(){ //comienza creacion de receta
    ui->stackedWidget->setCurrentIndex(2);
}

string receta;
int personas;
int ingredientes;
void MainWindow::on_nextF2_clicked(){ //comienza a escribir en archivo de texto
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
void MainWindow::on_nextF3_clicked(){ //escribe en archivo de texto
    if(contador<ingredientes){
        string ingre = ui->queEs->text().toStdString();
        string cant = QString::number(ui->cuantoEs->value()).toStdString();
        string medida = ui->unidad->currentText().toStdString();
        string nutri = ui->nutriente->currentText().toStdString();
        crearIngredientes(name, ingre, cant, medida, nutri);
        ui->queEs->clear();
        ui->cuantoEs->setValue(0.0);
        ui->unidad->setCurrentIndex(0);
        ui->nutriente->setCurrentIndex(0);
        ui->info->setCurrentIndex(0);
        ui->textoInteractivo->setText("Tienes " + QString::number(contador) + " ingredientes de " + QString::number(ingredientes));
        contador += 1;
    }
    else{
        string ingre = ui->queEs->text().toStdString();
        string cant = QString::number(ui->cuantoEs->value()).toStdString();
        string medida = ui->unidad->currentText().toStdString();
        string nutri = ui->nutriente->currentText().toStdString();
        crearIngredientes(name, ingre, cant, medida, nutri);
        ui->queEs->clear();
        ui->cuantoEs->setValue(0.0);
        ui->unidad->setCurrentIndex(0);
        ui->nutriente->setCurrentIndex(0);
        ui->info->setCurrentIndex(0);
        contador = 1;
        ui->stackedWidget->setCurrentIndex(4);
    }
}

void MainWindow::on_home_clicked(){ //termina de editar archivo de texto
    string instrucciones = ui->sts->toPlainText().toStdString();
    crearPreparacion(name, instrucciones);
    ui->stackedWidget->setCurrentIndex(1);
    cargarRecetas();
    ui->sts->clear();
}

void MainWindow::on_adios_clicked(){ //cierra sesion
    auto respuesta = QMessageBox::question(this, "Salir", "¿Estás seguro de abandonar tu Recetario?", QMessageBox::Yes | QMessageBox::No);
    if(respuesta == QMessageBox::Yes){
        name = "";
        ui->stackedWidget->setCurrentIndex(0);
    }
}

void MainWindow::cargarRecetas(){ //dispone todas las recetas creadas
    ui->listaRecetas->clear();
    listaRecetas = leerRecetas(name);
    deque<recetas>::iterator i;
    for(i = listaRecetas.begin(); i != listaRecetas.end(); i++){
        ui->listaRecetas->addItem(QString::fromStdString(i->getNombre()));
    }
}

void MainWindow::on_listaRecetas_currentRowChanged(int currentRow){ //genera la vista de una receta
    if (currentRow < 0 || currentRow >= listaRecetas.size()){
        return;
    }
    actual = listaRecetas[currentRow];
    ui->stackedWidget->setCurrentIndex(5);
    ui->title->setText(QString::fromStdString(actual.getNombre()));
    string parrafo = "";
    vector<string> linea = actual.getLista();
    for(int i = 0; i < linea.size(); i++){
        parrafo += to_string(i+1);
        parrafo += ". ";
        parrafo += linea[i];
        parrafo += "\n";
    }
    ui->ingre->setText(QString::fromStdString(parrafo));
    parrafo = "";
    vector<string> line = actual.getPasos();
    for(int i = 0; i < line.size(); i++){
        parrafo += line[i];
        parrafo += "\n";
    }
    ui->steps->setText(QString::fromStdString(parrafo));
    ui->cantidad->setValue(actual.getPersonas());
}

void MainWindow::on_backMenu_clicked(){ //vuelve al menu
    ui->stackedWidget->setCurrentIndex(1);
    cargarRecetas();
}

void MainWindow::on_escalar_clicked(){ //escala las recetas
    int nueva = ui->cantidad->value();
    int cuantos = actual.getPersonas();
    float factor = nueva/(float)cuantos;
    ui->title->setText(QString::fromStdString(actual.getNombre()));
    string parrafo = "";
    vector<string> linea = actual.getLista();
    for(int i = 0; i < linea.size(); i++){
        parrafo += to_string(i+1);
        parrafo += ". ";
        string instruccion = linea[i];
        int espacio = instruccion.find(" ");
        float corte = stof(instruccion.substr(0, espacio));
        string resto = instruccion.substr(espacio);
        parrafo += QString::number(corte*factor).toStdString() + resto;
        parrafo += "\n";
    }
    ui->ingre->setText(QString::fromStdString(parrafo));
    parrafo = "";
    vector<string> line = actual.getPasos();
    for(int i = 0; i < line.size(); i++){
        parrafo += line[i];
        parrafo += "\n";
    }
    ui->steps->setText(QString::fromStdString(parrafo));
    ui->cantidad->setValue(nueva);
}

void MainWindow::on_menu_clicked(){ //salir de crear receta
    auto respuesta = QMessageBox::question(this, "Volver", "¿Estás seguro de volver al menú de tu Recetario?", QMessageBox::Yes | QMessageBox::No);
    if(respuesta == QMessageBox::Yes){
        ui->stackedWidget->setCurrentIndex(1);
    }
}

void MainWindow::on_ingreso_clicked(){ //para cambiar de registro a ingreso
    ui->stackedWidget->setCurrentIndex(0);
    ui->usuarioBox->clear();
    ui->contraBox->clear();
}

void MainWindow::on_nueva_clicked(){ //para cambiar de ingreso a registro
    ui->stackedWidget->setCurrentIndex(6);
    ui->UserBox->clear();
    ui->PassBox->clear();
}

void MainWindow::on_genGrafico_clicked(){ //crea el grafico
    QChart *chart = doPieChart();
    ui->grafico->setChart(chart);
    ui->grafico->setRenderHint(QPainter::Antialiasing);
    ui->stackedWidget->setCurrentIndex(7);
}

void MainWindow::on_borrar_clicked(){ //elimina el grafico
    ui->stackedWidget->setCurrentIndex(5);
}
// INTERFAZ


//GRAFICO
QChart *MainWindow::doPieChart() {
    QString name = QString::fromStdString(actual.getNombre());
    vector<string> ingre = actual.getLista();
    float proteina = 0;
    float grasa = 0;
    float carbohidrato = 0;
    float vitamina = 0;
    float agua = 0;
    float mineral = 0;
    string parrafo = "";
    vector<string> linea = actual.getLista();
    for(int i = 0; i < linea.size(); i++){
        string instruccion = linea[i];
        int inicio = instruccion.find("(");
        int fin = instruccion.find(")");
        if (inicio != string::npos && fin != string::npos){
            string nutriente = instruccion.substr(inicio + 1, fin - inicio - 1);
            if(nutriente == "Proteínas"){
                proteina += 1;
            }
            else if(nutriente == "Grasas"){
                grasa += 1;
            }
            else if(nutriente == "Carbohidratos"){
                carbohidrato += 1;
            }
            else if(nutriente == "Vitaminas"){
                vitamina += 1;
            }
            else if(nutriente == "Aguas"){
                agua += 1;
            }
            else if(nutriente == "Minerales"){
                mineral += 1;
            }
        }
    }
    QPieSeries *series = new QPieSeries();
    if(proteina > 0){
        series->append("Proteínas", proteina);
    }
    if(grasa > 0){
        series->append("Grasas", grasa);
    }
    if(carbohidrato > 0){
        series->append("Carbohidratos", carbohidrato);
    }
    if(vitamina > 0){
        series->append("Vitaminas", vitamina);
    }
    if(agua > 0){
        series->append("Aguas", agua);
    }
    if(mineral > 0){
        series->append("Minerales", mineral);
    }
    series->setPieSize(0.75);
    vector<float> lista = {proteina, grasa, carbohidrato, vitamina, agua};
    float mayor = proteina;
    for(int i =1; i<lista.size();i++){
        if(lista[i]>mayor){
            mayor = lista[i];
        }
    }
    if(mayor > 0){
        for(int i = 0; i < series->slices().size(); i++){
            QPieSlice *slice = series->slices().at(i);
            slice->setLabelVisible();
            if(slice->label() == "Proteínas"){
                slice->setPen(QPen(Qt::darkRed, 2));
                slice->setBrush(Qt::red);
            }
            else if(slice->label() == "Grasas"){
                slice->setPen(QPen(Qt::darkYellow, 2));
                slice->setBrush(Qt::yellow);
            }
            else if(slice->label() == "Carbohidratos"){
                slice->setPen(QPen(Qt::darkMagenta, 2));
                slice->setBrush(Qt::magenta);
            }
            else if(slice->label() == "Vitaminas"){
                slice->setPen(QPen(Qt::darkGreen, 2));
                slice->setBrush(Qt::green);
            }
            else if(slice->label() == "Aguas"){
                slice->setPen(QPen(Qt::darkCyan, 2));
                slice->setBrush(Qt::cyan);
            }
            else if(slice->label() == "Minerales"){
                slice->setPen(QPen(Qt::darkGray, 2));
                slice->setBrush(Qt::lightGray);
            }
            if(slice->value() == mayor){
                slice->setExploded();
            }
        }
    }
    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setAnimationOptions(QChart::SeriesAnimations);
    chart->setTitle(name);
    QFont enunciado;
    enunciado.setFamily("Times New Roman");
    enunciado.setPointSize(26);
    enunciado.setBold(true);
    chart->setTitleFont(enunciado);
    chart->legend()->show();
    chart->legend()->setAlignment(Qt::AlignBottom);
    QFont detalles;
    detalles.setFamily("Times New Roman");
    detalles.setPointSize(10);
    chart->legend()->setFont(detalles);
    return chart;
}
//GRAFICO
