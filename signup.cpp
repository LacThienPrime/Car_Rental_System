#include "signup.h"
#include "ui_signup.h"

SignUp::SignUp(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::SignUp)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, &QPushButton::clicked, [=](){
        cleanLineEdit();
        this->hide();
    });
}

void SignUp::on_pushButton_clicked()
{
    connectDatabase();

    if(myData.open()) {
        qDebug() << "database connect succeed" << Qt::endl;

        getInput();

        QSqlQuery sql;
        QString checkExist = "select * from users where userName = '"+signName+"'";

        if(signName.isEmpty() || signPassword.isEmpty() ||
            signEmail.isEmpty() || signPhone.isEmpty())
        {
            QMessageBox::about(this, "sign up failed", "Please fill in all the information");
        }

        else if(sql.exec(checkExist))
        {
            if(sql.next() == true)
            {
                QMessageBox::information(this, "Not Inserted", "This user name already exist");
            }
            else if(sql.next() == false)
            {
                insertData();
                //cleanLineEdit();
            }
        }
    }

    else {
        QMessageBox::information(this, "Not connected", "database is not conntected");
    }
}

void SignUp::connectDatabase()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        myData = QSqlDatabase::database("qt_sql_default_connection");
    }

    else
    {
        myData = QSqlDatabase::addDatabase("QSQLITE");
    }

    myData.setHostName("localhost");
    myData.setUserName("Root");
    myData.setPassword("");

    myData.setDatabaseName("C:/Users/Rome/Documents/CarRentSystem/usersData.db");
}

void SignUp::insertData()
{
    getInput();

    QSqlQuery sql2;
    sql2.prepare("INSERT INTO users (userName, password, email, phoneNumber)" "VALUES (:userName, :password, :email, :phoneNumber)");
    sql2.bindValue(":userName", signName);
    sql2.bindValue(":password", signPassword);
    sql2.bindValue(":email", signEmail);
    sql2.bindValue(":phoneNumber", signPhone);

    if (sql2.exec())
    {
        QMessageBox::about(this, "Successful", "Sign Up successful, please back to Log in");
    }

    else
    {
        QMessageBox::about(this, "failed", "Sign Up failed, please check if connect database");
    }
}

void SignUp::getInput()
{
    signName = ui->lineEdit->text();
    signPassword = ui->lineEdit_2->text();
    signEmail = ui->lineEdit_3->text();
    signPhone = ui->lineEdit_4->text();
}

void SignUp::cleanLineEdit()
{
    ui->lineEdit->clear();
    ui->lineEdit_2->clear();
    ui->lineEdit_3->clear();
    ui->lineEdit_4->clear();
}

SignUp::~SignUp()
{
    delete ui;
}
