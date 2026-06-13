#ifndef INSTRUCCIONESDIALOG_H
#define INSTRUCCIONESDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class InstruccionesDialog;
}

class InstruccionesDialog : public QDialog
{
    Q_OBJECT

public:
    explicit InstruccionesDialog(QWidget *parent = nullptr);
    ~InstruccionesDialog();

    void setUsuario(QString nombre) { usuarioActual = nombre; }
    QString usuarioActual;

private slots:
    void on_btnAgregarPaso_clicked();
    void on_btnFinalizar_clicked();

private:
    Ui::InstruccionesDialog *ui;
};

#endif // INSTRUCCIONESDIALOG_H
