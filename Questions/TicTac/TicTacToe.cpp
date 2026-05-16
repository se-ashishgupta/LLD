#include <iostream>
#include <map>
#include <mutex>
#include <chrono>

using namespace std;

enum class PieceType
{
    X,
    O
};

class PlayingPiece
{
public:
    PieceType pieceType;

    PlayingPiece(PieceType pieceType)
    {
        this->pieceType = pieceType;
    }

    virtual char getPieceType() = 0;
};

class PlayingPieceX : public PlayingPiece
{
public:
    PlayingPieceX() : PlayingPiece(PieceType::X) {}

    char getPieceType() override
    {
        return 'X';
    }
};

class PlayingPieceO : public PlayingPiece
{
public:
    PlayingPieceO() : PlayingPiece(PieceType::O) {}

    char getPieceType() override
    {
        return 'O';
    }
};

// Board

class Board
{
public:
    int size;
    vector<vector<PlayingPiece *>> board;

    Board(int size)
    {
        this->size = size;
        board.resize(
            size,
            vector<PlayingPiece *>(size, nullptr));
    }

    bool addPiece(int row, int column, PlayingPiece *playingPiece)
    {
        if (row >= size || column >= size)
        {
            return false;
        }

        if (board[row][column] != nullptr)
        {
            return false;
        }

        board[row][column] = playingPiece;
        return true;
    }

    vector<pair<int, int>> getFreeCells()
    {
        vector<pair<int, int>> freeCells;

        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] == nullptr)
                {
                    freeCells.push_back({i, j});
                }
            }
        }

        return freeCells;
    }

    void printBoard()
    {
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                if (board[i][j] != nullptr)
                {
                    cout << board[i][j]->getPieceType() << " ";
                }
                else
                {
                    cout << "  ";
                }

                cout << " | ";
            }

            cout << endl;
        }
    }
};

class Player
{
private:
    string name;
    PlayingPiece *playingPiece;

public:
    Player(string name, PlayingPiece *playingPiece)
    {
        this->name = name;
        this->playingPiece = playingPiece;
    }

    string getName()
    {
        return name;
    }

    void setName(string name)
    {
        this->name = name;
    }

    PlayingPiece *getPlayingPiece()
    {
        return playingPiece;
    }

    void setPlayingPiece(PlayingPiece *playingPiece)
    {
        this->playingPiece = playingPiece;
    }
};

class TicTacToeGame
{
public:
    deque<Player *> players;
    Board *gameBoard;
    Player *winner;

    // for Two players only
    void initializeGame()
    {
        PlayingPieceX *crossPiece = new PlayingPieceX();

        Player *player1 = new Player("Ashish", crossPiece);

        PlayingPieceO *oPiece = new PlayingPieceO();

        Player *player2 = new Player("Himanshu", oPiece);

        players.push_back(player1);
        players.push_back(player2);

        gameBoard = new Board(3);
    }

    string startGame()
    {
        bool noWinner = true;

        while (noWinner)
        {
            Player *currPlayer = players.front();

            players.pop_front();

            gameBoard->printBoard();

            vector<pair<int, int>> freeSpace = gameBoard->getFreeCells();

            if (freeSpace.empty())
            {
                noWinner = false;
                continue;
            }

            int row, column;
            cout << "Player: " << currPlayer->getName() << " Enter row and column: " << endl;
            cin >> row >> column;

            bool isValidMove = gameBoard->addPiece(row, column, currPlayer->getPlayingPiece());

            if (!isValidMove)
            {
                cout << "Invalid Move" << endl;
                players.push_front(currPlayer);
                continue;
            }

            players.push_back(currPlayer);

            bool isWinner = checkForWinner(row, column, currPlayer->getPlayingPiece()->pieceType);

            if (isWinner)
            {
                gameBoard->printBoard();

                winner = currPlayer;

                return "Winner";
            }
        }

        return "Draw";
    };

    bool checkForWinner(
        int row,
        int column,
        PieceType pieceType)
    {
        bool rowMatch = true;
        bool columnMatch = true;
        bool diagonalMatch = true;
        bool antiDiagonalMatch = true;

        // Check Row
        for (int i = 0; i < gameBoard->size; i++)
        {
            if (gameBoard
                        ->board[row][i] ==
                    nullptr ||

                gameBoard
                        ->board[row][i]
                        ->pieceType !=
                    pieceType)
            {
                rowMatch = false;
                break;
            }
        }

        // Check Column
        for (int i = 0; i < gameBoard->size; i++)
        {
            if (gameBoard
                        ->board[i][column] ==
                    nullptr ||

                gameBoard
                        ->board[i][column]
                        ->pieceType !=
                    pieceType)
            {
                columnMatch = false;
                break;
            }
        }

        // Check Diagonal
        for (int i = 0; i < gameBoard->size; i++)
        {
            if (gameBoard
                        ->board[i][i] ==
                    nullptr ||

                gameBoard
                        ->board[i][i]
                        ->pieceType !=
                    pieceType)
            {
                diagonalMatch = false;
                break;
            }
        }

        // Check Anti-Diagonal
        for (int i = 0,
                 j = gameBoard->size - 1;

             i < gameBoard->size;

             i++, j--)
        {
            if (gameBoard
                        ->board[i][j] ==
                    nullptr ||

                gameBoard
                        ->board[i][j]
                        ->pieceType !=
                    pieceType)
            {
                antiDiagonalMatch = false;
                break;
            }
        }

        return rowMatch ||
               columnMatch ||
               diagonalMatch ||
               antiDiagonalMatch;
    }
};

int main()
{
    TicTacToeGame game;

    game.initializeGame();

    string result = game.startGame();

    if (result == "Winner")
    {
        cout << "Winner is: " << game.winner->getName() << endl;
    }
    else
    {
        cout << "Game Draw\n";
    }

    return 0;
}