#include "strongHold.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Constructor
Leadership::Leadership() : leaderName("No Leader"), leadershipStyle("Neutral"), isCoupAttempted(false) {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
}

// Method to elect a new leader
void Leadership::electLeader(const  string& name, const  string& style) {
    if (name.empty() || style.empty()) {
        throw  invalid_argument("Leader name and leadership style must not be empty.");
    }
    leaderName = name;
    leadershipStyle = style;
    isCoupAttempted = false; // Reset coup status after election
     cout << "New leader elected: " << leaderName << " (" << leadershipStyle << ")\n";
}

// Method to handle a coup attempt
void Leadership::handleCoup() {
    if (isCoupAttempted) {
         cout << "A coup has already been attempted. Stability is fragile.\n";
        return;
    }
    int successChance = rand() % 100; // Random chance of coup success (0-99)
    if (successChance < 30) { // 30% chance of success
        leaderName = "Rebel Leader";
        leadershipStyle = "Autocratic";
        isCoupAttempted = true;
         cout << "Coup successful! New leader: " << leaderName << " (" << leadershipStyle << ")\n";
    }
    else {
         cout << "Coup attempt failed. Current leader remains in power.\n";
    }
}

// Update method (required by the System base class)
void Leadership::update() {
    // Simulate random leadership events
    int event = rand() % 3; // Random event: 0 = coup, 1 = election, 2 = no event
    switch (event) {
    case 0:
        handleCoup();
        break;
    case 1:
        try {
            electLeader("Elected Leader", "Democratic");
        }
        catch (const  exception& e) {
             cerr << "Error: " << e.what() << "\n";
        }
        break;
    case 2:
         cout << "No significant leadership changes this turn.\n";
        break;
    }
}

// Save leadership state to a file
void Leadership::saveToFile(const  string& filename) {
     ofstream file(filename);
    if (file.is_open()) {
        file << leaderName << " " << leadershipStyle << " " << isCoupAttempted;
        file.close();
         cout << "Leadership state saved to " << filename << "\n";
    }
    else {
         cerr << "Error: Unable to save leadership state to file.\n";
    }
}

// Load leadership state from a file
void Leadership::loadFromFile(const  string& filename) {
     ifstream file(filename);
    if (file.is_open()) {
        file >> leaderName >> leadershipStyle >> isCoupAttempted;
        file.close();
         cout << "Leadership state loaded from " << filename << "\n";
    }
    else {
         cout << "Error: Unable to load leadership state from file.\n";
    }
}

// Get leadership status as a string
 string Leadership::getStatus() const {
    return "Leader: " + leaderName +
        ", Style: " + leadershipStyle +
        ", Coup Attempted: " + (isCoupAttempted ? "Yes" : "No");
}