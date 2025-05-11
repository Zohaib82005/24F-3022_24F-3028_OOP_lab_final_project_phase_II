#include "strongHold.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Constructor
Events::Events() : lastEvent("No Event") {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
}

// Method to trigger a random event
void Events::triggerRandomEvent() {
    int eventType = rand() % 7; // Randomly select an event type (0-6)
    switch (eventType) {
    case 0:
        lastEvent = "Famine: Food supply has drastically decreased.";
        std::cout << lastEvent << "\n";
        break;
    case 1:
        lastEvent = "Disease Outbreak: Population health is severely affected.";
        std::cout << lastEvent << "\n";
        break;
    case 2:
        lastEvent = "War: Enemy forces are attacking your kingdom.";
        std::cout << lastEvent << "\n";
        break;
    case 3:
        lastEvent = "Drought: Water sources have dried up, affecting agriculture.";
        std::cout << lastEvent << "\n";
        break;
    case 4:
        lastEvent = "Betrayal: A trusted advisor has betrayed you.";
        std::cout << lastEvent << "\n";
        break;
    case 5:
        lastEvent = "Bountiful Harvest: Resources are abundant this season.";
        std::cout << lastEvent << "\n";
        break;
    case 6:
        lastEvent = "Weather Storm: Severe weather damages infrastructure.";
        std::cout << lastEvent << "\n";
        break;
    }
}

// Update method (required by the System base class)
void Events::update() {
    // Simulate random events occurring periodically
    int chance = rand() % 100; // Random chance (0-99)
    if (chance < 30) { // 30% chance of triggering an event
        triggerRandomEvent();
    }
    else {
        std::cout << "No significant events occurred this turn.\n";
    }
}

// Save event state to a file
void Events::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << lastEvent;
        file.close();
        std::cout << "Event state saved to " << filename << "\n";
    }
    else {
        std::cerr << "Error: Unable to save event state to file.\n";
    }
}

// Load event state from a file
void Events::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        std::getline(file, lastEvent); // Read the entire line as the last event
        file.close();
        std::cout << "Event state loaded from " << filename << "\n";
    }
    else {
        std::cerr << "Error: Unable to load event state from file.\n";
    }
}

// Get event status as a string
std::string Events::getStatus() const {
    return "Last Event: " + lastEvent;
}