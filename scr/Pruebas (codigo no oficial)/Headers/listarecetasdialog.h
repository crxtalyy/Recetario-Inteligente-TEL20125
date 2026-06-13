#ifndef LISTARECETASDIALOG_H
#define LISTARECETASDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class ListaRecetasDialog;
}

class ListaRecetasDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ListaRecetasDialog(QWidget *parent = nullptr);
    ~ListaRecetasDialog();

    void setUsuario(QString nombre);
    QString usuarioActual;

private slots:
    void on_btnVolver_clicked();

private:
    Ui::ListaRecetasDialog *ui;
};
#endif
