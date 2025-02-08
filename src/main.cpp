#include <SFML/Graphics.hpp>
#include "helper/TextureManager.h" // uses 2.5.1 logic, some stuff has changed
#include "helper/Tile.h"
#include <iostream>
#include <vector>

Tile board[8][8];

std::string CoordinatesToPosition(int row, int column){
     return std::string(1, column + 'a') + std::string(1, row + '1');
}

std::pair<int, int> PositionToCoordinates(std::string position){
    return std::pair<int, int> (position[1] - '1', position[0] - 'a');
}

std::vector<std::string> LegalMoves(std::string position, bool turn) {
    // must check each piece legal moves
    std::vector<std::string> moves;
    std::pair<int, int> c = PositionToCoordinates(position);
    Tile& aTile = board[c.first][c.second];

    if (aTile.GetPlayer() == (!turn)){
        std::cout << "It is not this player's turn!" << std::endl;
        return moves;
    }

    if(aTile.GetPiece() == "P") {
        int forward = aTile.GetPlayer()? -1 : 1;
        if(board[c.first + 1*forward][c.second + 1].GetPlayer() == (!turn) && c.second + 1 < 8)
            moves.push_back(CoordinatesToPosition(c.first + 1*forward, c.second + 1));
        if(board[c.first + 1*forward][c.second - 1].GetPlayer() == (!turn) && c.second - 1 > 0)
            moves.push_back(CoordinatesToPosition(c.first + 1*forward, c.second - 1));    
        if(board[c.first + 1*forward][c.second].GetPlayer() == turn)
            return moves; 
        moves.push_back(CoordinatesToPosition(c.first + 1*forward, c.second));
        if(c.first == 1 || c.second == 6)
            moves.push_back(CoordinatesToPosition(c.first + 2*forward, c.second));
    }
    if(aTile.GetPiece() == "R") {

    }
    if(aTile.GetPiece() == "N") {

    }
    if(aTile.GetPiece() == "B") {

    }
    if(aTile.GetPiece() == "Q") {

    }
    if(aTile.GetPiece() == "K") {

    }
    
    return moves;
}

void InitializeBoard() {
    // sets all the pieces to their specific positions
    std::cout << "Initializing Board" << std::endl;
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
    

    std::cout << "Board was initialized" << std::endl;
}

void PrintBoard(){
    std::cout << "Printing board" << std::endl;
    for(int i = 7; i >= 0; i--){
        for(int j = 0; j < 7; j++)
            std::cout << "[" << std::setw(1) << board[i][j].GetPiece() << "] ";
        std::cout << "" << std::endl;
        std::cout << "\n";
    }
}


void MovePiece(std::string start, std::string end){
    // for this function to happen, the move MUST be legal (checks before calling the function)
    std::pair<int, int> a = PositionToCoordinates(start);
    std::pair<int, int> b = PositionToCoordinates(end);

    // pass all the information from a to b
    board[a.first][a.second].MovePiece(board[b.first][b.second]);
}

void CheckTile() {
    std::string tilePosition;
    std::cin >> tilePosition;
    int column = tilePosition[0] - 'a';
    int row = tilePosition[1] - '1';
    std::cout << "There is a " << board[row][column].GetPiece() << " in " << tilePosition << std::endl;
}



int main()
{
    // used for logic, prints almost everything in terminal
    InitializeBoard();
    PrintBoard();
    std::string a;
    std::cin >> a;

    std::vector<std::string> moves = LegalMoves(a, 0);
    for(int i = 0; i < moves.size(); i++)
        std::cout << moves.at(i) << " \n";

    // used for display, not being used at the moment
    /*
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
    */
    return 0;
}
