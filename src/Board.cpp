#include "Board.h"

Board::Board(){
    // 1. Initialize the Tiles that are empty (rows 3 to 6)
    for(int i = 2; i < 6; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = Tile();
        }
    }

    // 2. Initialize the pawns
    for(int i = 0; i < 8; i++){
        board[1][i] = Tile("P", 0);
        board[6][i] = Tile("P", 1);
    }

    // 3. Initialize pieces from the first and last row
    // 3.1 Rooks, Knights and Bishops
    for(int i = 0; i < 3; i++){ // loop for pieces 0=rook, 1=knight, 2=bishop
        for(int j = 0; j < 2; j++){ // loop for players
            int playerRow = j * 7; 
            std::string piece = "R";
            if(i == 1)
                piece = "N";
            if(i == 2)
                piece = "B";

            board[playerRow][i] = Tile(piece, j);
            board[playerRow][7-i] = Tile(piece, j);
        }
    }

    // 3.2 Kings and Queens

    for(int j = 0; j < 2; j++){
        int playerRow =  j*7;
        board[playerRow][3] = Tile("Q", j);
        board[playerRow][4] = Tile("K", j);
    }
}

