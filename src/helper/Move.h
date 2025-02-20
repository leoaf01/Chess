#pragma once
#include "Tile.h"

struct Move {
    Tile* fromTile;
    Tile* toTile;
    std::string notation;

    Move();
    Move(std::string n, Tile* from, Tile* to);
};