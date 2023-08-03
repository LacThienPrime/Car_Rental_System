#include "userscr.h"
#include "ui_userscr.h"

userscr::userscr(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::userscr)
{
    ui->setupUi(this);

    car.registerCustomer(this);

    dbWorker = new DatabaseWorker;
    dbWorker->moveToThread(&workerThread);

    connect(&workerThread, &QThread::finished, dbWorker, &QObject::deleteLater);
    connect(this, &userscr::fetchDataFromDatabase, dbWorker, &DatabaseWorker::fetchData);
    connect(dbWorker, &DatabaseWorker::dataFetched, this, &userscr::handleFetchedData);

    workerThread.start();

    emit fetchDataFromDatabase();

    //connectData();
    //appendData();
}

userscr::~userscr()
{
    delete ui;

    workerThread.quit();
    workerThread.wait();
}

void userscr::on_pushButton_clicked()
{
    QStringList Data;
    Data = this->getCurrentData();

    if (Data.isEmpty()) {
        return;
    }

    int carId = Data.at(0).toInt();

    QSqlQuery query;
    query.prepare("UPDATE vehicles SET availability = 1 WHERE ID = :carId");
    query.bindValue(":carId", carId);

    if (query.exec()) {
        car.notifyCustomer("You rent a car with ID: " + QString::number(carId));
    } else {
        car.notifyCustomer("Failed to rent the car.");
    }

    appendData();
}

void userscr::on_pushButton_2_clicked()
{
    QStringList data;
    data = this->getCurrentData();

    if (data.isEmpty()) {
        return;
    }

    int carId = data.at(0).toInt();

    QSqlQuery query;
    query.prepare("UPDATE vehicles SET availability = 0 WHERE ID = :carId");
    query.bindValue(":carId", carId);

    if (query.exec()) {
        car.notifyCustomer("You return a car with ID: " + QString::number(carId));
    } else {
        car.notifyCustomer("Failed to return the car.");
    }

    appendData();
}

void userscr::update(QString message)
{ 
    ui->listWidget->addItem(message);
}

void userscr::appendData()
{
    ui->tableView->setSelectionBehavior(QAbstractItemView::SelectRows);

    sqlModel = new QSqlQueryModel();
    sqlModel->setQuery("SELECT ID, carModel, colour FROM vehicles WHERE availability = 0");

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

void userscr::handleFetchedData(QSqlQueryModel *model)
{
    if (model)
    {
        ui->tableView->setModel(model);
    }
    else
    {
        QMessageBox::information(this, "Fail", "Failed to fetch data from the database.");
    }
}
