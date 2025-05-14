#include "strongHold.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Constructor
Population::Population() : peasants(100), merchants(50), nobles(10) {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
}

// Method to grow population
void Population::growPopulation() {
    peasants += rand() % 10 + 1; // Random growth between 1 and 10
    merchants += rand() % 5 + 1; // Random growth between 1 and 5
    nobles += rand() % 2 + 1;    // Random growth between 1 and 2
}

// Method to shrink population
void Population::shrinkPopulation() {
    peasants -= rand() % 10 + 1; // Random shrinkage between 1 and 10
    merchants -= rand() % 5 + 1; // Random shrinkage between 1 and 5
    nobles -= rand() % 2 + 1;    // Random shrinkage between 1 and 2

    // Ensure population does not go below zero
    if (peasants < 0) peasants = 0;
    if (merchants < 0) merchants = 0;
    if (nobles < 0) nobles = 0;
}

// Method to simulate a revolt
void Population::revolt() {
     cout << "The population is revolting!\n";
    peasants /= 2; // Lose half the peasants
    merchants /= 2; // Lose half the merchants
    nobles /= 2;    // Lose half the nobles
}

// Update method (required by the System base class)
void Population::update() {
    // Simulate population changes based on random events
    int event = rand() % 3; // Random event: 0 = grow, 1 = shrink, 2 = revolt
    switch (event) {
    case 0:
        growPopulation();
        break;
    case 1:
        shrinkPopulation();
        break;
    case 2:
        revolt();
        break;
    }
}

// Save population state to a file
void Population::saveToFile(const  string& filename) {
     ofstream file(filename);
    if (file.is_open()) {
        file << peasants << " " << merchants << " " << nobles;
        file.close();
         cout << "Population saved to " << filename << "\n";
    }
    else {
         cerr << "Error: Unable to save population to file.\n";
    }
}

// Load population state from a file
void Population::loadFromFile(const  string& filename) {
     ifstream file(filename);
    if (file.is_open()) {
        file >> peasants >> merchants >> nobles;
        file.close();
         cout << "Population loaded from " << filename << "\n";
    }
    else {
         cerr << "Error: Unable to load population from file.\n";
    }
}

// Get population status as a string
 string Population::getStatus() const {
    return "Peasants: " +  to_string(peasants) +
        ", Merchants: " +  to_string(merchants) +
        ", Nobles: " +  to_string(nobles);
}
