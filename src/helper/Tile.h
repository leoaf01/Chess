#pragma once
#include <array>
#include <string>
#include <vector>

class Tile {
    std::string pieceName; // 
    std::pair<int, int> position; 
    char playerPiece; // 0 if empty; 1 for white, 2 for black

    void SetPosition(int row, int column);
public:
    Tile();
    Tile(int row, int column);
    Tile(std::string piece, int row, int column, char player);
    std::string GetPosition();
    std::string GetPiece();
    int getPlayer();
};