//
// Created by Sarah Foster on 4/7/21.
//
#include "Board.h"
#include <sstream>

Board::Board(int width, int height, int mineCount, string fileName) {
    numTilesHeight = height;
    numTilesWidth = width;
    this->tileCount = width * height;
    this->width = width * 32;
    this->height = (height * 32) + 88;
    this->mineCount = mineCount;
    debugEnabled = false;
    gameOver = false;
    gameWon = false;
    numFlags = 0;
    correctFlags = 0;

    SetTextures();
    IsAMine(fileName);
    CreateBoard();
    FindNeighboringTiles();

}

Board::Board(int width, int height, int mineCount, vector<int>& mines) {
    numTilesHeight = height;
    numTilesWidth = width;
    this->tileCount = width * height;
    this->width = width * 32;
    this->height = (height * 32) + 88;
    this->mineCount = mineCount;
    debugEnabled = false;
    gameOver = false;
    gameWon = false;
    numFlags = 0;
    correctFlags = 0;
    this->mines = mines;

    SetTextures();
    CreateBoard();
    FindNeighboringTiles();
}

void Board::SetTextures(){
    face_happy.setTexture(TextureManager::GetTexture("face_happy"));
    face_happy.setPosition((float)width/2 - 1, (float)height - 89);
    face_win.setTexture(TextureManager::GetTexture("face_win"));
    face_win.setPosition((float)width/2 - 1, (float)height - 89);
    face_lose.setTexture(TextureManager::GetTexture("face_lose"));
    face_lose.setPosition((float)width/2 - 1, (float)height - 89);


    digits1.setTexture(TextureManager::GetTexture("digits"));
    digits1.setPosition((float)21, (float)height - 89);
    digits2.setTexture(TextureManager::GetTexture("digits"));
    digits2.setPosition((float)42, (float)height - 89);
    digits3.setTexture(TextureManager::GetTexture("digits"));
    digits3.setPosition((float)63, (float)height - 89);
    digitsExtra.setTexture(TextureManager::GetTexture("digits"));
    digitsExtra.setPosition((float)0, (float)height - 89);

    debug.setTexture(TextureManager::GetTexture("debug"));
    debug.setPosition((float)width/2 + 128, (float)height - 89);

    test_1.setTexture(TextureManager::GetTexture("test_1"));
    test_1.setPosition((float)width/2 + 192, (float)height - 89);
    test_2.setTexture(TextureManager::GetTexture("test_2"));
    test_2.setPosition((float)width/2 + 256, (float)height - 89);
    test_3.setTexture(TextureManager::GetTexture("test_3"));
    test_3.setPosition((float)width/2 + 320, (float)height - 89);

}

void Board::CreateBoard() {
    int x = 0;
    int y = 0;
    for (int i = 0; i < tileCount; i++) {
        Tiles tempTile;
        tempTile.isMine = mines[i];
        //set xy values
        tempTile.xpos = (float)x;
        tempTile.ypos = (float)y;
        tempTile.SetPosition((float)x, (float)y);
        x += 32;
        if (x % width == 0) {
            x = 0;
            y += 32;
        }
//        vector<float> coordinates;
//        coordinates.push_back(x);
//        coordinates.push_back(y);
//        gameBoardPlacement.insert({coordinates, tempTile});
        gameBoard.push_back(tempTile);//need to load in a specific board to set the bools
    }
}

void Board::IsAMine(string fileName) {
    ifstream InputFile;
    InputFile.open(fileName);
    char input;
    int isMine;
    int mineCounter = 0;
    if (InputFile.is_open()) {
        while(InputFile.get(input)){
            //InputFile.get(input);
            isMine = (int)(input) - 48;
            if (isMine == 1) {
                mineCounter++;
            }
            if (isMine == 0 || isMine == 1) {
                mines.push_back(isMine);
            }
        }
    }
}

void Board::DebugEnable() {
    debugEnabled = true;
}

void Board::DebugDisable() {
    debugEnabled = false;
}

