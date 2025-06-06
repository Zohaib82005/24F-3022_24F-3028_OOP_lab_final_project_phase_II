
#include "strongHold.h"

void TradeSystem::performTrade(const  string& sender, const  string& receiver, const  string& resource, int amount) {
    TradeRecord rec = { sender, receiver, "Trade", resource, amount, true };
    history.push_back(rec);
     cout << "Trade completed: " << sender << " sent " << amount << " " << resource << " to " << receiver << "\n";
}

void TradeSystem::performSmuggling(const  string& sender, const  string& receiver, const  string& resource, int amount) {
    bool caught = (rand() % 100 < 30); // 30% chance of getting caught

    TradeRecord rec = { sender, receiver, "Smuggle", resource, amount, !caught };
    history.push_back(rec);

    if (caught) {
         cout << "Smuggling failed! " << sender << " was caught trying to send " << amount << " " << resource << " to " << receiver << "\n";
    }
    else {
         cout << "Smuggling successful: " << sender << " smuggled " << amount << " " << resource << " to " << receiver << "\n";
    }
}

void TradeSystem::viewHistory() const {
     cout << "\n--- Trade & Smuggling History ---\n";
    for (const auto& rec : history) {
         cout << rec.type << ": " << rec.sender << " -> " << rec.receiver
            << ", " << rec.amount << " " << rec.resource
            << " (" << (rec.success ? "Success" : "Failed") << ")\n";
    }
}

void TradeSystem::saveToFile(const  string& filename) const {
     ofstream file(filename);
    if (file.is_open()) {
        for (const auto& rec : history) {
            file << rec.sender << "|" << rec.receiver << "|" << rec.type << "|"
                << rec.resource << "|" << rec.amount << "|" << rec.success << "\n";
        }
        file.close();
         cout << "Trade history saved to " << filename << "\n";
    }
}

void TradeSystem::loadFromFile(const  string& filename) {
     ifstream file(filename);
    if (file.is_open()) {
        history.clear();
         string line;
        while (getline(file, line)) {
            TradeRecord rec;
            size_t p1 = line.find("|");
            size_t p2 = line.find("|", p1 + 1);
            size_t p3 = line.find("|", p2 + 1);
            size_t p4 = line.find("|", p3 + 1);
            size_t p5 = line.find("|", p4 + 1);

            rec.sender = line.substr(0, p1);
            rec.receiver = line.substr(p1 + 1, p2 - p1 - 1);
            rec.type = line.substr(p2 + 1, p3 - p2 - 1);
            rec.resource = line.substr(p3 + 1, p4 - p3 - 1);
            rec.amount =  stoi(line.substr(p4 + 1, p5 - p4 - 1));
            rec.success = (line.substr(p5 + 1) == "1");

            history.push_back(rec);
        }
        file.close();
         cout << "Trade history loaded from " << filename << "\n";
    }
}