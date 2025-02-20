#include "helper/Move.h"

Move::Move() {
    notation = "";
    fromTile = nullptr;
    toTile = nullptr;
}

Move::Move(std::string n, Tile* from, Tile* to){
    notation = n;
    fromTile = from;
    toTile = to;
}