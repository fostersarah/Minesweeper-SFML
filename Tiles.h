//
// Created by Sarah Foster on 4/7/21.
//

#ifndef MINESWEEPER1_TILES_H
#define MINESWEEPER1_TILES_H
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <vector>
using namespace std;
class Tiles {
    //need a unclicked sprite
    //need a clicked sprite
public:
    sf::Sprite tile_hidden;
    sf::Sprite tile_revealed;
    sf::Sprite flag;
    sf::Sprite mine;
    sf::Sprite boardNum;
    bool isFlagged;
    bool isHidden;
    bool isMine;
    bool countAssigned;
    bool recursiveReveal;
    float xpos;
    float ypos;
    //sf::Vector2i position;
    vector<Tiles*> neighbors;
    int localMineCount;
    Tiles();
    void RevealTile();
    void SetPosition(float x, float y);
    sf::Sprite SpriteLocation();
    void FlagTile();
    void UnflagTile();
    void Draw(sf::RenderWindow& window);
    void DrawDebug(sf::RenderWindow& window);
    void DrawGameOver(sf::RenderWindow &window);
    void DrawGameWon(sf::RenderWindow &window);
    void SetMineNumber();
    void RevealAdjacentTiles();
    //find a way to store what the surroundings are

};
#endif //MINESWEEPER1_TILES_H
