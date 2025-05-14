#include "strongHold.h"
#include <iostream>
#include <vector>
#include <string>

void displayMainMenu() {
     cout << "\n=== Stronghold Multiplayer Menu ===\n";
     cout << "1. View Kingdom Status\n";
     cout << "2. Update All Systems\n";
     cout << "3. Save Game\n";
     cout << "4. Load Game\n";
     cout << "5. Send Message\n";
     cout << "6. View Chat Log\n";
     cout << "7. Save Chat\n";
     cout << "8. Load Chat\n";

     cout << "9. Form Alliance\n";
     cout << "10. Break Alliance\n";
     cout << "11. View Alliances\n";
     cout << "12. View Alliance History\n";
     cout << "13. Save Diplomacy\n";
     cout << "14. Load Diplomacy\n";


     cout << "15. Trade Resources\n";
     cout << "16. Smuggle Resources\n";
     cout << "17. View Trade History\n";
     cout << "18. Save Trade Log\n";
     cout << "19. Load Trade Log\n";


     cout << "20. Declare War\n";
     cout << "21. View Conflict History\n";
     cout << "22. Save Conflict Log\n";
     cout << "23. Load Conflict Log\n";
     cout << "24. View Map\n";

     cout << "25. Take Action This Season (per kingdom)\n";
     cout << "26. Trigger a event\n";
     cout << "27. Exit\n";
     cout << "Enter choice: ";
}
int main() {
    MapSystem map;
    ConflictSystem conflict;
    ChatSystem chat;
    DiplomacySystem diplomacy;
    TradeSystem tradeSys;
    Events event;
    bool kfound = false;
     vector<Kingdom> kingdoms;
    int numPlayers;
    string kingEvent;
     cout << "Enter number of kingdoms (players): ";
     cin >> numPlayers;
     cin.ignore(); // Clear newline

    for (int i = 0; i < numPlayers; ++i) {
         string name;
         cout << "Enter name for Kingdom " << (i + 1) << ": ";
         getline( cin, name);
        kingdoms.emplace_back(name);

        int x = rand() % 10;
        int y = rand() % 10;
        map.placeKingdom(name, x, y);  // Place each kingdom on the map
    }

    bool running = true;
    while (running) {
        displayMainMenu();
        int choice;
         cin >> choice;

        switch (choice) {
        case 1: // View Status
            for ( auto &k : kingdoms) {
                k.displayStatus();
            }
            break;

        case 2: // Update Systems
            for (auto& k : kingdoms)
                k.updateAllSystems();
            break;

        case 3: // Save
            for (auto& k : kingdoms)
                k.saveState();
             cout << "All kingdom states saved.\n";
            break;

        case 4: // Load
            for (auto& k : kingdoms)
                k.loadState();
             cout << "All kingdom states loaded.\n";
            break;
        case 5: { 
             string sender, receiver, content;
             cin.ignore();
             cout << "Enter sender kingdom: ";
             getline( cin, sender);
             cout << "Enter receiver kingdom: ";
             getline( cin, receiver);
             cout << "Enter message: ";
             getline( cin, content);
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
             string a, b;
             cin.ignore();
             cout << "Enter first kingdom: ";  getline( cin, a);
             cout << "Enter second kingdom: ";  getline( cin, b);
            diplomacy.formAlliance(a, b);
            break;
        }
        case 10: {
             string a, b;
             cin.ignore();
             cout << "Enter first kingdom: ";  getline( cin, a);
             cout << "Enter second kingdom: ";  getline( cin, b);
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
             string from, to, res;
            int amt;
             cin.ignore();
             cout << "Sender kingdom: "; getline( cin, from);
             cout << "Receiver kingdom: "; getline( cin, to);
             cout << "Resource (Food/Wood/Stone/Iron): "; getline( cin, res);
             cout << "Amount: ";  cin >> amt;
            tradeSys.performTrade(from, to, res, amt);
            break;
        }
        case 16: {
             string from, to, res;
            int amt;
             cin.ignore();
             cout << "Sender kingdom: "; getline( cin, from);
             cout << "Receiver kingdom: "; getline( cin, to);
             cout << "Resource (Food/Wood/Stone/Iron): "; getline( cin, res);
             cout << "Amount: ";  cin >> amt;
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
             string atk, def;
             cin.ignore();
             cout << "Attacker kingdom: "; getline( cin, atk);
             cout << "Defender kingdom: "; getline( cin, def);

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
                 cout << "Invalid kingdom names.\n";
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
             string name;
             cin.ignore();
             cout << "Enter kingdom name: ";
            getline( cin, name);

            Kingdom* target = nullptr;
            for (auto& k : kingdoms) {
                if (k.getName() == name) {
                    target = &k;
                    break;
                }
            }

            if (!target) {
                 cout << "Kingdom not found.\n";
                break;
            }

            int action;
             cout << "\nWhat would you like to do this season?\n";
             cout << "1. Collect taxes\n";
             cout << "2. Recruit soldiers\n";
             cout << "3. Train army\n";
             cout << "4. Build structure on map \n";
             cout << "5. Spend on services \n";
             cout << "6. Change policy (placeholder)\n";
             cout << "7. Do nothing\n";
             cout << "Enter action: ";
             cin >> action;

            switch (action) {
            case 1:
                try {
                    target->getEconomy().collectTaxes(rand() % 100 + 50); // simulate pop
                }
                catch (const  exception& e) {
                     cerr << "Error: " << e.what() << "\n";
                }
                break;
            case 2:
                try {
                    target->getMilitary().recruitSoldiers(rand() % 50 + 10);
                }
                catch (const  exception& e) {
                     cerr << "Error: " << e.what() << "\n";
                }
                break;
            case 3:
                target->getMilitary().trainArmy();
                break;
            case 4: {
                 string structure;
                 cin.ignore();
                 cout << "Enter structure to build (Fort / Farm): ";
                getline( cin, structure);

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
                     cout << name << " spent on public services. Morale and satisfaction improved.\n";
                }
                catch (const  exception& e) {
                     cerr << "Error: " << e.what() << "\n";
                }
                break;

            case 6:
                 cout << "This feature is not implemented yet.\n";
                break;
            case 7:
                 cout << "No action taken.\n";
                break;
            default:
                 cout << "Invalid seasonal action.\n";
                break;
            }
            break;
        }
        case 26:
            
            cout << "Triggering a random Event\n";
            cout << "Enter Kingdom Name: ";
            cin.ignore();
            getline(cin, kingEvent);
            for (auto &k : kingdoms) {
                if (k.getName() == kingEvent) {
                    k.eventTrigger();
                    kfound = true;
                    cout << "Kingdom found and event triggerd";
                    cout << "Event is: " << k.getLastEvent() << endl;
                    break;
                }

            }
            if (!kfound) {
                cout << "No Kingdom Found of name: " << kingEvent << endl;
            break;
        case 27:
            running = false;
            break;
        default:
             cout << "Invalid choice.\n";
            break;
        }
    }

    return 0;
}
