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
    board.PrintBoard();
    std::vector<Move> moves = board.PossibleMoves(1);
    std::cout << "Moves saved\n"; 
    for(int i = 0; i < moves.size(); i++)
        std::cout << moves.at(i).notation << std::endl;

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
