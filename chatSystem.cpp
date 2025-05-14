#include "strongHold.h"

void ChatSystem::sendMessage(const  string& sender, const  string& receiver, const  string& content) {
    Message msg = { sender, receiver, content };
    chatLog.push_back(msg);
     cout << "Message sent from " << sender << " to " << receiver << ": " << content << "\n";
}

void ChatSystem::displayChat() const {
     cout << "\n--- Chat Log ---\n";
    for (const auto& msg : chatLog) {
         cout << "[" << msg.sender << " -> " << msg.receiver << "] " << msg.content << "\n";
    }
}

void ChatSystem::saveChatToFile(const  string& filename) const {
     ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& msg : chatLog) {
            outFile << msg.sender << "|" << msg.receiver << "|" << msg.content << "\n";
        }
        outFile.close();
         cout << "Chat log saved to " << filename << "\n";
    }
}

void ChatSystem::loadChatFromFile(const  string& filename) {
     ifstream inFile(filename);
    if (inFile.is_open()) {
        chatLog.clear();
         string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1 + 1);
            if (pos1 !=  string::npos && pos2 !=  string::npos) {
                Message msg;
                msg.sender = line.substr(0, pos1);
                msg.receiver = line.substr(pos1 + 1, pos2 - pos1 - 1);
                msg.content = line.substr(pos2 + 1);
                chatLog.push_back(msg);
            }
        }
        inFile.close();
         cout << "Chat log loaded from " << filename << "\n";
    }
}

