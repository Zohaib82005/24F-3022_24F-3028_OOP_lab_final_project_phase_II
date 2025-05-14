#include "strongHold.h"

void DiplomacySystem::formAlliance(const  string& k1, const  string& k2) {
    alliances[k1].insert(k2);
    alliances[k2].insert(k1);

     string log = k1 + " formed an alliance with " + k2;
    history.push_back(log);
     cout << log << "\n";
}

void DiplomacySystem::breakAlliance(const  string& k1, const  string& k2) {
    alliances[k1].erase(k2);
    alliances[k2].erase(k1);

     string log = k1 + " broke alliance with " + k2;
    history.push_back(log);
     cout << log << "\n";
}

bool DiplomacySystem::isAllied(const  string& k1, const  string& k2) const {
    auto it = alliances.find(k1);
    if (it != alliances.end()) {
        return it->second.count(k2) > 0;
    }
    return false;
}

void DiplomacySystem::viewAlliances() const {
     cout << "\n--- Current Alliances ---\n";
    for (const auto& pair : alliances) {
         cout << pair.first << " is allied with: ";
        for (const auto& ally : pair.second) {
             cout << ally << " ";
        }
         cout << "\n";
    }
}

void DiplomacySystem::viewHistory() const {
     cout << "\n--- Alliance History ---\n";
    for (const auto& record : history) {
         cout << record << "\n";
    }
}

void DiplomacySystem::saveToFile(const  string& filename) const {
     ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : alliances) {
            for (const auto& ally : pair.second) {
                if (pair.first < ally) { // Save only one direction
                    file << pair.first << "|" << ally << "\n";
                }
            }
        }
        file.close();
         cout << "Alliances saved to " << filename << "\n";
    }
}

void DiplomacySystem::loadFromFile(const  string& filename) {
     ifstream file(filename);
    if (file.is_open()) {
        alliances.clear();
         string line;
        while (getline(file, line)) {
            size_t sep = line.find("|");
            if (sep !=  string::npos) {
                 string k1 = line.substr(0, sep);
                 string k2 = line.substr(sep + 1);
                formAlliance(k1, k2);
            }
        }
        file.close();
         cout << "Alliances loaded from " << filename << "\n";
    }
}