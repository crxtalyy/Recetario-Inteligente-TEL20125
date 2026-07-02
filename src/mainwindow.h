#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMainWindow>
#include <deque>
#include "recetas.h"
#include <QtCharts/QChartView>
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
    QChart *doPieChart();
    
private slots:
    void on_UserBox_textChanged(const QString &arg1);
    void on_PassBox_textChanged(const QString &arg1);
    void on_nameReceta_textChanged(const QString &arg1);
    void on_cantPersonas_valueChanged(int arg1);
    void on_cantIngredientes_valueChanged(int arg1);
    void on_queEs_textChanged(const QString &arg1);
    void on_cuantoEs_valueChanged(double arg1);
    void on_unidad_currentIndexChanged(int index);
    void on_nutriente_currentIndexChanged(int index);
    void on_sts_textChanged();
    void on_usuarioBox_textChanged(const QString &arg1);
    void on_contraBox_textChanged(const QString &arg1);

    void on_BotonEnter_clicked();
    void on_crearReceta_clicked();
    void on_nextF2_clicked();
    void on_nextF3_clicked();
    void on_home_clicked();
    void on_adios_clicked();
    void on_listaRecetas_currentRowChanged(int currentRow);
    void on_backMenu_clicked();
    void on_escalar_clicked();
    void on_menu_clicked();
    void on_ingreso_clicked();
    void on_nueva_clicked();
    void on_newaccount_clicked();
    void on_genGrafico_clicked();
    void on_borrar_clicked();

private:
    Ui::MainWindow *ui;
    void cargarRecetas();
    deque<recetas> listaRecetas;
    recetas actual;
    void activarLogin();
    void activarF1();
    void activarF2();
    void activarF3();
    void activarSignin();
};
#endif // MAINWINDOW_H
