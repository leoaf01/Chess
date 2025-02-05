#include "helper/Tile.h"

Tile::Tile(int row, int column) {
    pieceName = "";
    position = {row, column};
    playerPiece = 0;
}

Tile::Tile(std::string piece, int row, int column, char player) {
    pieceName = piece;
    position = {row, column};
    playerPiece = player;
}

std::pair<int, int> Tile::GetPosition(){
    return position;
}

std::string Tile::GetPiece(){
    return pieceName;
}

char Tile::GetPlayer(){
    return playerPiece;
}

void Tile::SetPosition(int row, int column) {
    position = {row, column};
}