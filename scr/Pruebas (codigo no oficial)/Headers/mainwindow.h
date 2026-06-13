#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "receta.h"
#include <QMainWindow>
#include <QString>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    void setUsuario(QString nombre);
    QString usuarioActual;

private slots:
    void on_btnAgregarReceta_clicked();
    void on_btnVerRecetas_clicked();
    void on_btnPresupuesto_clicked();
    void on_btnCerrarSesion_clicked();

private:
    Ui::MainWindow *ui;
};
#endif
