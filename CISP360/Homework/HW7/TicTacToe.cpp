// TicTacToe.cpp -- Assignment 6
// 4/21/2024
// John Glenn
#include <stack>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
using namespace std;

// Global Variables
const string F_START = "Started";
const string F_END = "Ended";
const string FG_RED = "\033[1;31m";
const string LOG_FILE = "Log.txt"; 
const string PROGRAM_NAME = "TikTacToe.cpp";
const string PROGRAM_AUTHOR = "John Glenn";
const string RST = "\033[0m";

// Function Prototypes
void announceFunction(string, string);
void ProgramGreeting();

// Class Definitions
class TicTacToe{
    private:
        const string EX[6] = {" __  __ "," \\ \\/ / ","  \\  /  ","  /  \\  "," /_/\\_\\ ","        "};
        const string OH[6] = {"  ____  "," / __ \\ "," ||  || "," ||__|| "," \\____/ ","        "};
        const int decoder[9][2] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
        const int TILE_WIDTH = 8;
        const int TILE_HEIGHT = 5;
        const char CROSS = '+';
        const char HOR   = '-';
        const char VER   = '|';
        int row, col, setTiles, gamesPlayed, choice, tally, cntTile;
        stack<string> winStack, tempStack;
        string strChoice, prompt;
        bool playAgain = true;
    public:
        TicTacToe(){
            announceFunction(__func__,F_START);
            resetBoard();
            announceFunction(__func__,F_END);
        }
        enum tileStatus  { UNSET, X, O };
        tileStatus gameBoard[3][3];
        tileStatus PLAYER1 = X;
        tileStatus PLAYER2 = O;
        tileStatus checkBoard(){
            //Check Rows
            for (int i = 0; i < 3; i++){
                tally = gameBoard[i][0] * gameBoard[i][1] * gameBoard[i][2];
                if (tally != UNSET){
                    switch (tally)
                    {
                    case 1:
                        return X;
                        break;
                    
                    case 8:
                        return O;
                        break;
                    }
                }
            }
            
            //Check Columns
            tally = 0;
            for (int i = 0; i < 3; i++){
                tally = gameBoard[0][i] * gameBoard[1][i] * gameBoard[2][i];
                if (tally != UNSET){
                    switch (tally)
                    {
                    case 1:
                        return X;
                        break;
                    
                    case 8:
                        return O;
                        break;
                    }
                }
            }
            //Check Diagonals
            tally = 0;
            tally = gameBoard[0][0] * gameBoard[1][1] * gameBoard[2][2];
            if (tally != UNSET){
                switch (tally){
                    case 1:
                        return X;
                        break;
                    case 8:
                        return O;
                        break;
                };
            };
            tally = 0;
            tally = gameBoard[0][2] * gameBoard[1][1] * gameBoard[2][0];
            if (tally != UNSET){
                switch (tally){
                    case 1:
                        return X;
                        break;
                    case 8:
                        return O;
                        break;
                };
            };
        return UNSET;
        }
        void resetBoard(){
            announceFunction(__func__,F_START);
            setTiles = 0;
            for (int r = 0; r < 3; r++){
                for (int c = 0; c < 3; c++){
                    gameBoard[r][c] = UNSET;
                };    
            };
            announceFunction(__func__,F_END);
        };
        bool set(int cell, tileStatus mark){
            announceFunction(__func__,F_START);
            if (!isSet(cell)){
                gameBoard[decoder[cell-1][0]][decoder[cell-1][1]] = mark;
                setTiles++;
                announceFunction(__func__,F_END);
                return true;
            }else{
                // Specification A1 - Open Moves Only Check
                cout << FG_RED << "Invalid Input: Space is already taken!" << RST << endl;
                announceFunction(__func__,F_END);
                return false;
            }  
        };
        int promptIntInRange(string prompt, int min, const int max){
            announceFunction(__func__, F_START);
            int intIn = 0;

            do{
                cout << prompt;
                cin >> intIn;
                //Speciﬁcation B2 - Valid Menu Choices
                if (intIn < min || intIn > max) cout << FG_RED << "Invalid Input! Number must be between " << min << " and " << max << RST << endl;
            }while (intIn < min || intIn > max);
            announceFunction(__func__, F_END);
            return intIn;
        }
        // Speciﬁcation C2 - Simple Display
        void printBoard(){
            announceFunction(__func__,F_START);
            cntTile = 1;
            for (int r = 0; r < 3; r++){
                for (int l = 0; l <= TILE_HEIGHT; l++){
                    for (int c = 0; c < 3; c++){

                        if (gameBoard[r][c] == X){
                            if (l == TILE_HEIGHT/2) cntTile++;
                            cout << EX[l];
                        }else if (gameBoard[r][c] == O){
                            if (l == TILE_HEIGHT/2) cntTile++;
                            cout << OH[l];
                        }else{
                            if (l == TILE_HEIGHT/2){
                                cout << setw(TILE_WIDTH/2) << "{" << cntTile << "}" << string(TILE_WIDTH/3, ' ');
                                cntTile++;
                            }else{
                                cout << string(TILE_WIDTH, ' ');
                            }
                        };
                        if ((c+1)%3 == 0){
                            cout << endl;
                        }else{
                            cout << VER;
                        };
                        
                    };
                };
                if ( r < 2) cout << string(TILE_WIDTH,HOR) <<  CROSS << string(TILE_WIDTH,HOR) << CROSS << string(TILE_WIDTH,HOR) << endl;
            };
            announceFunction(__func__,F_END);
        };
        void printWelcome(){
            announceFunction(__func__,F_START);
            cout << setw(27) << "Welcome to TicTacToe!\n\n";
            announceFunction(__func__,F_END);
        };
        void rules(){
            announceFunction(__func__,F_START);
            cout << "\n\nRULES\n=====\n\n1. The computer plays 'O'\n2. The player plays 'X'\n3. First player is random\n"
                 << "4. Get 3 in a row to win!\n\n";
            announceFunction(__func__,F_END);
        };
        void userTurn(){
            printBoard();
            do{
            prompt = "What space would you like to use? ";
            // Speciﬁcation B3 – Range Check Move
            choice = promptIntInRange(prompt, 1, 9);
            }while(!set(choice, X));
        };
        void computerTurn(){
            printBoard();
            srand(time(nullptr));
            do{
                choice = (int)(rand()%9+1);
            }while(isSet(choice));
            
            set(choice, O);
        };
        bool isSet(int cell){
            row = decoder[cell-1][0];
            col = decoder[cell-1][1];
            announceFunction(__func__,F_START);
            if (gameBoard[row][col] == UNSET){
                announceFunction(__func__,F_END);
                return false;
            }
                return true;
        }
        string play(){
            // Speciﬁcation C1 - Random Start
            int player = coinFlip();
            switch (player)
            {
            case 1:
                cout << "You make the first move!\n";
                break;
            case 0:
                cout << "The computer makes the first move!\n";
                break;
            }

            while (setTiles <= 9){
             switch (player)
            {
            case true:
                cout << "Users turn!\n";
                userTurn();
                break;
            case false:
                computerTurn();
                cout << "Computers turn!\n";
                break;
            }
            switch (checkBoard())
            {
            case X:
                return "User";
                break;
            case O:
                return "Computer";
                break;            
            default:
                break;
            }
            player = !player;
            }

            return "Computer";
        }
        bool promptReplay(){
            announceFunction(__func__,F_START);
            while (true){
                // Specification A2 - Play Again Option
                cout << "Do you want to play again? [Y/N] ";
                cin >> strChoice;
                strChoice = strToUpper(strChoice);
                if (strChoice == "Y"){
                    announceFunction(__func__,F_END);
                    return true;
                }else if (strChoice == "N"){
                    announceFunction(__func__,F_END);
                    return false;
                }else{
                    //Speciﬁcation B2 - Valid Menu Choices
                    cout << FG_RED << "Invalid Input. Try again...\n" << RST;
                }
            }
            
        };
        string strToUpper(string inStr){
            announceFunction(__func__,F_START);
            string outStr = "";

            for (int character = 0; character < inStr.size(); character++){
                outStr += toupper(inStr[character]);
            }
            announceFunction(__func__,F_END);
            return outStr;
        };
        bool coinFlip(){
            std::srand(time(nullptr));  // Seed with current time
            return (int)rand()%2;
        };
        void start(){
            announceFunction(__func__,F_START);
            printWelcome();
            printBoard();
            // Speciﬁcation B1 - Start Menu
            string prompt = "Main Menu\n\n1 - Display Rules\n2 - Play Game\n3 - Quit\n\nWhat would you like to do? ";
            choice = promptIntInRange(prompt, 1, 3);
            switch (choice)
            {
            case 1:
                rules();
                break;
            case 3:
                playAgain = false;
                break;
            }
            while(playAgain){
                resetBoard();
                string winner = play();
                printBoard();
                cout << "\nThe winner is " << winner << "!\n";
                winStack.push(winner);
                gamesPlayed++;
                printSummary();
                playAgain = promptReplay();
            };
            announceFunction(__func__,F_END);
        }
        // Specification A3 - Games Played Counter
        void printSummary(){
            cout << "Total games played: " << gamesPlayed << endl;
            while (!winStack.empty()){
                tempStack.push(winStack.top());
                winStack.pop();
            };
            for (int i = 1; i <= gamesPlayed; i++){
                cout << "Game " << i << " winner: " << tempStack.top() << endl;
                winStack.push(tempStack.top());
                tempStack.pop();
            }
            cout << endl << endl;
        }
};

