#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<map>
#include<set>


// Base class for all systems in the Stronghold game
class System {
public:
    virtual void update() = 0; // Pure virtual function for system updates
    virtual void saveToFile(const std::string& filename) = 0; // Save state to a file
    virtual void loadFromFile(const std::string& filename) = 0; // Load state from a file
    virtual ~System() {} // Virtual destructor for proper cleanup
};

// Population class to manage population dynamics
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
    void saveToFile(const std::string& filename) override;
    void loadFromFile(const std::string& filename) override;
    std::string getStatus() const; // Returns population status as a string
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
    void saveToFile(const std::string& filename) override;
    void loadFromFile(const std::string& filename) override;
    std::string getStatus() const; // Returns military status as a string
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
    void saveToFile(const std::string& filename) override;
    void loadFromFile(const std::string& filename) override;
    std::string getStatus() const; // Returns economic status as a string
};

// Leadership class to manage leadership mechanics
class Leadership : public System {
private:
    std::string leaderName;
    std::string leadershipStyle; // e.g., "Democratic", "Autocratic"
    bool isCoupAttempted;

public:
    Leadership();
    void electLeader(const std::string& name, const std::string& style);
    void handleCoup();
    void update() override;
    void saveToFile(const std::string& filename) override;
    void loadFromFile(const std::string& filename) override;
    std::string getStatus() const; // Returns leadership status as a string
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
    void saveToFile(const std::string& filename) override;
    void loadFromFile(const std::string& filename) override;
    std::string getStatus() const; // Returns banking status as a string
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
    void saveToFile(const std::string& filename) override;
    void loadFromFile(const std::string& filename) override;
    std::string getStatus() const; // Returns resource status as a string
};

// Events class to handle random events like famine, war, etc.
class Events : public System {
private:
    std::string lastEvent;

public:
    Events();
    void triggerRandomEvent();
    void update() override;
    void saveToFile(const std::string& filename) override;
    void loadFromFile(const std::string& filename) override;
    std::string getStatus() const; // Returns the last event triggered
};

class Kingdom {
private:
    std::string name;
    Population population;
    Military military;
    Economy economy;
    Leadership leadership;
    Banking banking;
    Resources resources;
    Events events;
   
public:
    Kingdom(const std::string& kingdomName);
    std::string getName() const;
    Economy& getEconomy();
    Military& getMilitary();
    Banking& getBanking();
    Leadership& getLeadership();
    Resources& getResources();
    void updateAllSystems();
    void displayStatus() const;

    // Save/load functionality
    void saveState();
    void loadState();
};


struct Message {
    std::string sender;
    std::string receiver;
    std::string content;
};

class ChatSystem {
private:
    std::vector<Message> chatLog;

public:
    void sendMessage(const std::string& sender, const std::string& receiver, const std::string& content);
    void displayChat() const;
    void saveChatToFile(const std::string& filename) const;
    void loadChatFromFile(const std::string& filename);
};

class DiplomacySystem {
private:
    std::map<std::string, std::set<std::string>> alliances;
    std::vector<std::string> history;

public:
    void formAlliance(const std::string& k1, const std::string& k2);
    void breakAlliance(const std::string& k1, const std::string& k2);
    bool isAllied(const std::string& k1, const std::string& k2) const;

    void viewAlliances() const;
    void viewHistory() const;

    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};


struct TradeRecord {
    std::string sender;
    std::string receiver;
    std::string type;  // "Trade" or "Smuggle"
    std::string resource;
    int amount;
    bool success;
};

class TradeSystem {
private:
    std::vector<TradeRecord> history;

public:
    void performTrade(const std::string& sender, const std::string& receiver, const std::string& resource, int amount);
    void performSmuggling(const std::string& sender, const std::string& receiver, const std::string& resource, int amount);

    void viewHistory() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};

struct ConflictLog {
    std::string attacker;
    std::string defender;
    bool betrayal;
    bool attackerWon;
};

class ConflictSystem {
private:
    std::vector<ConflictLog> history;

public:
    void declareWar(Kingdom& attacker, Kingdom& defender, DiplomacySystem& diplomacy);
    void viewConflictHistory() const;
    void saveToFile(const std::string& filename) const;
    void loadFromFile(const std::string& filename);
};


struct Position {
    int x, y;
};

class MapSystem {
private:
    int width, height;
    std::map<std::string, Position> kingdomPositions;
    Position pos;
    const std::string name;
    char** grid;
public:
    MapSystem(int w = 10, int h = 10); // Default 10x10 grid
    std::set<std::string> structures; // kingdom names with structures built
    void buildStructure(const std::string& name, std::string strut);
    bool hasStructure(const std::string& name) const;

    void placeKingdom(const std::string& name, int x, int y);
    void moveKingdom(const std::string& name, const std::string& direction);
    void displayMap() const;
    Position getPosition(const std::string& name) const;
};

#endif


