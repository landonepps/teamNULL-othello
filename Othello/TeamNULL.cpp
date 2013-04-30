//
//  main.cpp
//  Othello
//
//  Created by Landon Epps on 4/16/13.
//  Copyright (c) 2013 Landon Epps. All rights reserved.
//

#include "TeamNULL.h"

const pair<int, int> adjacentMoves[8] = {make_pair(-1, 0), make_pair(-1, 1),
make_pair(0 , 1), make_pair(1 , 1), make_pair(1 , 0), make_pair(1 , -1),
make_pair(0, -1), make_pair(-1, -1)};

void printBoard(Board b) {
    for (int i = 0; i < b.getRow(); i++) {
        for (int j = 0; j < b.getCol(); j++) {
            if (b[i][j] == WHITE) {
                cout << "☺ ";
            } else if (b[i][j] == BLACK) {
                cout << "☻ ";
            } else {
                cout << "- ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

set<Move> findMoves(int color, vector<pair<int, int> > &pieces, vector<pair<int, int> > &opponentsPieces, Board &b) {
    set<Move> moves;
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }
    // for all opponents pieces
    for (int i = 0; i < opponentsPieces.size(); i++) {
        // for all directions
        for(int j = 0; j < 8; j++) {
            // make a move for each direction in adjacentMoves
            pair<int,int> move = make_pair(opponentsPieces[i].first + adjacentMoves[j].first,
                                           opponentsPieces[i].second + adjacentMoves[j].second);
            // if that move is on the board and is open
            if (move.first >= 0 && move.first < b.getRow() &&
                move.second >= 0 && move.second < b.getCol() &&
                b[move.first][move.second] == OPEN) {
                // keep track of score
                int score = 0;
                Board newBoard = b;
                newBoard[move.first][move.second] = color;
                // for all directions
                for (int k = 0; k < 8; k++) {
                    // keep track of score for each direction
                    int tempScore = 0;
                    Board tempBoard = newBoard;
                    pair<int, int> nextDirection = make_pair(move.first + adjacentMoves[k].first,
                                                             move.second + adjacentMoves[k].second);
                    
                    while (nextDirection.first >= 0 && nextDirection.first < b.getRow() &&
                           nextDirection.second >= 0 && nextDirection.second < b.getCol() &&
                           b[nextDirection.first][nextDirection.second] == opponent) {
                        tempScore++;
                        tempBoard[nextDirection.first][nextDirection.second] = color;
                        nextDirection = make_pair(nextDirection.first + adjacentMoves[k].first,
                                                  nextDirection.second + adjacentMoves[k].second);
                    }
                    if (nextDirection.first >= 0 && nextDirection.first < b.getRow() &&
                        nextDirection.second >= 0 && nextDirection.second < b.getCol() &&
                        b[nextDirection.first][nextDirection.second] == color) {
                        score += tempScore;
                        newBoard = tempBoard;
                    }
                }
                if (score > 0) {
                    Move tempMove(move, score, newBoard);
                    moves.insert(tempMove);
                }
            }
        }
    }
    return moves;
}

////////////////////// change return type to void
Move TeamNULL::move(Board b, pair<int,int> &move) {
    int color = getColor();
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }

    if (!root) {
        root = new moveNode;
        root->color = opponent;
        root->board = b;
        root->move = make_pair(-1, -1);
        for (int i = 0; i < b.getRow(); i++) {
            for (int j = 0; j < b.getCol(); j++) {
                if (b[i][j] == color) {
                    root->pieces.push_back(make_pair(i, j));
                } else if (b[i][j] == opponent){
                    root->opponentsPieces.push_back(make_pair(i, j));
                }
            }
        }
    }
    
    set<Move> moves;
    moves = findMoves(color, root->pieces, root->opponentsPieces, b);
    ////////////// remove later
    if (moves.empty()) {
        Move noMoves(make_pair(-1, -1), 0, b);
        return noMoves;
    }
    move = moves.begin()->position;

    return *(moves.begin());
}

Move findMax(Board b, int level) {

    level--;
    if (level > 0) {
        findMin();
    }
}

Move findMin(Board b, int level) {

    level--;
    if (level > 0) {
        findMax();
    }
}

int main(int argc, const char * argv[])
{
    Board board;
    
    board[3][3] = WHITE;
    board[3][4] = BLACK;
    board[4][3] = BLACK;
    board[4][4] = WHITE;

    printBoard(board);
    pair<int, int> move;

    for (int i = 0; i < 32; i++) {
        TeamNULL player1(BLACK);
        TeamNULL player2(WHITE);
        Move moveObj = player1.move(board, move);
        board = moveObj.board;
        printBoard(board);
        moveObj = player2.move(board, move);
        board = moveObj.board;
        printBoard(board);
    }
    
    return 0;
}
