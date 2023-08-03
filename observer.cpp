#include "observer.h"

void Car::registerCustomer(Customer* customer) {
    if (!customers.contains(customer)) {
        customers.append(customer);
    }
}

void Car::removeCustomer(Customer* customer) {
    customers.removeOne(customer);
}

void Car::notifyCustomer(QString message) {
    for (auto customer : customers) {
        customer->update(message);
    }
}
