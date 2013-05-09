/******************************************************************************
 Author: Team NULL
 Title : Othello AI
 Description: This algorithm determines the optimal moves for a game of
 Othello. While this algorithm doesn't solve the game of Othello (since
 right now, Othello is considered an unsolved game), it implements a
 strategy which will calculate winning moves for the game. We use a strategy
 that limits the available moves of the opponent, while maximizing our
 available moves at the end of the game. We take into account special moves
 such as corner pieces, which are always the best move if available.
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
set<Move> findMoves(int color, pair<int, int> &realMove,
                    vector<pair<int, int> > const &oppPiece, Board &b) {
    set<Move> moves;
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }
    // for all opponents pieces
    for (int piece = 0; piece < oppPiece.size(); piece++) {
        // for all directions
        for(int dir1 = 0; dir1 < 8; dir1++) {
            // make a move for each direction in adjMovs
            pair<int,int> move = make_pair(oppPiece[piece].first +
                                           adjMovs[dir1].first,
                                           oppPiece[piece].second +
                                           adjMovs[dir1].second);
            // if that move is on the board and is open
            if (move.first >= 0 && move.first < b.getRow() &&
                move.second >= 0 && move.second < b.getCol() &&
                b[move.first][move.second] == OPEN) {
                // keep track of score
                int score = 0;
                // for all directions
                for (int dir2 = 0; dir2 < 8; dir2++) {
                    // keep track of score for each direction
                    int dirScore = 0;
                    pair<int, int> nextDir;
                    nextDir.first = move.first + adjMovs[dir2].first;
                    nextDir.second = move.second + adjMovs[dir2].second;

                    while (nextDir.first >= 0 && nextDir.first < b.getRow() &&
                           nextDir.second >= 0 && nextDir.second < b.getCol() &&
                           b[nextDir.first][nextDir.second] == opponent) {
                        dirScore++;
                        nextDir = make_pair(nextDir.first + adjMovs[dir2].first,
                                            nextDir.second + adjMovs[dir2].second);
                    }
                    if (nextDir.first >= 0 &&
                        nextDir.first < b.getRow() &&
                        nextDir.second >= 0 &&
                        nextDir.second < b.getCol() &&
                        b[nextDir.first][nextDir.second] == color) {
                        score += dirScore;
                    }
                }
                // if the move is a valid move (it took an opponents piece)
                if (score > 0) {
                    int cols = b.getCol();
                    int rows = b.getRow();
                    // if the move is a corner spot, set to highest priority
                    if ((move.first == 0 && move.second == 0) ||
                        (move.first == 0 && move.second == cols - 1) ||
                        (move.first == rows - 1 && move.second == 0) ||
                        (move.first == rows - 1 && move.second == cols - 1)) {
                        score = -(cols * rows);
                        realMove = move;
                    }
                    // if the move is the piece diagonal to the corner piece,
                    // set to lowest priority
                    else if ((move.first == 1 && move.second == 1) ||
                             (move.first == 1 && move.second == cols - 2) ||
                             (move.first == rows - 2 && move.second == 1) ||
                             (move.first == rows - 2 && move.second == cols - 2)) {
                        score = (cols * rows);
                    }

                    // if the move is adjacent to a corner spot and the corner
                    // spot has a piece in it, prioritize the move as high
                    // if the corner spot is open, prioritize to low
                    else if (move.first == 0 && move.second == 1) {
                        if (b[0][0] == OPEN) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == 0 && move.second == cols - 2) {
                        if (b[0][cols-1] == OPEN) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == rows - 1 && move.second == 1) {
                        if (b[rows-1][0] == OPEN) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == rows - 1 && move.second == cols - 2){
                        if (b[rows-1][cols-1] == OPEN) score = 3*rows;
                        else score = 0;
                    }

                    else if (move.first == 1 && move.second == 0) {
                        if (b[0][0] == OPEN) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == 1 && move.second == cols - 1) {
                        if (b[0][cols-1] == OPEN) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == rows - 2 && move.second == 0) {
                        if (b[rows-1][0] == OPEN) score = 3*rows;
                        else score = 0;
                    }
                    else if (move.first == rows - 2 && move.second == cols - 1){
                        if (b[rows-1][cols-1] == OPEN) score = 3*rows;
                        else score = 0;
                    }

                    // if the move is an edge move, prioritize it to high
                    else if (move.first == 0 || move.first == rows - 1 ||
                             move.second == 0 || move.second == cols - 1) {
                        score = 0;
                    }
                    else {
                        realMove = move;
                    }

                    moves.insert(Move(move, score));
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
void TeamNULL::move(Board b, pair<int,int> &move) {
    int color = getColor();
    int opponent;
    if (color == WHITE) {
        opponent = BLACK;
    } else {
        opponent = WHITE;
    }

    vector<pair<int, int> > oppPieces;

    for (int i = 0; i < b.getRow(); i++) {
        for (int j = 0; j < b.getCol(); j++) {
            if (b[i][j] == opponent){
                oppPieces.push_back(make_pair(i, j));
            }
        }
    }

    set<Move> moves = findMoves(color, move, oppPieces, b);

    if (!moves.empty()) {
        move = moves.begin()->position;
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
        player1.move(board, move);
        // board = moveObj.board;
        // printBoard(board);
        player2.move(board, move);
        // board = moveObj.board;
        // printBoard(board);
    }

    return 0;
}

