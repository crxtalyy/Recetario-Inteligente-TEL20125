#ifndef DETALLERECETADIALOG_H
#define DETALLERECETADIALOG_H

#include <QDialog>
#include <QString>

class receta;

namespace Ui {
class DetalleRecetaDialog;


class DetalleRecetaDialog : public QDialog
{
    Q_OBJECT

public:
    explicit DetalleRecetaDialog(QWidget *parent = nullptr);
    ~DetalleRecetaDialog();

    void setUsuario(QString nombre);
    void cargarReceta(QString nombreArchivo);

private slots:
    void on_btnVolver_clicked();
    void on_btnEscalar_clicked();

private:
    Ui::DetalleRecetaDialog *ui;
    QString usuarioActual;
    receta* recetaActual = nullptr;
};

#endif // DETALLERECETADIALOG_H
