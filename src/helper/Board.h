#pragma once
#include <string>
#include <set>
#include <vector>
#include <iomanip>
#include <iostream>
#include "Tile.h"

class Board {
    Tile board[8][8];
    std::vector<Tile&> pieces[2]; // idea for accessing all pieces of one player

public:
    Board();
    //void InitializeBoard(); // maybe not needed since constructor can initialize
    void PieceMoves(std::vector<Move>& moves, Tile& aTile, bool turn);
    std::vector<Move> PossibleMoves(bool turn);
    void PrintBoard(); // on terminal
    void MovePiece(std::string start, std::string end);
    //std::set<std::string> ThreatenedTiles(bool turn);
};

std::string CtoP(int row, int column);
std::pair<int, int> PtoC(std::string pos);
char ColToLetter(int col);

struct Move {
    //char movingPiece;
    //char takes = false; // x
    //char check = false; // +
    //char promotion = false; // a8=Q - maybe a string
    //std::string castling = ""; // 0-0 or 0-0-0
    //char checkmate = false;  // #

    Tile& fromTile;
    Tile& toTile;
    std::string notation;

    Move(std::string n, Tile& from, Tile& to)
        : notation(n), fromTile(from), toTile(to) {}
};