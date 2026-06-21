#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <deque>
#include "recetas.h"
using namespace std;

QT_BEGIN_NAMESPACE
namespace Ui{
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow() override;
    
private slots:
    void on_BotonEnter_clicked();
    void on_crearReceta_clicked();
    void on_nextF2_clicked();
    void on_nextF3_clicked();
    void on_home_clicked();
    void on_adios_clicked();
    void on_listaRecetas_currentRowChanged(int currentRow);
    void on_backMenu_clicked();
    void on_escalar_clicked();
    void on_UserBox_textChanged(const QString &arg1);
    void on_PassBox_textChanged(const QString &arg1);

private:
    Ui::MainWindow *ui;
    void cargarRecetas();
    deque<recetas> listaRecetas;
    recetas actual;
    void activarLogin();
};
#endif // MAINWINDOW_H
