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
#include <iostream>
#include <vector>
#include <set>

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
    }

    ~Board() {
        for (int i = 0; i < row; i++) {
            delete [] grid[i];
        }
        delete [] grid;
    }

    Board operator=(Board const &other) {
        row = other.row;
        col = other.col;
        grid = new int*[row];
        for (int i = 0; i < row; i++) {
            grid[i] = new int[col];
            for (int j = 0; j < col; j++) {
                grid[i][j] = other.grid[i][j];
            }
        }
        return *this;
    }

    Board(Board const &b) {
        row = b.row;
        col = b.col;
        grid = new int*[row];
        for (int i = 0; i < row; i++) {
            grid[i] = new int[col];
            for (int j = 0; j < col; j++) {
                grid[i][j] = b.grid[i][j];
            }
        }
    }

    int* operator[](int n) {
        return grid[n];
    }
};

struct moveNode {
    int color;
    // moveNode *parent;
    vector<moveNode> children;
    // int score;
    Board board;
    vector<pair<int, int> > pieces;
    vector<pair<int, int> > opponentsPieces;
    pair<int, int> move;
    /*
     moveNode(){
     score = s;
     }
     */
};

class Move {
public:
    pair<int, int> position;
    int score;
    Board board;
    bool operator<(const Move &other) const {
        return (this->position.first < other.position.first);
    }

    Move(pair<int, int> p, int s, Board const &b) {
        position = p;
        score = s;
        board = b;
    }
    
    Move(Move const &other) {
        position = other.position;
        score = other.score;
        board = other.board;
    }
};

class Player{
private:
    int color;
    
public:
    Player(int c = BLACK) { color = c; }
    virtual ~Player();
    int getColor() { return color; }
    void setColor(int c) { color = c; }
    virtual void move(Board, pair<int,int>&);
};

class TeamNULLPlayer: public Player
{
private:
    moveNode *root;
public:
    void move(Board, pair<int,int>&);
    TeamNULLPlayer() {
        root = NULL;
    }
};

#endif
