#include <SFML/Graphics.hpp>
#include <string>
#include <iostream>
#include <fstream>
#include "Board.h"
#include "Tiles.h"
#include "TextureManager.h"
#include "Random.h"
#include <map>
#include <random>


Board ReadTestBoardFile(string fileName) {
    ifstream InputFile;
    InputFile.open(fileName);
    string line;
    int width = 0;
    int height = 0;
    int mineCount = 0;
    string s_width;
    string s_height;
    string s_mineCount;

    if (InputFile.is_open()) {
        while (getline(InputFile, line)) {
            width = line.size();
            height++;
            mineCount = mineCount + count(line.begin(), line.end(), '1');
        }
    }

    Board board(width, height, mineCount, fileName);
    return board;
}

Board CreateRandomBoard(string fileName) {
    ifstream InputFile;
    InputFile.open(fileName);
    int width = 0;
    int height = 0;
    int mineCount = 0;
    string s_width;
    string s_height;
    string s_mineCount;
    if (InputFile.is_open()) {
        getline(InputFile, s_width);
        getline(InputFile, s_height);
        getline(InputFile, s_mineCount);
        width = stoi(s_width);
        height = stoi(s_height);
        mineCount = stoi(s_mineCount);
    }
    vector <int> mines;
    vector<int> mineIndex;
    for (int i = 0; i < (width * height); i++) {
        mines.push_back(0);
    }
    int mineCounter = 0;

    while (mineCounter < mineCount) {
        //int randomIndex = random() % (width * height);
        int randomIndex = Random::Int(0, width * height);
        auto it = find(mineIndex.begin(), mineIndex.end(), randomIndex);
        if (it == mineIndex.end()) {
            mineIndex.push_back(randomIndex);
            mines[randomIndex] = 1;
            mineCounter++;
        }

    }

    Board board(width, height, mineCount, mines);
    return board;

}


int main()
{
    Board board = CreateRandomBoard("boards/config.cfg");

    sf::RenderWindow window(sf::VideoMode(board.width, board.height), "Minesweeper");

    while(window.isOpen()){
        sf::Event event;

        while(window.pollEvent(event)) {
            if (event.type == sf::Event::Closed) {
                window.close();
            }

            else if (event.type == sf::Event::MouseButtonPressed) {
                sf::Vector2i mousePosition = sf::Mouse::getPosition(window);

                if (event.mouseButton.button == sf::Mouse::Left) {

                    for (int i = 0; i < board.gameBoard.size(); i++) {
                        auto bounds = board.gameBoard[i].SpriteLocation().getGlobalBounds();
                        if (bounds.contains(mousePosition.x, mousePosition.y) && board.gameBoard[i].isHidden && !board.gameOver
                            && !board.gameBoard[i].isFlagged && !board.gameWon) {
                            board.gameBoard[i].RevealTile();
                            board.gameWon = board.CheckGameWin();
                            if (board.gameBoard[i].isMine) {
                                board.gameOver = true;
                                board.debugEnabled = false;
                            }
                        }
                    }

                    //if one of the debug buttons are chosen
                    auto bounds1 = board.test_1.getGlobalBounds();
                    if (bounds1.contains(mousePosition.x, mousePosition.y)) {
                        board = ReadTestBoardFile("boards/testboard1.brd");
                    }
                    auto bounds2 = board.test_2.getGlobalBounds();
                    if (bounds2.contains(mousePosition.x, mousePosition.y)){
                        board = ReadTestBoardFile("boards/testboard2.brd");
                    }
                    auto bounds3 = board.test_3.getGlobalBounds();
                    if (bounds3.contains(mousePosition.x, mousePosition.y)){
                        board = ReadTestBoardFile("boards/testboard3.brd");
                    }
                    auto bounds4 = board.face_happy.getGlobalBounds();
                    if (bounds4.contains(mousePosition.x, mousePosition.y)){
                        board = CreateRandomBoard("boards/config.cfg");
                    }

                    //if debug option is shown, make all the mines visible

                    auto boundsMines = board.debug.getGlobalBounds();
                    if (boundsMines.contains(mousePosition.x, mousePosition.y) && !board.gameWon && !board.gameOver) {
                        if (board.debugEnabled) {
                            board.DebugDisable();
                        }
                        else {
                            board.DebugEnable();
                        }
                    }
                }


                else if (event.mouseButton.button == sf::Mouse::Right) {

                    for (int i = 0; i < board.gameBoard.size(); i++) {
                        auto bounds = board.gameBoard[i].SpriteLocation().getGlobalBounds();
                        if (bounds.contains(mousePosition.x, mousePosition.y) && board.gameBoard[i].isHidden && !board.gameOver
                        && !board.gameWon) {
                            if (board.gameBoard[i].isFlagged) {
                                board.gameBoard[i].UnflagTile();
                                board.numFlags--;
                                if (board.gameBoard[i].isMine) {
                                    board.correctFlags--;
                                }
                                board.CheckGameWin();
                            } else {
                                board.gameBoard[i].FlagTile();
                                board.numFlags++;
                                if (board.gameBoard[i].isMine) {
                                    board.correctFlags++;
                                }
                                board.CheckGameWin();
                            }
                        }
                    }
                }
            }
        }

        window.clear(sf::Color(255,255,255));


        for (int i = 0; i < board.tileCount; i++) {
            if (board.debugEnabled && !board.gameWon) {
                board.gameBoard[i].DrawDebug(window);
                board.GameOver(window);
            }
            else if(board.gameOver && !board.gameWon) {
                board.debugEnabled = false;
                board.gameBoard[i].DrawGameOver(window);
                board.GameOver(window);
            }
            else if(board.gameWon) {
                board.gameBoard[i].DrawGameWon(window);
                board.GameOver(window);
            }
            else {
                board.gameBoard[i].Draw(window);
                board.GameOver(window);
            }
        }
        //window.draw(board.face_happy);
        board.DrawButtons(window);
        board.DrawCounter(window);
        window.display();
    }

    return 0;
}