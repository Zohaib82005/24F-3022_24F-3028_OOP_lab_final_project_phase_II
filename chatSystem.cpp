#include "strongHold.h"

void ChatSystem::sendMessage(const std::string& sender, const std::string& receiver, const std::string& content) {
    Message msg = { sender, receiver, content };
    chatLog.push_back(msg);
    std::cout << "Message sent from " << sender << " to " << receiver << ": " << content << "\n";
}

void ChatSystem::displayChat() const {
    std::cout << "\n--- Chat Log ---\n";
    for (const auto& msg : chatLog) {
        std::cout << "[" << msg.sender << " -> " << msg.receiver << "] " << msg.content << "\n";
    }
}

void ChatSystem::saveChatToFile(const std::string& filename) const {
    std::ofstream outFile(filename);
    if (outFile.is_open()) {
        for (const auto& msg : chatLog) {
            outFile << msg.sender << "|" << msg.receiver << "|" << msg.content << "\n";
        }
        outFile.close();
        std::cout << "Chat log saved to " << filename << "\n";
    }
}

void ChatSystem::loadChatFromFile(const std::string& filename) {
    std::ifstream inFile(filename);
    if (inFile.is_open()) {
        chatLog.clear();
        std::string line;
        while (getline(inFile, line)) {
            size_t pos1 = line.find("|");
            size_t pos2 = line.find("|", pos1 + 1);
            if (pos1 != std::string::npos && pos2 != std::string::npos) {
                Message msg;
                msg.sender = line.substr(0, pos1);
                msg.receiver = line.substr(pos1 + 1, pos2 - pos1 - 1);
                msg.content = line.substr(pos2 + 1);
                chatLog.push_back(msg);
            }
        }
        inFile.close();
        std::cout << "Chat log loaded from " << filename << "\n";
    }
}

