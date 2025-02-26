#pragma once
#include <vector>
#include <unordered_map>
#include <iostream>
#include "Move.h"
#include "Tile.h"

class Board {
    Tile board[8][8];
    std::vector<Tile*> pieces[2];
    std::vector<Move> log;
public:
    Board();
    Board(std::vector<Tile*> copyPieces[2]);

    // moving piece functions
    void PieceMoves(std::unordered_map<std::string, std::vector<Move>>& moves, Tile* aTile, bool turn);
    std::unordered_map<std::string, std::vector<Move>> PossibleMoves(bool turn);
    void MovePiece(std::string start, std::string end);
    void MovePiece(Move m, bool);
    std::unordered_map<std::string, std::vector<Move>> LegalMoves(bool turn);
    
    // check game status functions
    bool Check(bool turn);
    bool Checkmate(bool turn);
    bool Stalemate(bool turn);
    
    void PrintBoard(); // on terminal
};


// coordinates <> position functions
std::string CtoP(int row, int column);
std::pair<int, int> PtoC(std::string pos);
char ColToLetter(int col);

