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
string Events::triggerRandomEvent() {
    int eventType = rand() % 7; // Randomly select an event type (0-6)
    switch (eventType) {
    case 0:
        lastEvent = "Famine: Food supply has drastically decreased.";
         return lastEvent ;
        break;
    case 1:
        lastEvent = "Disease Outbreak: Population health is severely affected.";
         return lastEvent ;
        break;
    case 2:
        lastEvent = "War: Enemy forces are attacking your kingdom.";
        return lastEvent;
        break;
    case 3:
        lastEvent = "Drought: Water sources have dried up, affecting agriculture.";
        return lastEvent;
        break;
    case 4:
        lastEvent = "Betrayal: A trusted advisor has betrayed you.";
        return lastEvent;
        break;
    case 5:
        lastEvent = "Bountiful Harvest: Resources are abundant this season.";
        return lastEvent;
        break;
    case 6:
        lastEvent = "Weather Storm: Severe weather damages infrastructure.";
        return lastEvent;
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
         cout << "No significant events occurred this turn.\n";
    }
}

// Save event state to a file
void Events::saveToFile(const  string& filename) {
     ofstream file(filename);
    if (file.is_open()) {
        file << lastEvent;
        file.close();
         cout << "Event state saved to " << filename << "\n";
    }
    else {
         cerr << "Error: Unable to save event state to file.\n";
    }
}

// Load event state from a file
void Events::loadFromFile(const  string& filename) {
     ifstream file(filename);
    if (file.is_open()) {
         getline(file, lastEvent); // Read the entire line as the last event
        file.close();
         cout << "Event state loaded from " << filename << "\n";
    }
    else {
         cout << "Error: Unable to load event state from file.\n";
    }
}
// Get event status as a string
 string Events::getStatus() const {
    return "Last Event: " + lastEvent;
}