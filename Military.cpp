#include "strongHold.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Constructor
Military::Military() : armySize(50), morale(100), isCorrupt(false) {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
}

// Method to recruit soldiers
void Military::recruitSoldiers(int count) {
    if (count <= 0) {
        throw std::invalid_argument("Recruitment count must be positive.");
    }
    armySize += count;
    std::cout << "Recruited " << count << " soldiers. New army size: " << armySize << "\n";
}

// Method to train the army
void Military::trainArmy() {
    if (morale < 50) {
        std::cout << "Morale too low to train the army effectively.\n";
        return;
    }
    morale += 10; // Training boosts morale
    std::cout << "Army trained. Morale increased to " << morale << ".\n";
}

// Method to pay the army
void Military::payArmy() {
    if (isCorrupt) {
        std::cout << "Corruption detected! Payment failed.\n";
        morale -= 20; // Corruption lowers morale
        if (morale < 0) morale = 0;
        return;
    }
    morale += 15; // Payment boosts morale
    std::cout << "Army paid. Morale increased to " << morale << ".\n";
}

// Method to decrease morale
void Military::decreaseMorale() {
    morale -= rand() % 20 + 1; // Random decrease between 1 and 20
    if (morale < 0) morale = 0;
    std::cout << "Army morale decreased to " << morale << ".\n";
}

// Update method (required by the System base class)
void Military::update() {
    // Simulate random military events
    int event = rand() % 3; // Random event: 0 = train, 1 = decrease morale, 2 = corruption check
    switch (event) {
    case 0:
        trainArmy();
        break;
    case 1:
        decreaseMorale();
        break;
    case 2:
        if (rand() % 100 < 20) { // 20% chance of corruption
            isCorrupt = true;
            std::cout << "Corruption detected in the military!\n";
        }
        else {
            isCorrupt = false;
        }
        break;
    }
}

// Save military state to a file
void Military::saveToFile(const std::string& filename) {
    std::ofstream file(filename);
    if (file.is_open()) {
        file << armySize << " " << morale << " " << isCorrupt;
        file.close();
        std::cout << "Military state saved to " << filename << "\n";
    }
    else {
        std::cerr << "Error: Unable to save military state to file.\n";
    }
}

// Load military state from a file
void Military::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        file >> armySize >> morale >> isCorrupt;
        file.close();
        std::cout << "Military state loaded from " << filename << "\n";
    }
    else {
        std::cerr << "Error: Unable to load military state from file.\n";
    }
}

// Get military status as a string
std::string Military::getStatus() const {
    return "Army Size: " + std::to_string(armySize) +
        ", Morale: " + std::to_string(morale) +
        ", Corruption: " + (isCorrupt ? "Yes" : "No");
}