#pragma once
#include <array>
#include <string>
#include <vector>

class Tile {
    std::string pieceName; // 
    char playerPiece; // -1 if empty; 0 for white, 1 for black

public:
    Tile() : pieceName(""), playerPiece(-1) {}
    Tile(std::string piece, char player);
    void MovePiece(Tile& destination);
    std::string GetPiece();
    char GetPlayer();
    void SetPlayer(char player);
    void SetPiece(std::string piece);
};