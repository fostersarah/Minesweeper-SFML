//
// Created by Sarah Foster on 4/7/21.
//

#ifndef MINESWEEPER1_BOARD_H
#define MINESWEEPER1_BOARD_H
#include <string>
#include <iostream>
#include <fstream>
#include "Tiles.h"
#include <SFML/Graphics.hpp>
#include "TextureManager.h"
#include <map>

using namespace std;

class Board {
public:
    sf::Sprite face_happy;
    sf::Sprite face_win;
    sf::Sprite face_lose;
    sf::Sprite digits1;
    sf::Sprite digits2;
    sf::Sprite digits3;
    sf::Sprite digitsExtra;
    sf::Sprite debug;
    sf::Sprite test_1;
    sf::Sprite test_2;
    sf::Sprite test_3;

    int numTilesWidth;
    int numTilesHeight;
    int width;
    int height;
    int mineCount;
    int tileCount;
    bool debugEnabled;
    bool gameOver;
    bool gameWon;
    int currentMineCount;
    int numFlags;
    int correctFlags;
    vector<int> mines;
    vector<Tiles> gameBoard;
    map<vector<float>, Tiles> gameBoardPlacement;
    Board(int width, int height, int mineCount, string fileName);
    Board(int width, int height, int mineCount, vector<int>& mines);
    void CreateBoard();
    void IsAMine(string fileName);
    void SetTextures();
    void DebugEnable();
    void DebugDisable();
    void DrawCounter(sf::RenderWindow &window);
    void DrawButtons(sf::RenderWindow &window);
    void GameOver(sf::RenderWindow &window);
    bool CheckGameWin();
    void FindNeighboringTiles();
};

#endif //MINESWEEPER1_BOARD_H
