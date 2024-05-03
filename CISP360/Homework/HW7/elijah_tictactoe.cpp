// main.cpp
// elijah wilson
// 05/04/2024

#include <ctime>
#include <fstream>
#include <iostream>
#include <iomanip>
#include <limits>
#include <vector>

// class prototype
class TicTacToe
{
    public:
        // constructor
        TicTacToe();

        // public method prototypes
        void startMenu();
        void logActivity(const std::string &message);

    private:
        // private attributes
        char gridSpaces[3][3] = {{' ', ' ', ' '}, {' ', ' ', ' '}, {' ', ' ', ' '}}; // aggregate initialization
        bool gameOver = false;
        char currentPlayer = ' ';
        char startingPlayer = ' ';
        int gameCount = -1; // since we increment at start of each game INCLUDING initial game, we start at -1
        std::string playerXName;
        std::string playerOName;
        int lastMoveRow = -1;
        int lastMoveCol = -1;
        std::vector<std::string> ledger; // vector to store move ledger

        // private method prototypes
        void startGame(const std::string &humanName, const std::string &robotName);
        void displayBoard();
        void displayInstructions();
        void checkTurn();
        bool checkWin();
        bool checkDraw();
        void updateBoard(int row, int col, char player);
        void switchPlayer();
        bool isValidMove(int row, int col);
        void promptMove();
        void playAgain();
        void updateLedger(const std::string &playerName, int position);
        void initializeGameParameters();
};

// funciton prototypes
void clearTerminal();
void programGreeting();


int main()
{
    // create TicTacToe object
    TicTacToe ttt;

    // log main function
    ttt.logActivity(__func__ + std::string("(); ") + std::string(""));

    clearTerminal();
    programGreeting();

    // call startMenu method
    ttt.startMenu();

    return 0;
}


// constructor (not required in this case but maybe it helps my plaigarism score lol)
TicTacToe::TicTacToe() = default;

void TicTacToe::updateBoard(const int row, const int col, const char player)
{
    logActivity(__func__ + std::string("(); ") + std::string("Updating board."));
    gridSpaces[row][col] = player;
    lastMoveRow = row; // update last move row
    lastMoveCol = col; // update last move column

    std::string playerName = (player == 'X') ? playerXName : playerOName;
}

// Speciﬁcation B1 - Start Menu
void TicTacToe::startMenu()
{
    logActivity(__func__ + std::string("(); ") + std::string("Drawing start menu."));

    std::string humanName, robotName;
    int choice;

    do
    {
        std::cout << "1. Explain Game\n";
        std::cout << "2. Play\n";
        std::cout << "3. Quit\n" << "\n";

        std::cout << "Enter your choice: ";
        std::cin >> choice;

        logActivity(__func__ + std::string("(); ") + std::string("Prompting for input (1, 2 or 3)"));
        switch (choice)
        {
            // explanation
            case 1:
                clearTerminal();
                logActivity("User input: 1 - Displaying explanation.");
                std::cout << "Tic Tac Toe is a two-player game where each player takes turns marking\n";
                std::cout << "a space in a 3x3 grid. The player who succeeds in placing three of their\n";
                std::cout << "marks in a horizontal, vertical, or diagonal row wins the game. (source: google)\n" << "\n";
                break;

            // play
            case 2:
                clearTerminal();
                logActivity("User input: 2 - Play game.");
                std::cout << "Enter your name: ";
                std::cin >> humanName;
                std::cout << "Enter a name for the robot: ";
                std::cin >> robotName;
                startGame(humanName, robotName);
                break;

            // quit
            case 3:
                logActivity("User input: 3 - Quitting program.");
                std::cout << "Goodbye!\n";
                return;

            // default
            default:
                logActivity(__func__ + std::string("(); ") + std::string("Invalid user input") + std::to_string(choice));
                std::cout << "Invalid choice. Please try again.\n";
                break;
        }
    }
    //Speciﬁcation B2 - Valid Menu Choices
    // while the choice isn't to quit, keep prompting.
    while (choice != 3);
}

