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

#include "TeamNULL.h"

const pair<int, int> adjMovs[8] = {make_pair(-1, 0), make_pair(-1, 1),
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

//*****************************************************************************
// name: findMoves                                                            *
// description: finds all on the moves for a particular color and returns it  *
//     as a set                                                               *
// return type: set<Move>                                                     *
// pre: the color integer is a valid value, the board is valid, and the       *
//     pieces/oppPiece vectors contain valid places on the board of           *
//     the proper color for each player.                                      *
// post: the pieces/oppPiece vectors and board is unchanged                   *
// returns: a set containing the possible moves for a player                  *
//*****************************************************************************
set<Move> findMoves(int color, vector<pair<int, int> > &oppPiece, Board &b) {
    set<Move> moves;
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }
    // for all opponents pieces
    for (int i = 0; i < oppPiece.size(); i++) {
        // for all directions
        for(int j = 0; j < 8; j++) {
            // make a move for each direction in adjMovs
            pair<int,int> move = make_pair(oppPiece[i].first +
                                           adjMovs[j].first,
                                           oppPiece[i].second +
                                           adjMovs[j].second);
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
                    pair<int, int> nextDir;
                    nextDir.first = move.first + adjMovs[k].first;
                    nextDir.second = move.second
                    + adjMovs[k].second;

                    while (nextDir.first >= 0 && nextDir.first < b.getRow() &&
                           nextDir.second >= 0 && nextDir.second < b.getCol() &&
                           b[nextDir.first][nextDir.second] == opponent) {
                        tempScore++;
                        tempBoard[nextDir.first][nextDir.second] = color;
                        nextDir = make_pair(nextDir.first + adjMovs[k].first,
                                            nextDir.second + adjMovs[k].second);
                    }
                    if (nextDir.first >= 0 &&
                        nextDir.first < b.getRow() &&
                        nextDir.second >= 0 &&
                        nextDir.second < b.getCol() &&
                        b[nextDir.first][nextDir.second] == color) {
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

//*****************************************************************************
// name: move                                                                 *
// description: finds a location to place a piece for the current move of     *
//     Othello given the board.                                               *
// return type: void                                                          *
// pre: the board information is valid and reflects the current state of the  *
//     game.                                                                  *
// post: the move reference passed is changed to the decided piece placement  *
// returns: nothing                                                           *
//*****************************************************************************
Move TeamNULL::move(Board b, pair<int,int> &move) {
    int color = getColor();
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }

    root = new moveNode;
    root->color = opponent;
    root->board = b;
    root->move = make_pair(-1, -1);
    for (int i = 0; i < b.getRow(); i++) {
        for (int j = 0; j < b.getCol(); j++) {
            if (b[i][j] == color) {
                root->pieces.push_back(make_pair(i, j));
            } else if (b[i][j] == opponent){
                root->oppPiece.push_back(make_pair(i, j));
            }
        }
    }

    set<Move> moves;
    moves = findMoves(color, root->oppPiece, b);

    if (!moves.empty()) {
        move = moves.begin()->position;
    } else {
        Move noMoves(make_pair(-1, -1), 0, b);
        return noMoves;
    }

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

