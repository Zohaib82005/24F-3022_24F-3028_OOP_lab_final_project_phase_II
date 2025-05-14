#ifndef STRONGHOLD_H
#define STRONGHOLD_H

#include <iostream>
#include <fstream>
#include <string>
#include<vector>
#include<map>
#include<set>
using namespace std;
//manage whole system
class System {
public:
    virtual void update() = 0; 
    virtual void saveToFile(const  string& filename) = 0; 
    virtual void loadFromFile(const  string& filename) = 0; 
    virtual ~System() {} 
};

// Population class
// This class manages the population of the kingdom
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
     string getStatus() const; 
};
// 
// Military class
// This class manages the military of the kingdom
// It includes army size, morale, and corruption
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
     string getStatus() const; 
};

// Economy class
// This class manages the economy of the kingdom
// It includes treasury, tax rate, and inflation
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
     string getStatus() const; 
};
// Leadership class
// This class manages the leadership of the kingdom
class Leadership : public System {
private:
     string leaderName;
     string leadershipStyle;
    bool isCoupAttempted;

public:
    Leadership();
    void electLeader(const  string& name, const  string& style);
    void handleCoup();
    void update() override;
    void saveToFile(const  string& filename) override;
    void loadFromFile(const  string& filename) override;
     string getStatus() const;
};

// Banking class
// This class manages the banking system of the kingdom
// It includes loan amount, interest rate, and fraud detection
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
     string getStatus() const; 
};

// Resources class
// This class manages the resources of the kingdom
// It includes food, wood, stone, and iron
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
     string getStatus() const; 
};

// Events class
// This class manages random events that can occur in the kingdom
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

// Kingdom class
// This class represents a kingdom and manages all systems
// It includes population, military, economy, leadership, banking, resources, and events
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
    
    void saveState();
    void loadState();
};

// 
// ChatSystem class
// This class manages the chat system between kingdoms
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
// 
// DiplomacySystem class
// This class manages alliances and conflicts between kingdoms
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


// TradeSystem class
// This class manages trade and smuggling between kingdoms

struct TradeRecord {
     string sender;
     string receiver;
     string type;  
     string resource;
    int amount;
    bool success;
};


// TradeSystem class
// This class manages trade and smuggling between kingdoms

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

// MapSystem class
// This class manages the map of the kingdom
// It includes the grid, kingdom positions, and structures
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