//
//  main.cpp
//  Othello
//
//  Created by Landon Epps on 4/16/13.
//  Copyright (c) 2013 Landon Epps. All rights reserved.
//

#include "othello.h"

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
                cout << "_ ";
            }
        }
        cout << endl;
    }
    cout << endl;
}

/*
struct moveInfo {
    int score;
    pair<int, int> move;
    moveInfo (int s, pair<int, int> m) {
        score = s;
        move = m;
    }
};
*/

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

void TeamNULLPlayer::move(Board b, pair<int,int> &move) {
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
    
    // set<Move> moves;
    // moves = findMoves(color, root->pieces, root->opponentsPieces, b);
    
}


int main(int argc, const char * argv[])
{
    Board board;
    Move move(make_pair(1, 1), 2, board);
    vector<pair<int, int> > blackPieces;
    vector<pair<int, int> > whitePieces;
    blackPieces.push_back(make_pair(1, 0));
    blackPieces.push_back(make_pair(1, 2));
    blackPieces.push_back(make_pair(2, 3));
    blackPieces.push_back(make_pair(3, 2));
    whitePieces.push_back(make_pair(0, 0));
    whitePieces.push_back(make_pair(1, 1));
    whitePieces.push_back(make_pair(2, 2));
    whitePieces.push_back(make_pair(3, 3));

    board[0][0] = WHITE;
    board[1][1] = WHITE;
    board[2][2] = WHITE;
    board[3][3] = WHITE;
    board[1][0] = BLACK;
    board[1][2] = BLACK;
    board[2][3] = BLACK;
    board[3][2] = BLACK;

    printBoard(board);

    set<Move> theMoves;
    theMoves = findMoves(1, blackPieces, whitePieces, board);
    
    for (set<Move>::iterator itr = theMoves.begin(); itr != theMoves.end(); itr++) {
        cout << "Move: (" << itr->position.first << ", " << itr->position.second << ")" << endl;
        cout << "Score: " << itr->score << endl;
        cout << "Board: " << endl;
        printBoard(itr->board);
    }

    return 0;
}
