#include "observer.h"

void Subject::registerObserver(Observer* observer) {
    if (!observers.contains(observer)) {
        observers.append(observer);
    }
}

void Subject::removeObserver(Observer* observer) {
    observers.removeOne(observer);
}

void Subject::notifyObservers(QString message) {
    for (auto observer : observers) {
        observer->update(message);
    }
}