void Board::DrawCounter(sf::RenderWindow &window) {
    currentMineCount = mineCount - numFlags;
    if (currentMineCount == 0 || gameWon) {
        digits1.setTextureRect(sf::IntRect(0, 0, 21, 32));
        digits2.setTextureRect(sf::IntRect(0, 0, 21, 32));
        digits3.setTextureRect(sf::IntRect(0, 0, 21, 32));
    }
    else if (currentMineCount <= -100) {
        digitsExtra.setTextureRect(sf::IntRect(210, 0, 21, 32));
        int hundredsPlace = abs(currentMineCount) / 100;
        int placement = hundredsPlace * 21;
        digits1.setTextureRect(sf::IntRect(placement, 0, 21, 32));
        int tensPlace = (abs(currentMineCount) - (hundredsPlace * 100) ) / 10;
        placement = tensPlace * 21;
        digits2.setTextureRect(sf::IntRect(placement, 0, 21, 32));
        int onesPlace = (abs(currentMineCount) - (hundredsPlace * 100)) % 10;
        placement = onesPlace * 21;
        digits3.setTextureRect(sf::IntRect(placement, 0, 21, 32));

    }
    else if (currentMineCount < 0 && currentMineCount > -100) {
        //fist image is 0
        digits1.setTextureRect(sf::IntRect(210, 0, 21, 32));
        currentMineCount = abs(currentMineCount);
        int tensPlace = currentMineCount / 10;
        int placement = tensPlace * 21;
        digits2.setTextureRect(sf::IntRect(placement, 0, 21, 32));
        int onesPlace = currentMineCount % 10;
        placement = onesPlace * 21;
        digits3.setTextureRect(sf::IntRect(placement, 0, 21, 32));

    }
    else {
        int hundredsPlace = currentMineCount / 100;
        int placement = hundredsPlace * 21;
        digits1.setTextureRect(sf::IntRect(placement, 0, 21, 32));
        int tensPlace = (currentMineCount - (hundredsPlace * 100) ) / 10;
        placement = tensPlace * 21;
        digits2.setTextureRect(sf::IntRect(placement, 0, 21, 32));
        int onesPlace = (currentMineCount - (hundredsPlace * 100)) % 10;
        placement = onesPlace * 21;
        digits3.setTextureRect(sf::IntRect(placement, 0, 21, 32));

    }
    if (currentMineCount <= -100) {
        window.draw(digitsExtra);
    }
    window.draw(digits1);
    window.draw(digits2);
    window.draw(digits3);
}

void Board::DrawButtons(sf::RenderWindow &window) {
    window.draw(debug);
    window.draw(test_1);
    window.draw(test_2);
    window.draw(test_3);
}

void Board::GameOver(sf::RenderWindow &window) {
    if (gameOver) {
        window.draw(face_lose);
    }
    else if(gameWon) {
        window.draw(face_win);
    }
    else {
        window.draw(face_happy);
    }
}

bool Board::CheckGameWin() {
    int revealed = 0;
    for (int i = 0; i < gameBoard.size(); i++) {
        if (!gameBoard[i].isHidden) {
            revealed++;
        }
    }
    if (revealed == (gameBoard.size() - mineCount)) {
        //mineCount = 0;
        return true;
    }
    return false;
}