void TicTacToe::startGame(const std::string &humanName, const std::string &robotName)
{
    logActivity(__func__ + std::string("(); ") + std::string("Started game with players: ") + humanName + ", " + robotName);

    // increment game count at the start of each game
    gameCount++;

    // flush any previous data
    initializeGameParameters();

    playerXName = humanName;
    playerOName = robotName;

    // Speciﬁcation C1 - Random Start
    srand(time(0)); // randomly pick who starts
    const int start = rand() % 2; // generate random int; either 0 or 1
    startingPlayer = (start == 0) ? 'X' : 'O'; // store the starting player
    currentPlayer = startingPlayer;

    std::cout << ((currentPlayer == 'X') ? playerXName : playerOName) << " moves first.\n";
    logActivity(
        "Game started. " + std::string((currentPlayer == 'X') ? playerXName : playerOName) + " moves first.");

    do
    {
        displayBoard();
        displayInstructions();
        promptMove();

        if (checkWin())
        {
            gameOver = true;
            displayBoard(); // display the final board state BEFORE announcing
            std::cout << ((currentPlayer == 'X') ? playerXName : playerOName) << " wins!\n\n";
            break; // exit the loop if a win is detected
        }

        if (checkDraw())
        {
            gameOver = true;
            displayBoard(); // display the final board state BEFORE announcing
            std::cout << "It's a draw!\n\n";
            break; // exit the loop if a draw is detected
        }
        switchPlayer();
    }
    while (!gameOver);

    // Specification A2 - Play Again Option
    playAgain();
}

void TicTacToe::initializeGameParameters()
{
    logActivity(__func__ + std::string("(); ") + std::string("Resetting game."));

    // reset gridSpaces to empty
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            gridSpaces[i][j] = ' ';
        }
    }

    // reset game state variables
    gameOver = false;
    currentPlayer = ' ';
    lastMoveRow = -1;
    lastMoveCol = -1;

    // clear the move ledger
    ledger.clear();
}


void TicTacToe::playAgain()
{
    logActivity(__func__ + std::string("(); ") + std::string("Prompting to play again."));

    char choice;
    bool validInput = false;

    do
    {
        std::cout << "Do you want to play again? (y/n): ";
        std::cin >> choice;

        // convert choice to lowercase for case-insensitive comparison
        choice = std::tolower(choice);

        if (choice == 'y')
        {
            logActivity("User chose 'y'");
            gameOver = false;
            startGame(playerXName, playerOName);
            validInput = true;
        } else if (choice == 'n')
        {
            logActivity("User chose 'n'");
            std::cout << "Goodbye!\n\n";
            validInput = true;
        } else
        {
            std::cout << "Invalid input. Please choose either 'y' or 'n'.\n";
        }
    } while (!validInput);
}


// Speciﬁcation C2 - Simple Display
void TicTacToe::displayBoard()
{
    logActivity(__func__ + std::string("(); ") + std::string("called."));

    clearTerminal();

    // i know `this->` is assumed when working in class scope but i just wanted to use it somewhere lol
    int moveNumber = this->gameCount;

    // Specification A3 - Games Played Counter
    logActivity(__func__ + std::string("(); ") + std::string("Drawing game count."));
    std::cout << "\nGame's finished: " << gameCount << "\n\n"; // display game count

    // display who goes first
    logActivity(__func__ + std::string("(); ") + std::string("Displaying who goes first."));
    std::cout << ((startingPlayer == 'X') ? playerXName : playerOName) << " goes first.\n\n";

    logActivity(__func__ + std::string("(); ") + std::string("Drawing grid."));
    for (int i = 0; i < 3; ++i)
    {
        std::cout << " " << " ";
        for (int j = 0; j < 3; ++j)
        {
            std::cout << " " << gridSpaces[i][j] << " ";
            if (j < 2)
            {
                std::cout << "|";
            }
            moveNumber++;
        }
        std::cout << "\n";
        if (i < 2)
        {
            std::cout << "  ---|---|---\n";
        }
    }
    std::cout << std::endl;

    // display move history
    logActivity(__func__ + std::string("(); ") + std::string("Displaying move ledger."));
    std::cout << "Ledger:\n";

    // range-based for-loop to spice it up
    for (const auto &entry: ledger)
    {
        std::cout << entry << "\n";
    }
    std::cout << "\n";
}

void TicTacToe::displayInstructions()
{
    logActivity(__func__ + std::string("(); ") + std::string("Displaying instructions."));
    std::cout << "Enter the number of a cell in which to place your X.\n\n";
}

