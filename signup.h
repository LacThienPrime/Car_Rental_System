#ifndef SIGNUP_H
#define SIGNUP_H

#include <QDialog>
#include <QMessageBox>
#include <QString>
#include <QSqlQueryModel>
#include <QSqlQuery>
#include <QDebug>
#include <QSqlError>
#include <QPainter>

namespace Ui {
class SignUp;
}

class SignUp : public QDialog
{
    Q_OBJECT

public:
    explicit SignUp(QWidget *parent = nullptr);
    ~SignUp();

    void getInput();
    void cleanLineEdit();
    void connectDatabase();
    void insertData();

private slots:
    void on_pushButton_clicked();

private:
    Ui::SignUp *ui;
    QSqlDatabase myData;

    QString signName;
    QString signPassword;
    QString signEmail;
    QString signPhone;
};

#endif // SIGNUP_H
