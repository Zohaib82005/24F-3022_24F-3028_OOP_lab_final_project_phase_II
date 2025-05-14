#include"strongHold.h"
MapSystem::MapSystem(int w, int h) : width(w), height(h) {
    grid = new char* [w];
    for (int i = 0;i < w; i++) {
        grid[i] = new char[h];
    }

    for (int i = 0; i < w; i++) {
        for (int j = 0; j < h; j++) {
            grid[i][j] = '.';
        }
    }
}

void MapSystem::placeKingdom(const  string& name, int x, int y) {

    grid[x][y] = name[0];
}

void MapSystem::moveKingdom(const std::string& name, const std::string& direction) {
    auto it = kingdomPositions.find(name);
    if (it == kingdomPositions.end()) return;

    Position& pos = it->second;

    if (direction == "up" && pos.y > 0) pos.y--;
    else if (direction == "down" && pos.y < height - 1) pos.y++;
    else if (direction == "left" && pos.x > 0) pos.x--;
    else if (direction == "right" && pos.x < width - 1) pos.x++;
    else std::cout << "Invalid move or out of bounds.\n";
    placeKingdom(name, pos.x, pos.y);
}



void MapSystem::displayMap() const {

     cout << "\n--- Kingdom Map ---\n";
    for (int y = 0; y < height; y++) {
        for (int x = 0; x < width; x++) {
             cout << grid[y][x] << " ";
        }
         cout << "\n";
    }
     cout << "\nLegend:\n";
    for (const auto& entry : kingdomPositions) {
         cout << toupper(entry.first[0]) << " = " << entry.first
            << " at (" << entry.second.x << "," << entry.second.y << ")\n";
    }

}

Position MapSystem::getPosition(const  string& name) const {
    auto it = kingdomPositions.find(name);
    if (it != kingdomPositions.end()) return it->second;
    return { -1, -1 }; 
}

void MapSystem::buildStructure(const  string& name,  string structure) {
    grid[rand() % 10][rand() % 10] = structure[0];
}

bool MapSystem::hasStructure(const  string& name) const {
    return structures.count(name) > 0;
}