void Board::FindNeighboringTiles() {

    //left upper corner
    gameBoard[0].neighbors.push_back(&gameBoard[1]);
    gameBoard[0].neighbors.push_back(&gameBoard[numTilesWidth]);
    gameBoard[0].neighbors.push_back(&gameBoard[numTilesWidth + 1]);
    if (!gameBoard[0].isMine) {
        for (int i = 0; i < 3; i++) {
            if (gameBoard[0].neighbors[i]->isMine) {
                gameBoard[0].localMineCount++;
            }
        }
        gameBoard[0].countAssigned = true;
        gameBoard[0].SetMineNumber();
    }
    //right upper corner
    gameBoard[numTilesWidth - 1].neighbors.push_back(&gameBoard[numTilesWidth - 2]);
    gameBoard[numTilesWidth - 1].neighbors.push_back(&gameBoard[2 * numTilesWidth - 2]);
    gameBoard[numTilesWidth - 1].neighbors.push_back(&gameBoard[2 * numTilesWidth - 1]);
    if (!gameBoard[numTilesWidth - 1].isMine) {
        for (int i = 0; i < 3; i++) {
            if (gameBoard[numTilesWidth - 1].neighbors[i]->isMine) {
                gameBoard[numTilesWidth - 1].localMineCount++;
            }
        }
        gameBoard[numTilesWidth - 1].SetMineNumber();
        gameBoard[numTilesWidth - 1].countAssigned = true;
    }
    //left bottom corner
    gameBoard[numTilesWidth * (numTilesHeight - 1)].neighbors.push_back(&gameBoard[numTilesWidth * (numTilesHeight - 2)]);
    gameBoard[numTilesWidth * (numTilesHeight - 1)].neighbors.push_back(&gameBoard[numTilesWidth * (numTilesHeight - 2) + 1]);
    gameBoard[numTilesWidth * (numTilesHeight - 1)].neighbors.push_back(&gameBoard[numTilesWidth * (numTilesHeight - 1) + 1]);
    if (!gameBoard[numTilesWidth * (numTilesHeight - 1)].isMine) {
        for (int i = 0; i < 3; i++) {
            if (gameBoard[numTilesWidth * (numTilesHeight - 1)].neighbors[i]->isMine) {
                gameBoard[numTilesWidth * (numTilesHeight - 1)].localMineCount++;
            }
        }
        gameBoard[numTilesWidth * (numTilesHeight - 1)].SetMineNumber();
        gameBoard[numTilesWidth * (numTilesHeight - 1)].countAssigned = true;
    }
    //right bottom corner
    gameBoard[numTilesWidth * numTilesHeight - 1].neighbors.push_back(&gameBoard[numTilesWidth * (numTilesHeight - 1)- 1]);
    gameBoard[numTilesWidth * numTilesHeight - 1].neighbors.push_back(&gameBoard[numTilesWidth * (numTilesHeight - 1)- 2]);
    gameBoard[numTilesWidth * numTilesHeight - 1].neighbors.push_back(&gameBoard[numTilesWidth * numTilesHeight - 2]);
    if (!gameBoard[numTilesWidth * numTilesHeight - 1].isMine) {
        for (int i = 0; i < 3; i++) {
            if (gameBoard[numTilesWidth * numTilesHeight - 1].neighbors[i]->isMine) {
                gameBoard[numTilesWidth * numTilesHeight - 1].localMineCount++;
            }
        }
        gameBoard[numTilesWidth * numTilesHeight - 1].SetMineNumber();
        gameBoard[numTilesWidth * numTilesHeight - 1].countAssigned = true;
    }
    //top row (excluding corners)
    for (int i = 1; i < numTilesWidth - 1; i++) {
        gameBoard[i].neighbors.push_back(&gameBoard[i+1]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-1]);
        gameBoard[i].neighbors.push_back(&gameBoard[i+1+numTilesWidth]);
        gameBoard[i].neighbors.push_back(&gameBoard[i+numTilesWidth]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-1+numTilesWidth]);
        if (!gameBoard[i].isMine) {
            for (int j = 0; j < 5; j++) {
                if (gameBoard[i].neighbors[j]->isMine) {
                    gameBoard[i].localMineCount++;
                }
            }
            gameBoard[i].SetMineNumber();
            gameBoard[i].countAssigned = true;
        }
    }
    //bottom row (excluding corners)
    for (int i = numTilesWidth * (numTilesHeight - 1) + 1; i < numTilesWidth * numTilesHeight - 1; i++) {
        gameBoard[i].neighbors.push_back(&gameBoard[i+1]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-1]);
        gameBoard[i].neighbors.push_back(&gameBoard[i+1-numTilesWidth]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-numTilesWidth]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-1-numTilesWidth]);
        if (!gameBoard[i].isMine) {
            for (int j = 0; j < 5; j++) {
                if (gameBoard[i].neighbors[j]->isMine) {
                    gameBoard[i].localMineCount++;
                }
            }
            gameBoard[i].SetMineNumber();
            gameBoard[i].countAssigned = true;

        }
    }
    //left
    for (int i = numTilesWidth; i < numTilesWidth * (numTilesHeight - 1); i+=numTilesWidth) {
        gameBoard[i].neighbors.push_back(&gameBoard[i+1]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-numTilesWidth]);
        gameBoard[i].neighbors.push_back(&gameBoard[i+numTilesWidth]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-numTilesWidth+1]);
        gameBoard[i].neighbors.push_back(&gameBoard[i+1+numTilesWidth]);
        if (!gameBoard[i].isMine) {
            for (int j = 0; j < 5; j++) {
                if (gameBoard[i].neighbors[j]->isMine) {
                    gameBoard[i].localMineCount++;
                }
            }
            gameBoard[i].SetMineNumber();
            gameBoard[i].countAssigned = true;

        }
    }

    //right
    for (int i = 2*numTilesWidth - 1; i < numTilesWidth * numTilesHeight - 1; i+=numTilesWidth) {
        gameBoard[i].neighbors.push_back(&gameBoard[i-1]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-numTilesWidth]);
        gameBoard[i].neighbors.push_back(&gameBoard[i+numTilesWidth]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-numTilesWidth-1]);
        gameBoard[i].neighbors.push_back(&gameBoard[i-1+numTilesWidth]);
        if (!gameBoard[i].isMine) {
            for (int j = 0; j < 5; j++) {
                if (gameBoard[i].neighbors[j]->isMine) {
                    gameBoard[i].localMineCount++;
                }
            }
            gameBoard[i].SetMineNumber();
            gameBoard[i].countAssigned = true;

        }
    }
    //middle tiles
    for (int i = 0; i < gameBoard.size(); i++) {
        if (!gameBoard[i].countAssigned) {
            gameBoard[i].neighbors.push_back(&gameBoard[i-1]);
            gameBoard[i].neighbors.push_back(&gameBoard[i+1]);
            gameBoard[i].neighbors.push_back(&gameBoard[i-numTilesWidth]);
            gameBoard[i].neighbors.push_back(&gameBoard[i+numTilesWidth]);
            gameBoard[i].neighbors.push_back(&gameBoard[i-numTilesWidth-1]);
            gameBoard[i].neighbors.push_back(&gameBoard[i-1+numTilesWidth]);
            gameBoard[i].neighbors.push_back(&gameBoard[i+1-numTilesWidth]);
            gameBoard[i].neighbors.push_back(&gameBoard[i+1+numTilesWidth]);
            if (!gameBoard[i].isMine) {
                for (int j = 0; j < 8; j++) {
                    if (gameBoard[i].neighbors[j]->isMine) {
                        gameBoard[i].localMineCount++;
                    }
                }
                gameBoard[i].SetMineNumber();
                gameBoard[i].countAssigned = true;

            }
        }
    }
}





