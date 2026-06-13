#include "instruccionesdialog.h"
#include "ui_instruccionesdialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>

InstruccionesDialog::InstruccionesDialog(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::InstruccionesDialog)
{
    ui->setupUi(this);
}

InstruccionesDialog::~InstruccionesDialog()
{
    delete ui;
}

void InstruccionesDialog::on_btnAgregarPaso_clicked()
{
    QString paso = ui->txtPaso->toPlainText();
    if (paso.trimmed().isEmpty()) return;

    int numeroPaso = ui->listaPasos->count() + 1;
    ui->listaPasos->addItem(QString::number(numeroPaso) + ". " + paso);
    ui->txtPaso->clear();
    ui->txtPaso->setFocus();
}

void InstruccionesDialog::on_btnFinalizar_clicked()
{
    QString nombreReceta = this->property("nombreReceta").toString();
    QStringList ingredientes = this->property("listaIngredientes").toStringList();

    if(nombreReceta.isEmpty()) nombreReceta = "Receta_Sin_Nombre";

    QString carpeta = "usuarios/" + this->usuarioActual;
    QDir().mkpath(carpeta);

    QFile archivo(carpeta + "/" + nombreReceta + ".txt");

    if (archivo.open(QIODevice::WriteOnly | QIODevice::Text)) {
        QTextStream out(&archivo);

        out << "Receta: " << nombreReceta << "\n\n";

        out << "--- INGREDIENTES ---\n";
        for(const QString &ing : ingredientes) {
            out << ing << "\n";
        }

        out << "\n--- PASOS DE PREPARACION ---\n";
        for(int i = 0; i < ui->listaPasos->count(); ++i) {
            out << ui->listaPasos->item(i)->text() << "\n";
        }

        archivo.close();
        QMessageBox::information(this, "Éxito", "¡Receta guardada con éxito!");
    } else {
        QMessageBox::warning(this, "Error", "No se pudo guardar la receta.");
    }

    this->accept();
}
