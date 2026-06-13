#ifndef AGREGARRECETADIALOG_H
#define AGREGARRECETADIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class AgregarRecetaDialog;
}

class AgregarRecetaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit AgregarRecetaDialog(QWidget *parent = nullptr);
    ~AgregarRecetaDialog();

    void setUsuario(QString nombre) { usuarioActual = nombre; }
    QString usuarioActual;

private slots:
    void on_btnSiguiente_clicked();

private:
    Ui::AgregarRecetaDialog *ui;
    QString nombreReceta;
};

#endif // AGREGARRECETADIALOG_H
