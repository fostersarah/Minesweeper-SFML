//
// Created by Sarah Foster on 4/7/21.
//

#ifndef MINESWEEPER1_TEXTUREMANAGER_H
#define MINESWEEPER1_TEXTUREMANAGER_H
#include <unordered_map>
#include <string>
#include <SFML/Graphics.hpp>
using std::unordered_map;
using std::string;

class TextureManager {

    static unordered_map<string, sf::Texture> textures;
    static void LoadTexture(string fileName);
public:
    static sf::Texture& GetTexture(string textureName);
    static void Clear(); // call this once at the end of main

};

#endif //MINESWEEPER1_TEXTUREMANAGER_H
