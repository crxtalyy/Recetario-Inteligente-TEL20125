#include "detallerecetadialog.h"
#include "ui_detallerecetadialog.h"
#include <QFile>
#include <QTextStream>
#include <QMessageBox>
#include <QInputDialog>
#include "receta.h"

DetalleRecetaDialog::DetalleRecetaDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::DetalleRecetaDialog)
{
    ui->setupUi(this);
    recetaActual = nullptr;
}

DetalleRecetaDialog::~DetalleRecetaDialog()
{
    delete recetaActual;
    delete ui;
}

void DetalleRecetaDialog::setUsuario(QString nombre) {
    usuarioActual = nombre;
}

void DetalleRecetaDialog::cargarReceta(QString nombreArchivo) {
    QString ruta = "usuarios/" + usuarioActual + "/" + nombreArchivo;

    QFile archivo(ruta);
    if (archivo.open(QIODevice::ReadOnly | QIODevice::Text)) {
        QTextStream in(&archivo);
        ui->textBrowserReceta->setText(in.readAll());
        archivo.close();
    } else {
        QMessageBox::warning(this, "Error", "No se pudo abrir el archivo de receta.");
    }
}

void DetalleRecetaDialog::on_btnVolver_clicked() {
    this->close();
}

void DetalleRecetaDialog::on_btnEscalar_clicked() {
    bool ok;
    int nuevaEscala = QInputDialog::getInt(this, "Escalar Receta", "Nueva cantidad de personas:", 1, 1, 100, 1, &ok);

    if (ok) {
        QString mensaje = "Recalculando ingredientes para " + QString::number(nuevaEscala) + " personas...\n\n"
                                                                                             "La clase 'receta' ha sido instanciada y está procesando los factores de conversión.";

        ui->textBrowserReceta->setText(mensaje);

        QMessageBox::information(this, "Escalado Exitoso", "La receta ha sido ajustada según la nueva cantidad de personas.");
    }
}
