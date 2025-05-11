
#include "strongHold.h"
#include <iostream>
#include <fstream>
#include <cstdlib>

void ConflictSystem::declareWar(Kingdom& attacker, Kingdom& defender, DiplomacySystem& diplomacy) {
    bool betrayal = diplomacy.isAllied(attacker.getName(), defender.getName());
    bool attackerWon = (rand() % 100) < 60; // 60% chance attacker wins

    ConflictLog log = { attacker.getName(), defender.getName(), betrayal, attackerWon };
    history.push_back(log);

    if (betrayal) {
        diplomacy.breakAlliance(attacker.getName(), defender.getName());
        std::cout << "⚠  Betrayal! " << attacker.getName() << " attacked their ally " << defender.getName() << "\n";
    }
    else {
        std::cout << attacker.getName() << " has declared war on " << defender.getName() << "\n";
    }

    if (attackerWon) {
        std::cout << attacker.getName() << " wins the battle!\n";
        // Simulate effects
        std::cout << defender.getName() << " loses 20 army and morale.\n";
        std::cout << attacker.getName() << " gains 10 morale.\n";
    }
    else {
        std::cout << defender.getName() << " defends successfully!\n";
        std::cout << attacker.getName() << " loses 15 army and morale.\n";
    }

    // You can later apply these effects directly using setter methods in Military if needed
}

void ConflictSystem::viewConflictHistory() const {
    std::cout << "\n--- Conflict History ---\n";
    for (const auto& log : history) {
        std::cout << log.attacker << " attacked " << log.defender;
        if (log.betrayal) std::cout << " (Betrayal)";
        std::cout << " -> " << (log.attackerWon ? "Attacker Won" : "Defender Won") << "\n";
    }
}

void ConflictSystem::saveToFile(const std::string& filename) const {
    std::ofstream file(filename);
    if (file.is_open()) {
        for (const auto& log : history) {
            file << log.attacker << "|" << log.defender << "|" << log.betrayal << "|" << log.attackerWon << "\n";
        }
        file.close();
        std::cout << "Conflict history saved to " << filename << "\n";
    }
}

void ConflictSystem::loadFromFile(const std::string& filename) {
    std::ifstream file(filename);
    if (file.is_open()) {
        history.clear();
        std::string line;
        while (getline(file, line)) {
            size_t p1 = line.find("|");
            size_t p2 = line.find("|", p1 + 1);
            size_t p3 = line.find("|", p2 + 1);
            size_t p4 = line.find("|", p3 + 1);

            ConflictLog log;
            log.attacker = line.substr(0, p1);
            log.defender = line.substr(p1 + 1, p2 - p1 - 1);
            log.betrayal = (line.substr(p2 + 1, p3 - p2 - 1) == "1");
            log.attackerWon = (line.substr(p3 + 1) == "1");

            history.push_back(log);
        }
        file.close();
        std::cout << "Conflict history loaded from " << filename << "\n";
    }
}