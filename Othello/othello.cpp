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

int main(int argc, const char * argv[])
{
    
    return 0;
}

struct moveNode {
    moveNode *parent;
    vector<moveNode> children;
    int score;
    bool max;
    pair<int, int> move;
    moveNode(int s, bool m){
        score = s;
        max = m;
    }
};


void findMoves(int color, vector<pair<int, int> > &blackMoves, vector<pair<int, int> > &whiteMoves, Board b) {
    vector<pair<int, int> > *opponentsMoves;
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
        opponentsMoves = &blackMoves;
    } else {
        opponent = WHITE;
        opponentsMoves = &whiteMoves;
    }

    for (int i = 0; i < opponentsMoves->size(); i++) {
        for(int j = 0; j < 8; < j++) {
            pair<int,int> move = (*opponentsMoves)[j] + enumNum[j];
            if (move == OPEN) {
                if (i > 0) {
                    if (j > 0) {
                        if (b[i - 1][j - 1] == opponent);
                    }
                    if (b[i - 1][j] == opponent);
                    if (j < b.getCol() - 1) {
                        if (b[i - 1][j + 1]) == opponent;
                    }
                }
                if (i < b.getRow() - 1) {
                    if (j > 0) {

                    }
                    if (j < b.getCol() - 1) {
                        
                    }
                }
                if (j > 0) {

                }
                if (j < b.getCol() - 1) {
                    
                }
            }
        }
    }
    return;
}

pair<int, int> generateTree(moveNode *root, vector<int, int> moves) {

    return make_pair(int(), int());
}

pair<int, int> TeamNULLPlayer::move(Board b){
    pair<int,int> nextMove;
    vector<int, int> moves;
    moveNode* root;

    return nextMove;
}
