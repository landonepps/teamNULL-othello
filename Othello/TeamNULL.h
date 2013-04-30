/******************************************************************************
 Author: Team NULL
 Title : Othello AI
 Description: This algorithm determines the optimal moves for a game of
 Othello. While this algorithm doesn't solve the game of Othello (since
 right now, Othello is considered an unsolved game), it implements a
 strategy which will calculate winning moves for the game.
 Created: 4/16/2013
 Modified: 4/29/2013
 Due: 4/29/2013
 ******************************************************************************/
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

class Move {
public:
    pair<int, int> position;
    int score;
    Board board;
    bool operator<(const Move &other) const {
        return (this->score < other.score);
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

struct moveNode {
    int color;
    vector<moveNode> children;
    Board board;
    vector<pair<int, int> > pieces;
    vector<pair<int, int> > oppPiece;
    pair<int, int> move;
};

class TeamNULL: public Player
{
private:
    moveNode *root;
    Move findMax(Board b);
    Move findMin(Board b);
public:
    TeamNULL(int c):Player(c) {
        root = NULL;
    }
    //**************************************************************************
    // name: move                                                              *
    // description: finds a location to place a piece for the current move of  *
    //     Othello given the board.                                            *
    // return type: void                                                       *
    // pre: the board information is valid and reflects the current state of   *
    //      the game.                                                          *
    // post: the move reference passed is changed to the decided piece         *
    //       placement                                                         *
    // returns: nothing                                                        *
    //**************************************************************************
    //void move(Board, pair<int,int>&);
    Move move(Board, pair<int,int>&);
};

#endif
