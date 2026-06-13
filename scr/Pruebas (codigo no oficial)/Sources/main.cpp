#include "mainwindow.h"
#include "logindialog.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    Logindialog login;

    if (login.exec() == QDialog::Accepted) {

        QString usuario = login.getUsuarioIngresado();

        MainWindow w;
        w.setUsuario(usuario);
        w.show();
        return a.exec();
    }

    return 0;
}
