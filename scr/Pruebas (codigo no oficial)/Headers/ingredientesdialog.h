#ifndef INGREDIENTESDIALOG_H
#define INGREDIENTESDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class IngredientesDialog;
}

class IngredientesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit IngredientesDialog(QWidget *parent = nullptr);
    ~IngredientesDialog();

    void setUsuario(QString nombre) { usuarioActual = nombre; }
    QString usuarioActual;

private slots:
    void on_btnAgregar_clicked();
    void on_btnSiguiente_clicked();

private:
    Ui::IngredientesDialog *ui;
};

#endif // INGREDIENTESDIALOG_H
