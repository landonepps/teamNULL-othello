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

struct moveInfo {
    int score;
    pair<int, int> move;
    moveInfo (int s, pair<int, int> m) {
        score = s;
        move = m;
    }
};

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
        if (this != &other) {
            if (grid) {
                for (int i = 0; i < row; i++) {
                    delete [] grid[i];
                }
                delete [] grid;
            }
            row = other.row;
            col = other.col;
            grid = new int*[row];
            for (int i = 0; i < row; i++) {
                grid[i] = new int[col];
                for (int j = 0; j < col; j++) {
                    grid[i][j] = other.grid[i][j];
                }
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

class Move {
public:
    pair<int, int> position;
    int score;
    int color;
    Board board;
    vector<Move> children;
    vector<pair<int, int> > pieces;
    vector<pair<int, int> > opponentsPieces;
    bool operator<(const Move &other) const {
        bool result = false;
        if (score < other.score) result = true;
        else if (position.first < other.position.first) result = true;
        else if (position.second < other.position.second) result = true;
        return result;
    }

    Move(pair<int, int> p, int s, Board const &b, int c) {
        position = p;
        score = s;
        board = b;
        color = c;
    }
    
    Move(Move const &other) {
        position = other.position;
        score = other.score;
        board = other.board;
        color = other.color;
    }
};

class Player{
private:
    int color;
    
public:
    Player(int c = BLACK) { color = c; }
    virtual ~Player() { };
    int getColor() { return color; }
    void setColor(int c) { color = c; }
    ///////// This needs to be changed back
    //virtual void move(Board, pair<int,int>&) = 0;
};


class TeamNULL: public Player
{
private:
    Move *root;
    Move findMax(Board b);
    Move findMin(Board b);
public:
    TeamNULL(int c):Player(c) {
        root = NULL;
    }
    ////////// This needs to be changed back
    //void move(Board, pair<int,int>&);
    Move move(Board, pair<int,int>&);
};

class TeamNULLGen: public Player
{
private:
    Move *root;
public:
    TeamNULLGen(int c):Player(c) {
        root = NULL;
    }
    ////////// This needs to be changed back
    //void move(Board, pair<int,int>&);
    Move move(Board, pair<int,int>&);
};

#endif
