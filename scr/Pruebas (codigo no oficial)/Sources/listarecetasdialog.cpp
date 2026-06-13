#include "listarecetasdialog.h"
#include "ui_listarecetasdialog.h"
#include "detallerecetadialog.h"
#include <QDir>
#include <QListWidgetItem>

ListaRecetasDialog::ListaRecetasDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::ListaRecetasDialog)
{
    ui->setupUi(this);

    connect(ui->listWidgetRecetas, &QListWidget::itemDoubleClicked, this, [=](QListWidgetItem *item){
        QString nombreArchivo = item->text();

        DetalleRecetaDialog vDetalle;
        vDetalle.setUsuario(this->usuarioActual);
        vDetalle.cargarReceta(nombreArchivo);
        vDetalle.exec();
    });
}

ListaRecetasDialog::~ListaRecetasDialog()
{
    delete ui;
}

void ListaRecetasDialog::setUsuario(QString nombre)
{
    usuarioActual = nombre;

    QString ruta = "usuarios/" + usuarioActual;
    QDir dir(ruta);

    QStringList archivos = dir.entryList(QStringList() << "*.txt", QDir::Files);

    ui->listWidgetRecetas->addItems(archivos);
}

void ListaRecetasDialog::on_btnVolver_clicked()
{
    this->close();
}
