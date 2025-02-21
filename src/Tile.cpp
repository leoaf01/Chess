#include "helper/Tile.h"

Tile::Tile(int r, int c){
    pieceName = "";
    playerPiece = -1;
    row = r;
    col = c;
}

Tile::Tile(std::string piece, char player, int r, int c) {
    pieceName = piece;
    playerPiece = player;
    row = r;
    col = c;
}

void Tile::MovePiece(Tile* destination) {
    destination->SetPiece(pieceName);
    destination->SetPlayer(playerPiece);
    // erase all values
    pieceName = "";
    playerPiece = -1;
}

std::string Tile::GetPiece(){
   return pieceName;
}

char Tile::GetPlayer(){
    return playerPiece;
}

int Tile::GetRow(){
    return row;
}

int Tile::GetCol(){
    return col;
}

void Tile::SetPlayer(char player) {
    playerPiece = player;
}

void Tile::SetPiece(std::string piece) {
    pieceName = piece;
}