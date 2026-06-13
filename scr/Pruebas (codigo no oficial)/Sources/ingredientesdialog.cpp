#include "ingredientesdialog.h"
#include "ui_ingredientesdialog.h"
#include "instruccionesdialog.h"

IngredientesDialog::IngredientesDialog(QWidget *parent) : QDialog(parent), ui(new Ui::IngredientesDialog) { ui->setupUi(this); }
IngredientesDialog::~IngredientesDialog() { delete ui; }

void IngredientesDialog::on_btnAgregar_clicked()
{
    QString linea = ui->lineEdit->text() + " | " + QString::number(ui->doubleSpinBox->value()) + " " + ui->comboBox->currentText();
    ui->listWidget->addItem(linea);
    ui->lineEdit->clear();
    ui->lineEdit->setFocus();
}

void IngredientesDialog::on_btnSiguiente_clicked()
{
    QStringList listaIngredientes;
    for(int i = 0; i < ui->listWidget->count(); ++i) {
        listaIngredientes << ui->listWidget->item(i)->text();
    }

    InstruccionesDialog v3;
    v3.setUsuario(this->usuarioActual);

    v3.setProperty("nombreReceta", this->property("nombreReceta"));
    v3.setProperty("listaIngredientes", listaIngredientes);

    v3.exec();
    this->close();
}
