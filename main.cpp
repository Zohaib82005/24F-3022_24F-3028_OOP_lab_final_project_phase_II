#include "strongHold.h"
#include <iostream>
#include <vector>
#include <string>

void displayMainMenu() {
    std::cout << "\n=== Stronghold Multiplayer Menu ===\n";
    std::cout << "1. View Kingdom Status\n";
    std::cout << "2. Update All Systems\n";
    std::cout << "3. Save Game\n";
    std::cout << "4. Load Game\n";
    std::cout << "5. Send Message\n";
    std::cout << "6. View Chat Log\n";
    std::cout << "7. Save Chat\n";
    std::cout << "8. Load Chat\n";

    std::cout << "9. Form Alliance\n";
    std::cout << "10. Break Alliance\n";
    std::cout << "11. View Alliances\n";
    std::cout << "12. View Alliance History\n";
    std::cout << "13. Save Diplomacy\n";
    std::cout << "14. Load Diplomacy\n";


    std::cout << "15. Trade Resources\n";
    std::cout << "16. Smuggle Resources\n";
    std::cout << "17. View Trade History\n";
    std::cout << "18. Save Trade Log\n";
    std::cout << "19. Load Trade Log\n";


    std::cout << "20. Declare War\n";
    std::cout << "21. View Conflict History\n";
    std::cout << "22. Save Conflict Log\n";
    std::cout << "23. Load Conflict Log\n";
    std::cout << "24. View Map\n";
    std::cout << "25. Move Kingdom\n";

    std::cout << "26. Take Action This Season (per kingdom)\n";

    std::cout << "27. Exit\n";
    std::cout << "Enter choice: ";
}
int main() {
    MapSystem map;
    ConflictSystem conflict;
    ChatSystem chat;
    DiplomacySystem diplomacy;
    TradeSystem tradeSys;
    std::vector<Kingdom> kingdoms;
    int numPlayers;

    std::cout << "Enter number of kingdoms (players): ";
    std::cin >> numPlayers;
    std::cin.ignore(); // Clear newline

    for (int i = 0; i < numPlayers; ++i) {
        std::string name;
        std::cout << "Enter name for Kingdom " << (i + 1) << ": ";
        std::getline(std::cin, name);
        kingdoms.emplace_back(name);

        int x = rand() % 10;
        int y = rand() % 10;
        map.placeKingdom(name, x, y);  // Place each kingdom on the map
    }

    bool running = true;
    while (running) {
        displayMainMenu();
        int choice;
        std::cin >> choice;

        switch (choice) {
        case 1: // View Status
            for (const auto& k : kingdoms)
                k.displayStatus();
            break;

        case 2: // Update Systems
            for (auto& k : kingdoms)
                k.updateAllSystems();
            break;

        case 3: // Save
            for (auto& k : kingdoms)
                k.saveState();
            std::cout << "All kingdom states saved.\n";
            break;

        case 4: // Load
            for (auto& k : kingdoms)
                k.loadState();
            std::cout << "All kingdom states loaded.\n";
            break;
        case 5: { // Send Message
            std::string sender, receiver, content;
            std::cin.ignore();
            std::cout << "Enter sender kingdom: ";
            std::getline(std::cin, sender);
            std::cout << "Enter receiver kingdom: ";
            std::getline(std::cin, receiver);
            std::cout << "Enter message: ";
            std::getline(std::cin, content);
            chat.sendMessage(sender, receiver, content);
            break;
        }

        case 6:
            chat.displayChat();
            break;

        case 7:
            chat.saveChatToFile("chat_log.txt");
            break;

        case 8:
            chat.loadChatFromFile("chat_log.txt");
            break;
        case 9: {
            std::string a, b;
            std::cin.ignore();
            std::cout << "Enter first kingdom: "; std::getline(std::cin, a);
            std::cout << "Enter second kingdom: "; std::getline(std::cin, b);
            diplomacy.formAlliance(a, b);
            break;
        }
        case 10: {
            std::string a, b;
            std::cin.ignore();
            std::cout << "Enter first kingdom: "; std::getline(std::cin, a);
            std::cout << "Enter second kingdom: "; std::getline(std::cin, b);
            diplomacy.breakAlliance(a, b);
            break;
        }
        case 11:
            diplomacy.viewAlliances();
            break;
        case 12:
            diplomacy.viewHistory();
            break;
        case 13:
            diplomacy.saveToFile("diplomacy.txt");
            break;
        case 14:
            diplomacy.loadFromFile("diplomacy.txt");
            break;
        case 15: {
            std::string from, to, res;
            int amt;
            std::cin.ignore();
            std::cout << "Sender kingdom: "; getline(std::cin, from);
            std::cout << "Receiver kingdom: "; getline(std::cin, to);
            std::cout << "Resource (Food/Wood/Stone/Iron): "; getline(std::cin, res);
            std::cout << "Amount: "; std::cin >> amt;
            tradeSys.performTrade(from, to, res, amt);
            break;
        }
        case 16: {
            std::string from, to, res;
            int amt;
            std::cin.ignore();
            std::cout << "Sender kingdom: "; getline(std::cin, from);
            std::cout << "Receiver kingdom: "; getline(std::cin, to);
            std::cout << "Resource (Food/Wood/Stone/Iron): "; getline(std::cin, res);
            std::cout << "Amount: "; std::cin >> amt;
            tradeSys.performSmuggling(from, to, res, amt);
            break;
        }
        case 17:
            tradeSys.viewHistory();
            break;
        case 18:
            tradeSys.saveToFile("trade_log.txt");
            break;
        case 19:
            tradeSys.loadFromFile("trade_log.txt");
            break;
        case 20: {
            std::string atk, def;
            std::cin.ignore();
            std::cout << "Attacker kingdom: "; getline(std::cin, atk);
            std::cout << "Defender kingdom: "; getline(std::cin, def);

            Kingdom* attackerPtr = nullptr;
            Kingdom* defenderPtr = nullptr;

            for (auto& k : kingdoms) {
                if (k.getName() == atk) attackerPtr = &k;
                if (k.getName() == def) defenderPtr = &k;
            }

            if (attackerPtr && defenderPtr) {
                conflict.declareWar(*attackerPtr, *defenderPtr, diplomacy);
            }
            else {
                std::cout << "Invalid kingdom names.\n";
            }
            break;
        }

        case 21:
            conflict.viewConflictHistory();
            break;

        case 22:
            conflict.saveToFile("conflict_log.txt");
            break;

        case 23:
            conflict.loadFromFile("conflict_log.txt");
            break;
        case 24:
            map.displayMap();
            break;

        case 25: {
            std::string name, direction;
            std::cin.ignore();
            std::cout << "Enter kingdom name: "; getline(std::cin, name);
            std::cout << "Enter direction (up/down/left/right): "; getline(std::cin, direction);
            map.moveKingdom(name, direction);
            break;
        }
        case 26: {
            std::string name;
            std::cin.ignore();
            std::cout << "Enter kingdom name: ";
            getline(std::cin, name);

            Kingdom* target = nullptr;
            for (auto& k : kingdoms) {
                if (k.getName() == name) {
                    target = &k;
                    break;
                }
            }

            if (!target) {
                std::cout << "Kingdom not found.\n";
                break;
            }

            int action;
            std::cout << "\nWhat would you like to do this season?\n";
            std::cout << "1. Collect taxes\n";
            std::cout << "2. Recruit soldiers\n";
            std::cout << "3. Train army\n";
            std::cout << "4. Build structure on map \n";
            std::cout << "5. Spend on services \n";
            std::cout << "6. Change policy (placeholder)\n";
            std::cout << "7. Do nothing\n";
            std::cout << "Enter action: ";
            std::cin >> action;

            switch (action) {
            case 1:
                try {
                    target->getEconomy().collectTaxes(rand() % 100 + 50); // simulate pop
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;
            case 2:
                try {
                    target->getMilitary().recruitSoldiers(rand() % 50 + 10);
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;
            case 3:
                target->getMilitary().trainArmy();
                break;
            case 4: {
                std::string structure;
                std::cin.ignore();
                std::cout << "Enter structure to build (Fort / Farm): ";
                getline(std::cin, structure);

                // Build at the kingdom’s current map location
                map.buildStructure(target->getName(), structure);

                // Optional effects
                if (structure == "Fort") {
                    target->getMilitary().trainArmy();  // Fort gives morale/training
                }
                else if (structure == "Farm") {
                    target->getResources().gatherResources();  // Farm improves resources
                }
                break;
            }

            case 5:
                try {
                    target->getEconomy().adjustTaxRate(0.2f); // simulate stability policy
                    target->getMilitary().trainArmy(); // improve morale slightly
                    std::cout << name << " spent on public services. Morale and satisfaction improved.\n";
                }
                catch (const std::exception& e) {
                    std::cerr << "Error: " << e.what() << "\n";
                }
                break;

            case 6:
                std::cout << "This feature is not implemented yet.\n";
                break;
            case 7:
                std::cout << "No action taken.\n";
                break;
            default:
                std::cout << "Invalid seasonal action.\n";
                break;
            }
            break;
        }
        case 27:
            running = false;
            break;
        default:
            std::cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
}