class logger{
  private:
    ofstream outfile;

    logger(){
      std::srand(time(nullptr));  // Seed with current time
      initLogFile();
    };
    void initLogFile(){
        time_t t = std::time(nullptr);
        tm tm = *std::localtime(&t);
        outfile.open(LOG_FILE);
        outfile << "New log started at " << put_time(&tm, "%F %T") << endl;
}

  public:
    static logger& getInstance() {
      static logger instance;
          return instance;
      };
    void logMsg(string msg){
        time_t t = std::time(nullptr);
        tm tm = *std::localtime(&t);
        outfile << put_time(&tm, "%F %T") <<  "\t" << msg;
    }
};


int main() {
  // Set up logging
  clock_t start = clock();
  logger& appLog = appLog.getInstance();
  announceFunction(__func__, F_START);
  
  // Program Greeting
  ProgramGreeting();
  
  // Initialize and start game
  TicTacToe game;
  game.start();

  // Calculate total run time
  clock_t end = clock();
  double total_runtime = double(end-start) / CLOCKS_PER_SEC;
  cout << "\n\nTotal runtime: " << total_runtime << " sec";
  announceFunction(__func__, F_END);

  // Exit
  return 0;
}

// Speciﬁcation C3 - Function Activity to Disk
void announceFunction(string funcName, string action){
    logger& appLog = appLog.getInstance();
    appLog.logMsg("\tFunction " + funcName +"() " + action + ".\n");
}

void ProgramGreeting() {
    announceFunction(__func__, F_START);
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    cout << string('*',62) << "\nWelcome to  " << PROGRAM_NAME << "!!" 
    << "\nAuthor: " <<  PROGRAM_AUTHOR
    << "\nDate: " << put_time(&tm, "%F %T") << '\n'
    << string('*',62) << "\n\n\n";
    announceFunction(__func__, F_END);
}

