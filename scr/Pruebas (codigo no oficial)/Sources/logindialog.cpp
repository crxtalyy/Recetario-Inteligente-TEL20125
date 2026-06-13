#include "logindialog.h"
#include "ui_logindialog.h"
#include <QMessageBox>
#include <QFile>
#include <QTextStream>
#include <QDir>

Logindialog::Logindialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Logindialog)
{
    ui->setupUi(this);
}

Logindialog::~Logindialog()
{
    delete ui;
}

QString Logindialog::getUsuarioIngresado()
{
    return ui->lineEdit->text();
}

void Logindialog::on_pushButton_clicked()
{
    QString usuario = ui->lineEdit->text();
    QString contrasena = ui->lineEdit_2->text();

    if(usuario.isEmpty() || contrasena.isEmpty()) {
        QMessageBox::warning(this, "Error", "Por favor completa ambos campos.");
        return;
    }

    QDir().mkpath("usuarios");
    QString ruta = "usuarios/" + usuario + ".txt";
    QFile archivo(ruta);

    if (archivo.exists()) {
        archivo.open(QIODevice::ReadOnly | QIODevice::Text);
        QTextStream in(&archivo);
        QString passGuardada = in.readLine();
        archivo.close();

        if (contrasena == passGuardada) {
            accept();
        } else {
            QMessageBox::critical(this, "Error", "Contraseña incorrecta.");
        }
    } else {
        archivo.open(QIODevice::WriteOnly | QIODevice::Text);
        QTextStream out(&archivo);
        out << contrasena;
        archivo.close();

        QMessageBox::information(this, "Bienvenido", "Usuario registrado correctamente.");
        accept();
    }
}
