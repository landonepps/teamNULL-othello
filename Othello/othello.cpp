//
//  main.cpp
//  Othello
//
//  Created by Landon Epps on 4/16/13.
//  Copyright (c) 2013 Landon Epps. All rights reserved.
//

#include <iostream>
#include <vector>
#include "othello.h"

const pair<int, int> adjacentMoves[8] = {make_pair(-1, 0), make_pair(-1, 1),
make_pair(0 , 1), make_pair(1 , 1), make_pair(1 , 0), make_pair(1 , -1),
make_pair(0, -1), make_pair(-1, -1)};

/*
struct moveNode {
    moveNode *parent;
    vector<moveNode> children;
    int score;
    bool max;
    pair<int, int> move;
    moveNode(int s, int m){
        score = s;
        max = m;
    }
};
*/
struct moveInfo {
    int score;
    pair<int, int> move;
    moveInfo (int s, pair<int, int> m) {
        score = s;
        move = m;
    }
};

vector<moveInfo> findMoves(int color, vector<pair<int, int> > &blackPieces, vector<pair<int, int> > &whitePieces, Board b) {
    vector<pair<int, int> > *opponentsPieces;
    vector<moveInfo> moves;
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
        opponentsPieces = &blackPieces;
    } else {
        opponent = WHITE;
        opponentsPieces = &whitePieces;
    }
    // for all opponents pieces
    for (int i = 0; i < opponentsPieces->size(); i++) {
        // for all directions
        for(int j = 0; j < 8; j++) {
            // make a move for each direction in adjacentMoves
            pair<int,int> move = make_pair((*opponentsPieces)[i].first + adjacentMoves[j].first,
                                           (*opponentsPieces)[i].second + adjacentMoves[j].second);
            // if that move is on the board and is open
            if (move.first >= 0 && move.first < b.getRow() &&
                move.second >= 0 && move.second < b.getCol() &&
                b[move.first][move.second] == OPEN) {
                // keep track of score
                int score = 0;
                // for all directions
                for (int k = 0; k < 8; k++) {
                    // keep track of score for each direction
                    int tempScore = 0;
                    pair<int, int> nextDirection = make_pair(move.first + adjacentMoves[k].first,
                                                             move.second + adjacentMoves[k].second);
                    
                    while (nextDirection.first >= 0 && nextDirection.first < b.getRow() &&
                           nextDirection.second >= 0 && nextDirection.second < b.getCol() &&
                           b[nextDirection.first][nextDirection.second] == opponent) {
                        tempScore++;
                        nextDirection = make_pair(nextDirection.first + adjacentMoves[k].first,
                                                  nextDirection.second + adjacentMoves[k].second);
                    }
                    if (nextDirection.first >= 0 && nextDirection.first < b.getRow() &&
                        nextDirection.second >= 0 && nextDirection.second < b.getCol() &&
                        b[nextDirection.first][nextDirection.second] == color) {
                        score += tempScore;
                    }
                }
                if (score > 0) {
                    moves.push_back(moveInfo(score, move));
                }
            }
        }
    }
    return moves;
}
/*
pair<int, int> generateTree(moveNode *root, vector<int, int> moves) {

    return make_pair(int(), int());
}

pair<int, int> TeamNULLPlayer::move(Board b){
    pair<int,int> nextMove;
    vector<int, int> moves;
    moveNode* root;

    return nextMove;
}
*/
int main(int argc, const char * argv[])
{
    Board board;
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


    /*
     grid[0][0] = WHITE;
     grid[1][1] = WHITE;
     grid[2][2] = WHITE;
     grid[3][3] = WHITE;
     grid[1][0] = BLACK;
     grid[1][2] = BLACK;
     grid[2][3] = BLACK;
     grid[3][2] = BLACK;
     */

    vector<moveInfo> theMoves;
    theMoves = findMoves(1, blackPieces, whitePieces, board);

    for (int i = 0; i < theMoves.size(); i++) {
        cout << "Move #" << i + 1 << ": (" << theMoves[i].move.first << ", " << theMoves[i].move.second << ")" << endl;
        cout << "Score: " << theMoves[i].score << endl;
    }
    return 0;
}
