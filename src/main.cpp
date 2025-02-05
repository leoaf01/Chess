#include <SFML/Graphics.hpp>
#include "helper/TextureManager.h" // uses 2.5.1 logic, some stuff has changed
#include "helper/Tile.h"
#include <unordered_map>
#include <iostream>
#include <array>

static std::unordered_map<int, char> columns = {{1,'a'},{2,'b'},{3,'c'},{4,'d'},{5,'e'},{6,'f'},{7,'g'},{8,'h'}};

void InitializeBoard(Tile board[8][8]) {
    // sets all the pieces to their specific positions
    std::cout << "Initializing Board" << std::endl;
    // 1. Initialize the Tiles that are empty (rows 3 to 6)

    for(int i = 2; i < 6; i++){
        for(int j = 0; j < 8; j++){
            board[i][j] = Tile(i, j);
        }
    }

    // 2. Initialize the pawns
    for(int i = 0; i < 8; i++){
        board[1][i] = Tile("pawn", 1, i , 1);
        board[6][i] = Tile("pawn", 6, i, 2);
    }

    // 3. Initialize pieces from the first and last row

    // 3.1 Rooks, Knights and Bishops
    for(int i = 0; i < 3; i++){ // loop for pieces 0=rook, 1=knight, 2=bishop
        for(int j = 0; j < 2; j++){ // loop for players
            int playerRow = j * 7; 
            std::string piece = "rook";
            if(i = 1)
                piece = "knight";
            if(i = 2)
                piece = "bishop";

            board[playerRow][i] = Tile(piece, playerRow, i, j+1);
            board[playerRow][8-i] = Tile(piece, playerRow, 8-i, j+1);
        }
    }

    // 3.2 Kings and Queens

    for(int j = 0; j < 2; j++){
        int playerRow =  j*7;
        board[playerRow][3] = Tile("queen", playerRow, 3, j+1);
        board[playerRow][4] = Tile("king", playerRow, 4, j+1);
    }
    

    std::cout << "Board was initialized" << std::endl;
}

void PrintBoard(Tile board[8][8]){
    std::cout << "Printing board" << std::endl;
    for(int i = 0; i < 8; i++)
        for(int j = 0; j < 8; j++)
            std::cout << board[i][j].GetPosition() << std::endl;
}


int main()
{
    Tile board[8][8];
    InitializeBoard(board);
    PrintBoard(board);
    while(true){
        std::cout << "Continue? Press 1" << std::endl;
        int d;
        std::cin >> d;
        if(d=1)
            break;
    }
    return 0;
}
