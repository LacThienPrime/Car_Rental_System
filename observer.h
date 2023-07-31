#ifndef OBSERVER_H
#define OBSERVER_H

#include <QObject>
#include <QVector>
#include <QString>

class Observer {
public:
    virtual void update(QString message) = 0;
};

class Observer;

class Subject {
public:
    void registerObserver(Observer* observer);
    void removeObserver(Observer* observer);
    void notifyObservers(QString message);

private:
    QVector<Observer*> observers;
};

#endif // OBSERVER_H
