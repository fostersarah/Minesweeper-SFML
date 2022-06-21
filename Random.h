//
// Created by Sarah Foster on 4/20/21.
//

#ifndef MINESWEEPER1_RANDOM_H
#define MINESWEEPER1_RANDOM_H
#include <iostream>
#include <random>

class Random {
    static std::mt19937 random;
public:
    static int Int(int min, int max);
    static float Float(int min, int max);
};


#endif //MINESWEEPER1_RANDOM_H
