#include <iostream>
#include <deque>
#include <random>
#include <vector>

using namespace std;

class Player
{
private:
    string id;
    int currPosition;

public:
    Player(string id, int currPosition = 0)
    {
        this->id = id;
        this->currPosition = currPosition;
    }

    string getPlayerId()
    {
        return this->id;
    }

    int getPlayerCurrPosition()
    {
        return this->currPosition;
    }

    void setPlayerCurrPosition(int currPosition)
    {
        this->currPosition = currPosition;
    }
};

class Jump
{
private:
    int start;
    int end;

public:
    void setStartAndEnd(int start, int end)
    {
        this->start = start;
        this->end = end;
    }

    int getStart()
    {
        return start;
    }

    int getEnd()
    {
        return end;
    }
};

class Cell
{
private:
    Jump *jump;

public:
    Cell()
    {
        jump = nullptr;
    }

    void setJump(Jump *jump)
    {
        this->jump = jump;
    }

    Jump *getJump()
    {
        return jump;
    }
};

class Dice
{
public:
    int diceCount;
    int min = 1;
    int max = 6;

public:
    Dice(int diceCount)
    {
        this->diceCount = diceCount;
    }

    int rollDice()
    {
        int totalSum = 0;
        int diceUsed = 0;

        random_device rd;
        mt19937 gen(rd());

        uniform_int_distribution<> dist(min, max);

        while (diceUsed < diceCount)
        {
            totalSum += dist(gen);
            diceUsed++;
        }

        return totalSum;
    }
};

class Board
{
private:
    vector<vector<Cell>> cells;

public:
    Board(int boardSize, int numOfSnakes, int numOfLadder)
    {
        initializeCell(boardSize);
        addSnakesLadders(numOfSnakes, numOfLadder);
    }

    void initializeCell(int boardSize)
    {
        cells.resize(boardSize, vector<Cell>(boardSize));

        for (int i = 0; i < boardSize; i++)
        {
            for (int j = 0; j < boardSize; j++)
            {
                cells[i][j] = Cell();
            }
        }
    }

    void addSnakesLadders(int numOfSnakes, int numOfLadder)
    {
        random_device rd;
        mt19937 gen(rd());

        int maxPos = cells.size() * cells.size() - 1;

        uniform_int_distribution<> dist(1, maxPos);

        // Add Snakes
        while (numOfSnakes > 0)
        {
            int snakeHead = dist(gen);
            int snakeTail = dist(gen);

            if (snakeTail >= snakeHead)
            {
                continue;
            }

            Jump *snakeObj = new Jump();
            snakeObj->setStartAndEnd(snakeHead, snakeTail);

            Cell &cell = getCell(snakeHead);
            if (cell.getJump() != nullptr)
            {
                continue;
            }
            cell.setJump(snakeObj);

            numOfSnakes--;
        }

        // Add Ladders
        while (numOfLadder > 0)
        {
            int ladderStart = dist(gen);
            int ladderEnd = dist(gen);

            if (ladderStart >= ladderEnd)
            {
                continue;
            }

            Jump *snakeObj = new Jump();
            snakeObj->setStartAndEnd(ladderStart, ladderEnd);

            Cell &cell = getCell(ladderStart);
            if (cell.getJump() != nullptr)
            {
                continue;
            }
            cell.setJump(snakeObj);

            numOfLadder--;
        }
    }

    Cell &getCell(int playerPosition)
    {
        int boardRow = playerPosition / cells.size();
        int boardColumn = playerPosition % cells.size();

        return cells[boardRow][boardColumn];
    }

    int getBoardSize()
    {
        return cells.size();
    }
};

class Game
{
private:
    Board board;
    Dice dice;
    deque<Player> playersList;
    Player *winner;

public:
    Game(int numOfPlayers) : board(10, 5, 4), dice(1), winner(nullptr)
    {
        addPlayers(numOfPlayers);
    }

    void addPlayers(int numPlayers)
    {
        for (int i = 1; i <= numPlayers; i++)
        {
            playersList.emplace_back(
                "Player-" + to_string(i),
                0);
        }
    }

    Player &findPlayerTurn()
    {
        playersList.push_back(playersList.front());
        playersList.pop_front();

        return playersList.back();
    }

    int jumpCheck(int playerNewPosition)
    {
        int lastCell = board.getBoardSize() * board.getBoardSize() - 1;

        if (playerNewPosition > lastCell)
        {
            return playerNewPosition;
        }

        Cell &cell = board.getCell(playerNewPosition);

        if (cell.getJump() != nullptr && cell.getJump()->getStart() == playerNewPosition)
        {
            string jumpBy =
                (cell.getJump()->getStart() < cell.getJump()->getEnd())
                    ? "Ladder"
                    : "Snake";

            cout << "[+] Jump done by: " << jumpBy << endl;

            return cell.getJump()->getEnd();
        }

        return playerNewPosition;
    }

    void startGame()
    {
        while (winner == nullptr)
        {
            Player &playerTurn = findPlayerTurn();

            cout << "Player turn: "
                 << playerTurn.getPlayerId()
                 << " current position is: "
                 << playerTurn.getPlayerCurrPosition()
                 << endl;

            int diceNumber = dice.rollDice();

            int playerNewPosition = playerTurn.getPlayerCurrPosition() + diceNumber;

            playerNewPosition =
                jumpCheck(playerNewPosition);

            playerTurn.setPlayerCurrPosition(playerNewPosition);

            cout << "Player turn: "
                 << playerTurn.getPlayerId()
                 << " new Position is: "
                 << playerNewPosition
                 << endl;

            if (playerNewPosition >= board.getBoardSize() * board.getBoardSize() - 1)
            {
                winner = &playerTurn;
            }
        }

        cout << "\n===> The Winner is: "
             << winner->getPlayerId() << endl;
    }
};

int main()
{
    int n = 2;

    // cout << "Enter number of players: ";
    // cin >> n;

    Game game(n);
    game.startGame();

    return 0;
}