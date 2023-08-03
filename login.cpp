#include "login.h"
#include "ui_login.h"

using namespace Qt;

Login::Login(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Login)
{
    ui->setupUi(this);

    ptrSignUp = new SignUp();
    ptrMain = new mainscr();
    ptrUserScr = new userscr();
}

void Login::on_pushButton_2_clicked()
{
    ptrSignUp->show();
}

void Login::on_pushButton_clicked()
{
    connectDatabase();

    if(db.open()) {
        matchDatabase();
    }

    else {
        QMessageBox::information(this, "database", "connection failed");
    }
}

void Login::connectDatabase(){
    if(QSqlDatabase::contains("qt_sql_default_connection")) {
        db = QSqlDatabase::database("qt_sql_default_connection");
    }

    else {
        db = QSqlDatabase::addDatabase("QSQLITE");
    }

    db.setHostName("localhost");
    db.setUserName("Root");
    db.setPassword("");

    db.setDatabaseName("C:/Users/Rome/Documents/CarRentSystem/usersData.db");
}

void Login::matchDatabase()
{
    QString userName = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    qDebug() << "connection succeed";

    QSqlQuery query(QSqlDatabase::database("QSQLITE"));
    query.prepare(QString("Select * from users Where userName = :userName " "And password = :password"));

    query.bindValue(":userName", userName);
    query.bindValue(":password", password);

    if(!query.exec())
    {
        QMessageBox::information(this, "failed", "failed to execute");
    }

    else
    {
        if(query.next())
        {
            QString userNameFromDB = query.value(0).toString();
            QString passwordFromDB = query.value(1).toString();

            if(userNameFromDB == "rome" && passwordFromDB == "rome")
            {
                qDebug() << "Admin login"<< endl;
                ptrMain->show();
            }

            else if(userNameFromDB == userName && passwordFromDB == password)
            {
                ptrUserScr->show();
            }
        }

        else
        {
            QMessageBox::information(this, "failed", "Log in failed, Please check your username or password");
        }
    }
}

Login::~Login()
{
    delete ui;
}
