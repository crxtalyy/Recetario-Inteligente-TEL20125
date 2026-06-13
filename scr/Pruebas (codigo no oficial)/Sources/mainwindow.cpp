#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "agregarrecetadialog.h"
#include <QMessageBox>
#include "listarecetasdialog.h"

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), ui(new Ui::MainWindow) { ui->setupUi(this); }
MainWindow::~MainWindow() { delete ui; }

void MainWindow::setUsuario(QString nombre) { usuarioActual = nombre; }

void MainWindow::on_btnAgregarReceta_clicked()
{
    AgregarRecetaDialog dialogo;
    dialogo.setUsuario(usuarioActual);
    dialogo.exec();
}

void MainWindow::on_btnVerRecetas_clicked()
{
    ListaRecetasDialog vLista;

    vLista.setUsuario(this->usuarioActual);

    vLista.exec();
}
void MainWindow::on_btnPresupuesto_clicked() { QMessageBox::information(this, "Funcionalidad", "Aquí gestionarás tus precios y presupuesto."); }
void MainWindow::on_btnCerrarSesion_clicked() { if (QMessageBox::question(this, "Cerrar sesión", "¿Estás segura?") == QMessageBox::Yes) close(); }
