#pragma once
#include <SFML/Graphics.hpp>
#include <unordered_map>
#include <string>

class TextureManager {
    static std::unordered_map<std::string, sf::Texture> textures;
    static void LoadTexture(std::string textureName);
public:
    static sf::Texture& GetTexture(std::string textureName);
    static void Clear(); // destructor at the end of main()
};