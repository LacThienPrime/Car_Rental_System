#include "userscr.h"
#include "ui_userscr.h"

userscr::userscr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userscr)
{
    ui->setupUi(this);

    car.registerCustomer(this);

    connectData();
    appendData();
}

userscr::~userscr()
{
    delete ui;
}

void userscr::on_pushButton_clicked()
{
    QStringList Data;
    Data = this->getCurrentData();

    QString Result = Data.join(" ");
    car.notifyCustomer("You rent a car with ID: " + Result);
}

void userscr::on_pushButton_2_clicked()
{
    QStringList data;
    data = this->getCurrentData();

    QString result = data.join(" ");
    car.notifyCustomer("You return a car with ID: " + result);
}

void userscr::update(QString message)
{ 
    ui->listWidget->addItem(message);
}

void userscr::appendData()
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);
    ui->tableView->setModel(sqlModel);
}

QStringList userscr::getCurrentData()
{
    QStringList rowData;

    int row = ui->tableView->currentIndex().row();
    QAbstractItemModel *model = ui->tableView->model();
    //QModelIndex index0 = model->index(row, 0);

    if(row != -1)
    {
        rowData << model->index(row, 0).data().toString();
        rowData << model->index(row, 1).data().toString();
        rowData << model->index(row, 2).data().toString();
        rowData << model->index(row, 3).data().toString();
        rowData << model->index(row, 4).data().toString();
        rowData << model->index(row, 5).data().toString();
        //rowData << model->data(index0).toString();
    }
    return rowData;
}

void userscr::connectData()
{
    if(QSqlDatabase::contains("qt_sql_default_connection"))
    {
        database = QSqlDatabase::database("qt_sql_default_connection");
    }

    else
    {
        database = QSqlDatabase::addDatabase("QSQLITE");
    }

    database.setHostName("localhost");
    database.setUserName("Root");
    database.setPassword("");
    database.setDatabaseName("C:/Users/Rome/Documents/CarRentSystem/usersData.db");

    if(database.open())
    {
        sqlModel = new QSqlQueryModel();
        sqlModel->setQuery("select ID, carModel, colour from vehicles");
    }

    else
    {
        QMessageBox::information(this, "fail", "open failed");
    }
}
