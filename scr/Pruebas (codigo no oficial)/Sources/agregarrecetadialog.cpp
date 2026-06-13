#include "agregarrecetadialog.h"
#include "ui_agregarrecetadialog.h"
#include "ingredientesdialog.h"
#include <QInputDialog>

AgregarRecetaDialog::AgregarRecetaDialog(QWidget *parent)
    : QDialog(parent), ui(new Ui::AgregarRecetaDialog)
{
    ui->setupUi(this);
}

AgregarRecetaDialog::~AgregarRecetaDialog()
{
    delete ui;
}

void AgregarRecetaDialog::on_btnSiguiente_clicked()
{
    bool ok;
    QString nombre = QInputDialog::getText(this, "Nueva Receta", "Nombre de la receta:", QLineEdit::Normal, "", &ok);

    if(ok && !nombre.isEmpty()) {
        IngredientesDialog v2;
        v2.setUsuario(this->usuarioActual);

        v2.setProperty("nombreReceta", nombre);

        v2.exec();
        this->close();
    }
}
