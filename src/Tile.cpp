#include "helper/Tile.h"
#include <unordered_map>

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
