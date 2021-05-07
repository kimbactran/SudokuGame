#ifndef SUDOKU_H
#define SUDOKU_H
#include <stdio.h>
#include <stdbool.h>
#include <iostream>
#include <random>
#include <algorithm>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <chrono>
#include<stdlib.h>
#define UNASSIGNED 0

using namespace std;

class Sudoku
{
    public:
        Sudoku();
        virtual ~Sudoku();
        int grid[9][9];
          int solnGrid[9][9];
          int guessNum[9];
          int gridPos[81];
          int level=1;
          Sudoku (string, bool row_major=true);
          void createSeed();
          bool solveGrid();
          string getGrid();
          void countSoln(int &number);
          void genPuzzle();
          bool verifyGridStatus();

    private:
        int difficultyLevel;
        bool grid_status;
};

#endif // SUDOKU_H
