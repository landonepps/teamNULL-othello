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

set<Move> findMoves(int color, vector<pair<int, int> > const &pieces, vector<pair<int, int> > const &opponentsPieces, Board &b) {
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
                    // stored score is score of board
                    score = score + 1 + static_cast<int>(pieces.size());
                    moves.insert(Move(move, score, newBoard, color));
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
        root = new Move(make_pair(-1, -1), -1, b, opponent);
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
        Move noMoves(make_pair(-1, -1), 0, b, OPEN);
        return noMoves;
    }
    move = moves.begin()->position;

    for (set<Move>::iterator itr = moves.begin(); itr != moves.end(); itr++) {
        root->children.push_back(*itr);
    }
    
    Move minMove(make_pair(-1, -1), b.getCol()*b.getRow(), b, color);

    for (int i = 0; i < root->children.size(); i++) {
        Move newRoot = root->children[i];
        set<Move> chMoves;
        for (int j = 0; j < newRoot.board.getRow(); j++) {
            for (int k = 0; k < newRoot.board.getCol(); k++) {
                if (newRoot.board[j][k] == color) {
                    newRoot.pieces.push_back(make_pair(j, k));
                } else if (newRoot.board[j][k] == opponent) {
                    newRoot.opponentsPieces.push_back(make_pair(j, k));
                }
            }
        }
        chMoves = findMoves(opponent, newRoot.opponentsPieces, newRoot.pieces, newRoot.board);
        
        for (set<Move>::iterator itr = chMoves.begin(); itr != chMoves.end(); itr++) {
            newRoot.children.push_back(*itr);
        }

        // make sure this works
        if (newRoot.children.size() > 0) {
            newRoot.score = newRoot.children[newRoot.children.size() - 1].score;
        } else newRoot.score = 0;
        
        if (minMove.score > newRoot.score) minMove = newRoot;
    }
    move = minMove.position;

    for (int i = 0; i < root->children.size(); i++) {
        Move newRoot = root->children[i];
        for (int j = 0; j < newRoot.children.size(); j++) {
            set<Move> chMoves;
            newRoot = newRoot.children[j];
            
            for (int a = 0; a < newRoot.board.getRow(); a++) {
                for (int b = 0; b < newRoot.board.getCol(); b++) {
                    if (newRoot.board[a][b] == color) {
                        newRoot.pieces.push_back(make_pair(a, b));
                    } else if (newRoot.board[a][b] == opponent) {
                        newRoot.opponentsPieces.push_back(make_pair(a, b));
                    }
                }
            }
            
            chMoves = findMoves(color, newRoot.pieces, newRoot.opponentsPieces, newRoot.board);

            for (set<Move>::iterator itr = chMoves.begin(); itr != chMoves.end(); itr++) {
                newRoot.children.push_back(*itr);
            }

            for (int k = 0; k < newRoot.children.size(); k++) {
                set<Move> chMoves;
                newRoot = newRoot.children[k];

                for (int a = 0; a < newRoot.board.getRow(); a++) {
                    for (int b = 0; b < newRoot.board.getCol(); b++) {
                        if (newRoot.board[a][b] == color) {
                            newRoot.pieces.push_back(make_pair(a, b));
                        } else if (newRoot.board[a][b] == opponent) {
                            newRoot.opponentsPieces.push_back(make_pair(a, b));
                        }
                    }
                }

                chMoves = findMoves(opponent, newRoot.opponentsPieces, newRoot.pieces, newRoot.board);

                for (set<Move>::iterator itr = chMoves.begin(); itr != chMoves.end(); itr++) {
                    newRoot.children.push_back(*itr);
                }

                // make sure this works
                if (newRoot.children.size() > 0) {
                    newRoot.score = newRoot.children[newRoot.children.size() - 1].score;
                } else newRoot.score = 0;
            }
            // calculate minimum child
            Move minMove(make_pair(-1, -1), b.getCol()*b.getRow(), b, color);
            for (int c = 0; c < newRoot.children.size(); c++) {
                if (minMove.score > newRoot.children[c].score) minMove = newRoot.children[c];
            }
            newRoot.score = minMove.score;
        }
        // calculate maximum child
        Move maxMove(make_pair(-1, -1), 0, b, color);
        for (int c = 0; c < newRoot.children.size(); c++) {
            if (maxMove.score < newRoot.children[c].score) maxMove = newRoot.children[c];
        }
        newRoot.score = minMove.score;
    }
    // calculate minimum child
    Move result(make_pair(-1, -1), b.getCol()*b.getRow(), b, color);
    for (int c = 0; c < root->children.size(); c++) {
        if (result.score > root->children[c].score) result = root->children[c];
    }

    return result;
}

////////////////////// change return type to void
Move TeamNULLGen::move(Board b, pair<int,int> &move) {
    int color = getColor();
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }

    if (!root) {
        root = new Move(make_pair(-1, -1), -1, b, opponent);
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
        Move noMoves(make_pair(-1, -1), 0, b, OPEN);
        return noMoves;
    }
    move = moves.begin()->position;

    /*set<Move>::iterator itr;
    for(itr = moves.begin(); itr != moves.end(); itr++);

    return *(--itr)*/
    return *(moves.begin());
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
        TeamNULLGre player1(BLACK);
        TeamNULLGre player2(WHITE);
        Move moveObj = player1.move(board, move);
        board = moveObj.board;
        printBoard(board);
        moveObj = player2.move(board, move);
        board = moveObj.board;
        printBoard(board);
    }
    
    return 0;
}
