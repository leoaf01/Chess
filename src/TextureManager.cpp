#include "helper/TextureManager.h"
#include <iostream>

std::unordered_map<std::string, sf::Texture> TextureManager::textures;

void TextureManager::LoadTexture(std::string fileName) {
    std::string path = "images/";
    path += fileName + ".png";
    if (!textures[fileName].loadFromFile(path)) {
    std::cout << "Error: Failed to load texture: " << path << std::endl;
    }
}

sf::Texture& TextureManager::GetTexture(std::string textureName){
    // if the texture DOESN'T exist
    if (textures.find(textureName) == textures.end()) {
        LoadTexture(textureName); // load it
    }
    return textures[textureName];
}

void TextureManager::Clear() {
    textures.clear();
}