#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<map>
#include<set>
using namespace std;

// Base class for all systems in the Stronghold game
class System {
public:
    virtual void update() = 0; // Pure virtual function for system updates
    virtual void saveToFile(const  string& filename) = 0; // Save state to a file
    virtual void loadFromFile(const  string& filename) = 0; // Load state from a file
    virtual ~System() {} // Virtual destructor for proper cleanup
};

// Population class to manage population dynamics like peasants and merchants and nobles
class Population : public System {
private:
    int peasants;
    int merchants;
    int nobles;

public:
    Population();
    void growPopulation();
    void shrinkPopulation();
    void revolt();
    void update() override;
    void saveToFile(const  string& filename) override;
    void loadFromFile(const  string& filename) override;
     string getStatus() const; // Returns population status as a string
};

// Military class to manage the army
class Military : public System {
private:
    int armySize;
    int morale;
    bool isCorrupt;

public:
    Military();
    void recruitSoldiers(int count);
    void trainArmy();
    void payArmy();
    void decreaseMorale();
    void update() override;
    void saveToFile(const  string& filename) override;
    void loadFromFile(const  string& filename) override;
     string getStatus() const; // Returns military status as a string
};

// Economy class to manage the kingdom's economy
class Economy : public System {
private:
    int treasury;
    float taxRate;
    float inflation;

public:
    Economy();
    void collectTaxes(int population);
    void adjustTaxRate(float newRate);
    void handleInflation();
    void update() override;
    void saveToFile(const  string& filename) override;
    void loadFromFile(const  string& filename) override;
     string getStatus() const; // Returns economic status as a string
};

// Leadership class to manage leadership mechanics
class Leadership : public System {
private:
     string leaderName;
     string leadershipStyle; // e.g., "Democratic", "Autocratic"
    bool isCoupAttempted;

public:
    Leadership();
    void electLeader(const  string& name, const  string& style);
    void handleCoup();
    void update() override;
    void saveToFile(const  string& filename) override;
    void loadFromFile(const  string& filename) override;
     string getStatus() const; // Returns leadership status as a string
};

// Banking class to manage loans, interest, and audits
class Banking : public System {
private:
    int loanAmount;
    float interestRate;
    bool isFraudDetected;

public:
    Banking();
    void takeLoan(int amount, float rate);
    void auditBank();
    void repayLoan(int amount);
    void update() override;
    void saveToFile(const  string& filename) override;
    void loadFromFile(const  string& filename) override;
     string getStatus() const; // Returns banking status as a string
};

// Resources class to manage resource gathering and consumption
class Resources : public System {
private:
    int food;
    int wood;
    int stone;
    int iron;

public:
    Resources();
    void gatherResources();
    void consumeResources(int foodConsumed, int woodConsumed, int stoneConsumed, int ironConsumed);
    void tradeResources(int foodTraded, int woodTraded, int stoneTraded, int ironTraded);
    void update() override;
    void saveToFile(const  string& filename) override;
    void loadFromFile(const  string& filename) override;
     string getStatus() const; // Returns resource status as a string
};

// Events class to handle random events like famine, war, etc.
class Events : public System {
private:
     string lastEvent;
public:
    Events();
    string triggerRandomEvent();
    void update() override;
    void saveToFile(const  string& filename) override;
    void loadFromFile(const  string& filename) override;
    string getStatus() const;
};

class Kingdom {
private:
     string name;
    Population population;
    Military military;
    Economy economy;
    Leadership leadership;
    Banking banking;
    Resources resources;
    Events events;
    string lastEvents = "No Event Triggerd";
public:
    Kingdom(const  string& kingdomName);
     string getName() const;
    Economy& getEconomy();
    Military& getMilitary();
    Banking& getBanking();
    Leadership& getLeadership();
    Resources& getResources();
    void updateAllSystems();
    void displayStatus() const;
    void eventTrigger();
    string getLastEvent() const;
    // Save/load functionality
    void saveState();
    void loadState();
};


struct Message {
     string sender;
     string receiver;
     string content;
};

class ChatSystem {
private:
     vector<Message> chatLog;

public:
    void sendMessage(const  string& sender, const  string& receiver, const  string& content);
    void displayChat() const;
    void saveChatToFile(const  string& filename) const;
    void loadChatFromFile(const  string& filename);
};

class DiplomacySystem {
private:
     map< string,  set< string>> alliances;
     vector< string> history;

public:
    void formAlliance(const  string& k1, const  string& k2);
    void breakAlliance(const  string& k1, const  string& k2);
    bool isAllied(const  string& k1, const  string& k2) const;

    void viewAlliances() const;
    void viewHistory() const;

    void saveToFile(const  string& filename) const;
    void loadFromFile(const  string& filename);
};


struct TradeRecord {
     string sender;
     string receiver;
     string type;  
     string resource;
    int amount;
    bool success;
};

class TradeSystem {
private:
     vector<TradeRecord> history;

public:
    void performTrade(const  string& sender, const  string& receiver, const  string& resource, int amount);
    void performSmuggling(const  string& sender, const  string& receiver, const  string& resource, int amount);

    void viewHistory() const;
    void saveToFile(const  string& filename) const;
    void loadFromFile(const  string& filename);
};

struct ConflictLog {
     string attacker;
     string defender;
    bool betrayal;
    bool attackerWon;
};

class ConflictSystem {
private:
     vector<ConflictLog> history;

public:
    void declareWar(Kingdom& attacker, Kingdom& defender, DiplomacySystem& diplomacy);
    void viewConflictHistory() const;
    void saveToFile(const  string& filename) const;
    void loadFromFile(const  string& filename);
};


struct Position {
    int x, y;
};

class MapSystem {
private:
    int width, height;
     map< string, Position> kingdomPositions;
    Position pos;
    const  string name;
    char** grid;
public:
    MapSystem(int w = 10, int h = 10); 
     set< string> structures; 
    void buildStructure(const  string& name,  string strut);
    bool hasStructure(const  string& name) const;

    void placeKingdom(const  string& name, int x, int y);
    void moveKingdom(const  string& name, const  string& direction);
    void displayMap() const;
    Position getPosition(const  string& name) const;
};

#endif


