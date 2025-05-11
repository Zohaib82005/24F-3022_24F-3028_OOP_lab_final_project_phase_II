#include "strongHold.h"

void DiplomacySystem::formAlliance(const std::string& k1, const std::string& k2) {
    alliances[k1].insert(k2);
    alliances[k2].insert(k1);

    std::string log = k1 + " formed an alliance with " + k2;
    history.push_back(log);
    std::cout << log << "\n";
}

void DiplomacySystem::breakAlliance(const std::string& k1, const std::string& k2) {
    alliances[k1].erase(k2);
    alliances[k2].erase(k1);

    std::string log = k1 + " broke alliance with " + k2;
    history.push_back(log);
    std::cout << log << "\n";
}

bool DiplomacySystem::isAllied(const std::string& k1, const std::string& k2) const {
    auto it = alliances.find(k1);
    if (it != alliances.end()) {
        return it->second.count(k2) > 0;
    }
    return false;
}

void DiplomacySystem::viewAlliances() const {
    std::cout << "\n--- Current Alliances ---\n";
    for (const auto& pair : alliances) {
        std::cout << pair.first << " is allied with: ";
        for (const auto& ally : pair.second) {
            std::cout << ally << " ";
        }
        std::cout << "\n";
    }
}

void DiplomacySystem::viewHistory() const {
    std::cout << "\n--- Alliance History ---\n";
    for (const auto& record : history) {
        std::cout << record << "\n";
    }
}

void DiplomacySystem::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& pair : alliances) {
            for (const auto& ally : pair.second) {
                if (pair.first < ally) { // Save only one direction
                    file << pair.first << "|" << ally << "\n";
                }
            }
        }
        file.close();
        std::cout << "Alliances saved to " << filename << "\n";
    }
}

void DiplomacySystem::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        alliances.clear();
        std::string line;
        while (getline(file, line)) {
            size_t sep = line.find("|");
            if (sep != std::string::npos) {
                std::string k1 = line.substr(0, sep);
                std::string k2 = line.substr(sep + 1);
                formAlliance(k1, k2);
            }
        }
        file.close();
        std::cout << "Alliances loaded from " << filename << "\n";
    }
}