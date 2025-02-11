#pragma once
#include <string>
#include <set>
#include <vector>
#include "Tile.h"

class Board {
    Tile board[8][8];
    std::vector<Tile*> whitePieces; // idea for accessing all pieces of one player
    std::vector<Tile*> blackPieces;
public:
    Board();
    void InitializeBoard(); // maybe not needed since constructor can initialize
    std::vector<std::string> Moves(std::string pos, bool turn);
    void PrintBoard(); // on terminal
    void MovePiece(std::string start, std::string end);
    std::set<std::string> ThreatenedTiles(bool turn);
};