#include <SFML/Graphics.hpp>
#include "helper/TextureManager.h" // uses 2.5.1 logic, some stuff has changed
#include "helper/Board.h"
#include <iostream>
#include <vector>


int main()
{
    // used for logic, prints in terminal
    Board board;
    std::cout << "Board Initialized\n";

    bool turn = 0;
    int count = 1;
    while(board.LegalMoves(turn).size() > 0){
        board.PrintBoard();
        std::cout << "Choose your move, player " << turn + 1 << ".\n";
        std::vector<Move> moves = board.LegalMoves(turn);
        // std::vector<Move> possibles = board.PossibleMoves(turn);
        for(int i = 0; i < moves.size(); i++)
            std::cout << i << ". " << moves.at(i).notation << std::endl;
            int input;
            std::cin >> input;
            if(input > moves.size() || input < 0){
                std::cout << "Please choose one of the following moves.\n";
                continue;
            }
            board.MovePiece(moves.at(input), turn);
            count++;
            turn = !turn;
    }

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