void TicTacToe::promptMove()
{
    logActivity(__func__ + std::string("(); ") + std::string("Prompting move."));

    if (currentPlayer == 'X')
    {
        int position;
        std::cout << playerXName << "'s turn (choose position 1-9): ";

        while (!(std::cin >> position) || position < 1 || position > 9)
        {
            logActivity(__func__ + std::string("(); ") + std::string("Invalid move input. ") + std::to_string(position) + std::string(" is not in range 1-9"));

            std::cout << "Invalid input. Please enter an integer between 1 and 9: ";
            std::cin.clear(); // clear the error flags
            std::cin.ignore(std::numeric_limits<std::streamsize>::max(), '\n'); // discard the input buffer
        }

        position--; // adjustment for indexing
        const int row = position / 3;
        const int col = position % 3;
        if (isValidMove(row, col))
        {
            logActivity(__func__ + std::string("(); ") + std::string("Valid move."));

            updateBoard(row, col, currentPlayer);
            updateLedger(playerXName, position + 1);
        }
        else
        {
            logActivity(__func__ + std::string("(); ") + std::string("Invalid move, reprompting."));

            std::cout << "Invalid move. The spot is already occupied. Please choose another position.\n";
            promptMove(); // reprompt if the move is invalid
        }
    }
    else
    {
        // random move for mr robot man
        int row, col;
        do
        {
            row = rand() % 3;
            col = rand() % 3;
        }
        while (!isValidMove(row, col));

        updateBoard(row, col, currentPlayer);
        updateLedger(playerOName, row * 3 + col + 1);
    }
}


bool TicTacToe::isValidMove(int row, int col)
{
    logActivity(__func__ + std::string("(); ") + std::string("Checking if move is valid."));

    // Speciﬁcation B3 – Range Check Move
    // check if the position is out of bounds
    if (row < 0 || row >= 3 || col < 0 || col >= 3)
    {
        return false;
    }

    // Specification A1 - Open Moves Only Check
    // check if the position is already occupied
    if (gridSpaces[row][col] != ' ')
    {
        return false;
    }

    return true;
}

void TicTacToe::checkTurn()
{
    logActivity(__func__ + std::string("(); ") + std::string("Checking who's turn it is."));

    std::cout << currentPlayer << "'s turn.\n";
}

bool TicTacToe::checkWin()
{
    // check for row win
    for (int i = 0; i < 3; ++i)
    {
        if (gridSpaces[i][0] == currentPlayer && gridSpaces[i][1] == currentPlayer && gridSpaces[i][2] == currentPlayer)
        {
            return true;
        }
    }

    // check for col win
    for (int i = 0; i < 3; ++i)
    {
        if (gridSpaces[0][i] == currentPlayer && gridSpaces[1][i] == currentPlayer && gridSpaces[2][i] == currentPlayer)
        {
            return true;
        }
    }

    // check for diag win
    if ((gridSpaces[0][0] == currentPlayer && gridSpaces[1][1] == currentPlayer && gridSpaces[2][2] == currentPlayer) ||
        (gridSpaces[0][2] == currentPlayer && gridSpaces[1][1] == currentPlayer && gridSpaces[2][0] == currentPlayer))
    {
        return true;
    }

    return false;
}


bool TicTacToe::checkDraw()
{
    logActivity(__func__ + std::string("(); ") + std::string("checking for draw."));

    // if any cell is still empty, the game is not a draw
    for (int i = 0; i < 3; ++i)
    {
        for (int j = 0; j < 3; ++j)
        {
            if (gridSpaces[i][j] == ' ')
            {
                return false;
            }
        }
    }
    logActivity(__func__ + std::string("(); ") + std::string("Game resulted in a draw."));
    std::cout << "It's a draw!\n";
    return true;
}

void TicTacToe::switchPlayer()
{
    logActivity(__func__ + std::string("(); ") + std::string("Switching player."));

    currentPlayer = currentPlayer == 'X' ? 'O' : 'X';
}

// Speciﬁcation C3 - Function Activity to Disk
void TicTacToe::logActivity(const std::string &message)
{
    std::ofstream logFile("log.txt", std::ios::app);
    if (logFile.is_open())
    {
        time_t now = time(0);
        tm *localTime = localtime(&now);
        logFile << std::put_time(localTime, "%Y-%m-%d %X") << " - " << message << std::endl;
        logFile.close();
    }
}

void TicTacToe::updateLedger(const std::string &playerName, int const position)
{
    logActivity(__func__ + std::string("(); ") + std::string("Updating ledger."));
    std::string const message = playerName + " played " + std::to_string(position);
    ledger.push_back(message);
}


void clearTerminal()
{
    TicTacToe log;
    log.logActivity(__func__ + std::string("(); ") + std::string("Clearing terminal window."));
#ifdef _WIN32
    system("cls");
#else
    system("clear");
#endif
}

void programGreeting()
{
    TicTacToe log;
    log.logActivity(__func__ + std::string("(); ") + std::string("Displaying greeting."));

    std::cout << "\nWelcome to my Tic Tac Toe program :)" << "\n";
    std::cout << "Author: Elijah Wilson" << "\n\n";
}
