#pragma once
#include <vector>
#include <iomanip>
#include <iostream>
#include "Move.h"
#include "Tile.h"

class Board {
    Tile board[8][8];
    std::vector<Tile*> pieces[2]; // idea for accessing all pieces of one player
    
public:
    Board();
    //void InitializeBoard(); // maybe not needed since constructor can initialize
    void PieceMoves(std::vector<Move>& moves, Tile* aTile, bool turn);
    std::vector<Move> PossibleMoves(bool turn);
    void PrintBoard(); // on terminal
    void MovePiece(std::string start, std::string end);
    //std::set<std::string> ThreatenedTiles(bool turn);
};

std::string CtoP(int row, int column);
std::pair<int, int> PtoC(std::string pos);
char ColToLetter(int col);

