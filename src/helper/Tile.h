#pragma once
#include <string>

class Tile {
    std::string pieceName; // one letter name, could change to char
    char playerPiece; // -1 if empty; 0 for white, 1 for black
    int row, col;

public:
    Tile() : pieceName(""), playerPiece(-1), row(-1), col(-1) {};
    Tile(int r, int c);
    Tile(std::string piece, char player, int r, int c);
    void MovePiece(Tile* destination);
    std::string GetPiece();
    char GetPlayer();
    int GetRow();
    int GetCol();
    void SetPlayer(char player);
    void SetPiece(std::string piece);
};