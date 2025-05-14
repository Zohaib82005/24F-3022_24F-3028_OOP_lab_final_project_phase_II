#include "Stronghold.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Constructor
Economy::Economy() : treasury(1000), taxRate(0.2f), inflation(1.0f) {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
}

// Method to collect taxes based on population
void Economy::collectTaxes(int population) {
    if (population <= 0) {
        throw  invalid_argument("Population must be greater than zero to collect taxes.");
    }
    int taxRevenue = static_cast<int>(population * taxRate); // Calculate tax revenue
    treasury += taxRevenue;
     cout << "Collected " << taxRevenue << " gold in taxes. Treasury: " << treasury << "\n";
}

// Method to adjust the tax rate
void Economy::adjustTaxRate(float newRate) {
    if (newRate < 0.0f || newRate > 1.0f) {
        throw  invalid_argument("Tax rate must be between 0.0 and 1.0.");
    }
    taxRate = newRate;
     cout << "Tax rate adjusted to " << taxRate * 100 << "%.\n";
}

// Method to handle inflation
void Economy::handleInflation() {
    inflation += 0.05f; // Simulate inflation increase
    if (inflation > 2.0f) inflation = 2.0f; // Cap inflation at 200%
     cout << "Inflation increased to " << inflation * 100 << "%.\n";
}

// Update method (required by the System base class)
void Economy::update() {
    // Simulate random economic events
    int event = rand() % 3; // Random event: 0 = collect taxes, 1 = inflation, 2 = adjust tax rate
    switch (event) {
    case 0:
        try {
            collectTaxes(rand() % 100 + 50); // Random population between 50 and 150
        }
        catch (const  exception& e) {
             cerr << "Error: " << e.what() << "\n";
        }
        break;
    case 1:
        handleInflation();
        break;
    case 2:
        try {
            adjustTaxRate(static_cast<float>(rand() % 100) / 100.0f); // Random tax rate between 0.0 and 1.0
        }
        catch (const  exception& e) {
             cerr << "Error: " << e.what() << "\n";
        }
        break;
    }
}

// Save economic state to a file
void Economy::saveToFile(const  string& filename) {
     ofstream file(filename);
    if (file.is_open()) {
        file << treasury << " " << taxRate << " " << inflation;
        file.close();
         cout << "Economic state saved to " << filename << "\n";
    }
    else {
         cerr << "Error: Unable to save economic state to file.\n";
    }
}


void Economy::loadFromFile(const  string& filename) {
     ifstream file(filename);
    if (file.is_open()) {
        file >> treasury >> taxRate >> inflation;
        file.close();
         cout << "Economic state loaded from " << filename << "\n";
    }
    else {
         cerr << "Error: Unable to load economic state from file.\n";
    }
}


 string Economy::getStatus() const {
    return "Treasury: " +  to_string(treasury) +
        ", Tax Rate: " +  to_string(taxRate * 100) + "%" +
        ", Inflation: " +  to_string(inflation * 100) + "%";
}