#include "strongHold.h"
#include <iostream>

Kingdom::Kingdom(const std::string& kingdomName) : name(kingdomName) {}

std::string Kingdom::getName() const {
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
    std::cout << "\n=== Status of " << name << " ===\n";
    std::cout << population.getStatus() << "\n";
    std::cout << military.getStatus() << "\n";
    std::cout << economy.getStatus() << "\n";
    std::cout << leadership.getStatus() << "\n";
    std::cout << banking.getStatus() << "\n";
    std::cout << resources.getStatus() << "\n";
    std::cout << events.getStatus() << "\n";
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

Economy& Kingdom::getEconomy() { return economy; }
Military& Kingdom::getMilitary() { return military; }
Banking& Kingdom::getBanking() { return banking; }
Leadership& Kingdom::getLeadership() { return leadership; }
Resources& Kingdom::getResources() { return resources; }