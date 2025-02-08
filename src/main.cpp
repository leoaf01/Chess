#include <SFML/Graphics.hpp>
#include "helper/TextureManager.h" // uses 2.5.1 logic, some stuff has changed
#include "helper/Tile.h"
#include <iostream>
#include <array>

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
            if(i == 1)
                piece = "knight";
            if(i == 2)
                piece = "bishop";

            board[playerRow][i] = Tile(piece, playerRow, i, j+1);
            board[playerRow][7-i] = Tile(piece, playerRow, 7-i, j+1);
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
    for(int i = 7; i >= 0; i--){
        for(int j = 7; j >= 0; j--)
            std::cout << "[" << board[i][j].GetPiece() << "] ";
        std::cout << "" << std::endl;
    }
}

void MovePiece(Tile board[8][8]){

}

void CheckTile(Tile board[8][8]) {
    std::string tilePosition;
    std::cin >> tilePosition;
    int column = tilePosition[0] - 'a';
    int row = tilePosition[1] - '1';
    std::cout << "There is a " << board[row][column].GetPiece() << " in " << tilePosition << std::endl;
}

std::string CoordinatesToPosition(int row, int column){
     return std::string(1, column + 'a') + std::string(1, row + '1');
}

std::pair<int, int> PositionToCoordinates(std::string position){
    return std::pair<int, int> (position[1] - '1', position[0] - 'a');
}


int main()
{
    // used for logic, prints almost everything in   terminal
    Tile board[8][8];
    InitializeBoard(board);
    PrintBoard(board);
    int a, b;
    std::cin >> a >> b;
    std::cout << CoordinatesToPosition(a, b) << std::endl;

    // used for display
    sf::RenderWindow window(sf::VideoMode({591, 591}), "My Chess Game");
    sf::CircleShape shape(100.f);
    shape.setFillColor(sf::Color::Green);

    sf::Texture leo;
    leo.loadFromFile("images/leo.jpg");

    sf::Sprite sprite(leo);
    sprite.setTextureRect(sf::IntRect({1, 1}, {591, 591}));
    sprite.setPosition({0, 0});
    

    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
                window.close();
        }

        window.clear();
        window.draw(sprite);
        window.display();
    }

    TextureManager::Clear();
    return 0;
}
