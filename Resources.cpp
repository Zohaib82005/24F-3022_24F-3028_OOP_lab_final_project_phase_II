#include "strongHold.h"
#include <iostream>
#include <fstream>
#include <cstdlib> // For rand()
#include <ctime>   // For time()

// Constructor
Resources::Resources() : food(500), wood(300), stone(200), iron(100) {
    srand(static_cast<unsigned>(time(0))); // Seed random number generator
}

// Method to gather resources
void Resources::gatherResources() {
    food += rand() % 50 + 10;    // Random food gathered between 10 and 60
    wood += rand() % 40 + 10;    // Random wood gathered between 10 and 50
    stone += rand() % 30 + 5;    // Random stone gathered between 5 and 35
    iron += rand() % 20 + 5;     // Random iron gathered between 5 and 25
     cout << "Resources gathered: Food=" << food << ", Wood=" << wood
        << ", Stone=" << stone << ", Iron=" << iron << "\n";
}

// Method to consume resources
void Resources::consumeResources(int foodConsumed, int woodConsumed, int stoneConsumed, int ironConsumed) {
    if (foodConsumed < 0 || woodConsumed < 0 || stoneConsumed < 0 || ironConsumed < 0) {
        throw  invalid_argument("Resource consumption values must be non-negative.");
    }
    food -= foodConsumed;
    wood -= woodConsumed;
    stone -= stoneConsumed;
    iron -= ironConsumed;

    // Ensure resources do not go below zero
    if (food < 0) food = 0;
    if (wood < 0) wood = 0;
    if (stone < 0) stone = 0;
    if (iron < 0) iron = 0;

     cout << "Resources consumed: Food=" << foodConsumed << ", Wood=" << woodConsumed
        << ", Stone=" << stoneConsumed << ", Iron=" << ironConsumed << "\n";
}

// Method to trade resources
void Resources::tradeResources(int foodTraded, int woodTraded, int stoneTraded, int ironTraded) {
    if (foodTraded > food || woodTraded > wood || stoneTraded > stone || ironTraded > iron) {
        throw  invalid_argument("Cannot trade more resources than available.");
    }
    food -= foodTraded;
    wood -= woodTraded;
    stone -= stoneTraded;
    iron -= ironTraded;

    // Simulate receiving other resources in return (e.g., equal exchange)
    food += woodTraded + stoneTraded + ironTraded;
    wood += foodTraded + stoneTraded + ironTraded;
    stone += foodTraded + woodTraded + ironTraded;
    iron += foodTraded + woodTraded + stoneTraded;

     cout << "Resources traded: Food=" << foodTraded << ", Wood=" << woodTraded
        << ", Stone=" << stoneTraded << ", Iron=" << ironTraded << "\n";
}

// Update method (required by the System base class)
void Resources::update() {
    // Simulate random resource events
    int event = rand() % 3; // Random event: 0 = gather, 1 = consume, 2 = trade
    switch (event) {
    case 0:
        gatherResources();
        break;
    case 1:
        try {
            consumeResources(rand() % 50, rand() % 40, rand() % 30, rand() % 20);
        }
        catch (const  exception& e) {
             cerr << "Error: " << e.what() << "\n";
        }
        break;
    case 2:
        try {
            tradeResources(rand() % 10, rand() % 10, rand() % 10, rand() % 10);
        }
        catch (const  exception& e) {
             cerr << "Error: " << e.what() << "\n";
        }
        break;
    }
}

// Save resource state to a file
void Resources::saveToFile(const  string& filename) {
     ofstream file(filename);
    if (file.is_open()) {
        file << food << " " << wood << " " << stone << " " << iron;
        file.close();
         cout << "Resource state saved to " << filename << "\n";
    }
    else {
         cerr << "Error: Unable to save resource state to file.\n";
    }
}

// Load resource state from a file
void Resources::loadFromFile(const  string& filename) {
     ifstream file(filename);
    if (file.is_open()) {
        file >> food >> wood >> stone >> iron;
        file.close();
         cout << "Resource state loaded from " << filename << "\n";
    }
    else {
         cout << "Error: Unable to load resource state from file.\n";
    }
}

// Get resource status as a string
 string Resources::getStatus() const {
    return "Food: " +  to_string(food) +
        ", Wood: " +  to_string(wood) +
        ", Stone: " +  to_string(stone) +
        ", Iron: " +  to_string(iron);
}