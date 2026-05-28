#include <iostream>
#include <vector>
#include <deque>

using namespace std;

// ======================= PIECE TYPE =======================
enum class PieceType
{
    X,
    O
};

// ======================= PLAYING PIECE =======================
class PlayingPiece
{
protected:
    PieceType pieceType;

public:
    PlayingPiece(PieceType pieceType) : pieceType(pieceType) {}

    PieceType getPieceType() const { return pieceType; }

    virtual char getSymbol() const = 0;
    virtual ~PlayingPiece() = default;
};

class PlayingPieceX : public PlayingPiece
{
public:
    PlayingPieceX() : PlayingPiece(PieceType::X) {}
    char getSymbol() const override { return 'X'; }
};

class PlayingPieceO : public PlayingPiece
{
public:
    PlayingPieceO() : PlayingPiece(PieceType::O) {}
    char getSymbol() const override { return 'O'; }
};

// ======================= BOARD =======================
class Board
{
private:
    int size;
    vector<vector<PlayingPiece *>> grid;

public:
    Board(int size) : size(size)
    {
        grid.assign(size, vector<PlayingPiece *>(size, nullptr));
    }

    bool addPiece(int row, int col, PlayingPiece *piece)
    {
        if (row < 0 || col < 0 || row >= size || col >= size)
        {
            cout << "[ERROR] Position out of bounds. Valid range: 0 to " << size - 1 << endl;
            return false;
        }

        if (grid[row][col] != nullptr)
        {
            cout << "[ERROR] Cell already occupied. Try another." << endl;
            return false;
        }

        grid[row][col] = piece;
        return true;
    }

    bool isFull() const
    {
        for (int i = 0; i < size; i++)
            for (int j = 0; j < size; j++)
                if (grid[i][j] == nullptr)
                    return false;
        return true;
    }

    bool checkWinner(int row, int col, PieceType pieceType) const
    {
        bool rowMatch = true;
        bool colMatch = true;
        bool diagMatch = true;
        bool antiDiagMatch = true;

        for (int i = 0; i < size; i++)
        {
            if (grid[row][i] == nullptr || grid[row][i]->getPieceType() != pieceType)
                rowMatch = false;

            if (grid[i][col] == nullptr || grid[i][col]->getPieceType() != pieceType)
                colMatch = false;

            if (grid[i][i] == nullptr || grid[i][i]->getPieceType() != pieceType)
                diagMatch = false;

            if (grid[i][size - 1 - i] == nullptr || grid[i][size - 1 - i]->getPieceType() != pieceType)
                antiDiagMatch = false;
        }

        return rowMatch || colMatch || diagMatch || antiDiagMatch;
    }

    void printBoard() const
    {
        cout << endl;

        // Column index header
        cout << "   ";
        for (int j = 0; j < size; j++)
            cout << " " << j << "  ";
        cout << endl;

        for (int i = 0; i < size; i++)
        {
            cout << " " << i << " "; // Row index
            for (int j = 0; j < size; j++)
            {
                char symbol = (grid[i][j] != nullptr) ? grid[i][j]->getSymbol() : ' ';
                cout << " " << symbol << " ";
                if (j < size - 1)
                    cout << "|";
            }
            cout << endl;

            if (i < size - 1)
            {
                cout << "   ";
                for (int j = 0; j < size; j++)
                {
                    cout << "---";
                    if (j < size - 1)
                        cout << "+";
                }
                cout << endl;
            }
        }

        cout << endl;
    }

    int getSize() const { return size; }
};

// ======================= PLAYER =======================
class Player
{
private:
    string name;
    PlayingPiece *playingPiece;

public:
    Player(const string &name, PlayingPiece *playingPiece)
        : name(name), playingPiece(playingPiece) {}

    string getName() const { return name; }
    PlayingPiece *getPlayingPiece() const { return playingPiece; }
};

// ======================= TIC TAC TOE GAME =======================
class TicTacToeGame
{
private:
    deque<Player *> players;
    Board *board;
    Player *winner;

public:
    TicTacToeGame(int boardSize, vector<Player *> playerList)
        : board(new Board(boardSize)), winner(nullptr)
    {
        for (Player *p : playerList)
            players.push_back(p);
    }

    ~TicTacToeGame()
    {
        delete board;
    }

    string startGame()
    {
        cout << "\n===== TIC TAC TOE =====\n";

        while (true)
        {
            Player *currPlayer = players.front();
            players.pop_front();

            board->printBoard();

            if (board->isFull())
                return "Draw";

            int row, col;
            cout << "Player [" << currPlayer->getName()
                 << " (" << currPlayer->getPlayingPiece()->getSymbol()
                 << ")] - Enter row and column: ";
            cin >> row >> col;

            bool validMove = board->addPiece(row, col, currPlayer->getPlayingPiece());

            if (!validMove)
            {
                // Give turn back to same player
                players.push_front(currPlayer);
                continue;
            }

            players.push_back(currPlayer);

            if (board->checkWinner(row, col, currPlayer->getPlayingPiece()->getPieceType()))
            {
                board->printBoard();
                winner = currPlayer;
                return "Winner";
            }
        }
    }

    Player *getWinner() const { return winner; }
};

// ======================= MAIN =======================
int main()
{
    // Setup pieces
    PlayingPiece *pieceX = new PlayingPieceX();
    PlayingPiece *pieceO = new PlayingPieceO();

    // Setup players
    Player *player1 = new Player("Ashish", pieceX);
    Player *player2 = new Player("Himanshu", pieceO);

    // Start game on a 3x3 board
    TicTacToeGame game(3, {player1, player2});

    string result = game.startGame();

    if (result == "Winner")
        cout << "\n🏆 Winner is: " << game.getWinner()->getName() << "!\n";
    else
        cout << "\n🤝 It's a Draw!\n";

    // Cleanup
    delete player1;
    delete player2;
    delete pieceX;
    delete pieceO;

    return 0;
}