#pragma once
#include <array>
#include <string>
#include <vector>

class Tile {
    std::string pieceName; // 
    std::pair<int, int> position; // check if really necessary
    char playerPiece; // 0 if empty; 1 for white, 2 for black

public:
    Tile() : pieceName(""), position({-1, -1}), playerPiece(0) {}
    Tile(int row, int column);
    Tile(std::string piece, int row, int column, char player);
    void MovePiece(Tile& destination);
    std::pair<int, int> GetPosition();
    std::string GetPiece();
    char GetPlayer();
    void SetPosition(int row, int column);
    void SetPlayer(char player);
    void SetPiece(std::string piece);
};