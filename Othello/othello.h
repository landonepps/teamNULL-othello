//
//  othello.h
//  Othello
//
//  Created by Landon Epps on 4/16/13.
//  Copyright (c) 2013 Landon Epps. All rights reserved.
//
//  Testing Commit to GitHub

#ifndef Othello_othello_h
#define Othello_othello_h

#include <utility>

using namespace std;

const int OPEN  = 0;
const int BLACK = 1;
const int WHITE = 2;


class Board{
private:
    int row, col;
    int **grid;
public:
    int getRow();
    int getCol();
    int* operator[](int n);
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
