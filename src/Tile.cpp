#include "helper/Tile.h"

Tile::Tile(std::string piece, char player) {
    pieceName = piece;
    playerPiece = player;
}

void Tile::MovePiece(Tile& destination) {
    destination.SetPiece(pieceName);
    destination.SetPlayer(playerPiece);
    // erase all values
    pieceName = "";
    playerPiece = 0;
}

std::string Tile::GetPiece(){
    return pieceName;
}

char Tile::GetPlayer(){
    return playerPiece;
}


void Tile::SetPlayer(char player) {
    playerPiece = player;
}

void Tile::SetPiece(std::string piece) {
    pieceName = piece;
}