#include "strongHold.h"
#include <iostream>

Kingdom::Kingdom(const  string& kingdomName) : name(kingdomName) {}

 string Kingdom::getName() const {
    return name;
}

void Kingdom::updateAllSystems() {
    population.update();
    military.update();
    economy.update();
    leadership.update();
    banking.update();
    resources.update();
    events.update();
}

void Kingdom::displayStatus() const {
    cout << "\n=== Status of " << name << " ===\n";
    cout << population.getStatus() << "\n";
    cout << military.getStatus() << "\n";
    cout << economy.getStatus() << "\n";
    cout << leadership.getStatus() << "\n";
    cout << banking.getStatus() << "\n";
    cout << resources.getStatus() << "\n";
    cout << getLastEvent() << "\n";
    
}

string Kingdom::getLastEvent() const {
    return events.getStatus();
}

void Kingdom::saveState() {
    population.saveToFile(name + "_population.txt");
    military.saveToFile(name + "_military.txt");
    economy.saveToFile(name + "_economy.txt");
    leadership.saveToFile(name + "_leadership.txt");
    banking.saveToFile(name + "_banking.txt");
    resources.saveToFile(name + "_resources.txt");
    events.saveToFile(name + "_events.txt");
}

void Kingdom::loadState() {
    population.loadFromFile(name + "_population.txt");
    military.loadFromFile(name + "_military.txt");
    economy.loadFromFile(name + "_economy.txt");
    leadership.loadFromFile(name + "_leadership.txt");
    banking.loadFromFile(name + "_banking.txt");
    resources.loadFromFile(name + "_resources.txt");
    events.loadFromFile(name + "_events.txt");
}
void Kingdom::eventTrigger() {
    lastEvents = events.triggerRandomEvent();
}


Economy& Kingdom::getEconomy() { return economy; }
Military& Kingdom::getMilitary() { return military; }
Banking& Kingdom::getBanking() { return banking; }
Leadership& Kingdom::getLeadership() { return leadership; }
Resources& Kingdom::getResources() { return resources; }
