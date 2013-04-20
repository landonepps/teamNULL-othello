//
//  othello.h
//  Othello
//
//  Created by Landon Epps on 4/16/13.
//  Copyright (c) 2013 Landon Epps. All rights reserved.
//

#ifndef Othello_othello_h
#define Othello_othello_h

#include <utility>

using namespace std;

const int OPEN  = 0;
const int BLACK = 1;
const int WHITE = 2;

/*
class Board{
private:
    int row, col;
    int **grid;
public:
    int getRow();
    int getCol();
    int* operator[](int n);
};*/

class Board {
private:
    int row, col;
    int **grid;
public:
    int getRow() {
        return row;
    }
    int getCol() {
        return col;
    }
    Board(int r = 8, int c = 8) {
        row = r;
        col = c;
        grid = new int*[row];
        for (int i = 0; i < row; i++) {
            grid[i] = new int[col];
            for (int j = 0; j < col; j++) {
                grid[i][j] = OPEN;
            }
        }
        grid[0][0] = WHITE;
        grid[1][1] = WHITE;
        grid[2][2] = WHITE;
        grid[3][3] = WHITE;
        grid[1][0] = BLACK;
        grid[1][2] = BLACK;
        grid[2][3] = BLACK;
        grid[3][2] = BLACK;

        
    }
    ~Board() {
        for (int i = 0; i < row; i++) {
            //delete [] grid[i];
        }
        //delete [] grid;
    }
    int* operator[](int n) {
        return grid[n];
    }
};

class Player{
private:
    int color;
    
public:
    Player(int c = BLACK);
    virtual ~Player();
    int getColor();
    void setColor(int c);
    virtual void move(Board, pair<int,int>&);
};

class TeamNULLPlayer: public Player
{
private:

public:
    pair<int,int> move(Board b);
};

#endif
