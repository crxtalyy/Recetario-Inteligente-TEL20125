#ifndef LOGINDIALOG_H
#define LOGINDIALOG_H

#include <QDialog>
#include <QString>

namespace Ui {
class Logindialog;
}

class Logindialog : public QDialog
{
    Q_OBJECT

public:
    explicit Logindialog(QWidget *parent = nullptr);
    ~Logindialog();

    QString getUsuarioIngresado();

private slots:
    void on_pushButton_clicked();

private:
    Ui::Logindialog *ui;
};

#endif // LOGINDIALOG_H
