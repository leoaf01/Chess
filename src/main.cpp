#include <SFML/Graphics.hpp>
#include "helper/TextureManager.h" // uses 2.5.1 logic, some stuff has changed
#include "helper/Board.h"
#include <iostream>
#include <vector>
#include <format>


int main()
{
    // used for logic, prints in terminal
    Board board;
    std::cout << "Board Initialized\n";
    board.PrintBoard();
    bool turn = 0;
    int count = 1;
    bool end_game = false;
    while(board.LegalMoves(turn).size() > 0){
        std::cout << "Choose your move, player " << turn + 1 << ".\n";
        std::unordered_map<std::string, std::vector<Move>> moves = board.LegalMoves(turn);
        
        std::string input = "";
        std::cin >> input;
        if(moves[input].size() == 0){
            std::cout << "Please choose a legal move.\n";
            continue;
        }
        int i = 0;
        if(input == "0-0" || input == "0-0-0"){
            for(auto m : moves[input]){
                board.MovePiece(m, turn);
                std::cout << m.toTile->GetCol() << "\n";
            }
        }
        else if(moves[input].size() > 1){
            std::cout << "Please choose which piece moves to " << input << std::endl;
            for(i = 0; i < moves[input].size(); i++){
                int row = moves[input].at(i).fromTile->GetRow();
                int col = moves[input].at(i).fromTile->GetCol();
                std::string piece = moves[input].at(i).fromTile->GetPiece() + CtoP(row, col);
                
                std::cout << i + 1 << ". " << piece << std::endl;
            }
            int input2;
            std::cin >> input2;
            if(input2 <= 0 || input2 > moves[input].size()){
                "Please choose a legal move.\n";
                continue;
            }
            else    
                i = input2 - 1;
        }
        board.MovePiece(moves[input].at(i), turn);
        std::string suffix = "";
        if(board.Checkmate(turn))
            break;
        else if(board.Check(turn))
            suffix = "+";
        std::cout << "Player " << turn + 1 << " moves " << input + suffix << std::endl;
        count++;
        turn = !turn;
        board.PrintBoard();
    }
    turn != turn;
    std::string endgame_message = "";
    if(board.Checkmate(turn))
        endgame_message = "Player " + std::to_string(turn+1) + " won!"; 
    else 
        endgame_message = "It's a tie!";
    std::cout << std::endl << endgame_message << std::endl;
    board.PrintBoard();

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
