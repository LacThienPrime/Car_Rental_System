#ifndef OBSERVER_H
#define OBSERVER_H

#include <QObject>
#include <QVector>
#include <QString>

class Customer {
public:
    virtual ~Customer() {};

    virtual void update(QString message) = 0;
};

class Car {
public:
    void registerCustomer(Customer* customer);
    void removeCustomer(Customer* customer);
    void notifyCustomer(QString message);

private:
    QVector<Customer*> customers;
};

#endif // OBSERVER_H
