//
// Created by Sarah Foster on 4/8/21.
//
#include "Tiles.h"
#include "Board.h"

Tiles::Tiles() {
    tile_hidden.setTexture(TextureManager::GetTexture("tile_hidden"));
    tile_revealed.setTexture(TextureManager::GetTexture("tile_revealed"));
    flag.setTexture(TextureManager::GetTexture("flag"));
    mine.setTexture(TextureManager::GetTexture("mine"));
    isHidden = true;
    isFlagged = false;
    localMineCount = 0;
    countAssigned = false;
    recursiveReveal = false;
}

    void Tiles::RevealTile() {
        isHidden = false;
        if (localMineCount == 0 && !isMine && !isFlagged) {
            for (int i = 0; i < neighbors.size(); i++) {
                if (neighbors[i]->isHidden && neighbors[i]->localMineCount == 0 && !neighbors[i]->isFlagged) {
                    neighbors[i]->RevealTile();
                }
                else if (!neighbors[i]->isFlagged){
                    neighbors[i]->isHidden = false;
                }
            }
        }
    }

       void Tiles::FlagTile() {
           isFlagged = true;
       }

       void Tiles::UnflagTile() {
           isFlagged = false;
       }

       void Tiles::SetPosition(float x, float y) {
           tile_hidden.setPosition(x, y);
           flag.setPosition(x, y);
           tile_revealed.setPosition(x, y);
           mine.setPosition(x, y);
           xpos = x;
           ypos = y;
       }

       sf::Sprite Tiles::SpriteLocation() {
           return tile_revealed;
       }

       void Tiles::Draw(sf::RenderWindow &window) {
           window.draw(tile_revealed);
           if (isMine) {
               window.draw(mine);
           }
           if (!isHidden && !isMine) {
               window.draw(boardNum); // set number
           }
           if (isHidden) {
               window.draw(tile_hidden);
           }
           if (isFlagged) {
               window.draw(flag);
           }

       }

       void Tiles::DrawDebug(sf::RenderWindow &window) {
           //debugging doesn't stay on when changing boards
           //if there is a flag, the mine isnt revealed
           window.draw(tile_revealed);
           if (!isHidden && !isMine) {
               window.draw(boardNum); // set number
           }
           if (isHidden) {
               window.draw(tile_hidden);
           }
           if (isFlagged) {
               window.draw(flag);
           }
           if (isMine) {
               window.draw(mine);
           }

       }

       void Tiles::DrawGameOver(sf::RenderWindow &window) {
           window.draw(tile_revealed);
           if (!isHidden && !isMine) {
               window.draw(boardNum); // set number
           }
           if (isMine && isFlagged) {
               window.draw(flag);
               window.draw(mine);
           }
           if (isHidden && !isMine) {
               window.draw(tile_hidden);
           }
           if (isFlagged && !isMine) {
               window.draw(flag);
           }
           if (isMine && !isFlagged) {
               window.draw(mine);
           }
       }

    void Tiles::DrawGameWon(sf::RenderWindow &window) {
        window.draw(tile_revealed);
        if (isMine) {
            window.draw(tile_hidden);
            window.draw(flag);
        }
        else{
        window.draw(boardNum);
        }
    }


void Tiles::SetMineNumber() {
           if (!isMine && localMineCount > 0) {
               if (localMineCount == 1) {
                   boardNum.setTexture(TextureManager::GetTexture("number_1"));
               } else if (localMineCount == 2) {
                   boardNum.setTexture(TextureManager::GetTexture("number_2"));
               } else if (localMineCount == 3) {
                   boardNum.setTexture(TextureManager::GetTexture("number_3"));
               } else if (localMineCount == 4) {
                   boardNum.setTexture(TextureManager::GetTexture("number_4"));
               } else if (localMineCount == 5) {
                   boardNum.setTexture(TextureManager::GetTexture("number_5"));
               } else if (localMineCount == 6) {
                   boardNum.setTexture(TextureManager::GetTexture("number_6"));
               } else if (localMineCount == 7) {
                   boardNum.setTexture(TextureManager::GetTexture("number_7"));
               } else if (localMineCount == 8) {
                   boardNum.setTexture(TextureManager::GetTexture("number_8"));
               }
               boardNum.setPosition(xpos, ypos);
           }

       }