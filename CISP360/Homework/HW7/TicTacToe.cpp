// TicTacToe.cpp -- Assignment 6
// 5/3/2024
// John Glenn
#include <stack>
#include <ctime>
#include <iostream>
#include <iomanip>
#include <fstream>
#include <string>
using namespace std;

// Function Prototypes
void announceFunction(string, string);
void ProgramGreeting(string, string);

// Class Definitions
class TicTacToe{
    private:
        enum tile  { UNSET, X, O };
        tile gameBoard[3][3];
        tile PLAYER1 = X;
        tile PLAYER2 = O;

        const string EX[6] = {" __  __ "," \\ \\/ / ","  \\  /  ","  /  \\  "," /_/\\_\\ ","        "};
        const string OH[6] = {"  ____  "," / __ \\ "," ||  || "," ||__|| "," \\____/ ","        "};
        const int decoder[9][2] = {{0,0},{0,1},{0,2},{1,0},{1,1},{1,2},{2,0},{2,1},{2,2}};
        const string FG_RED = "\033[1;31m", RST = "\033[0m";
        const int TILE_WIDTH = 8, TILE_HEIGHT = 5;
        const char CROSS = '+', HOR   = '-', VER   = '|';
        int row, col, setTiles, choice, tally, cntTile, gamesPlayed=0;
        stack<string> winStack, tempStack;
        string strChoice, prompt;
        bool playAgain = true;
        
        // Private Class Methods
        tile    checkBoard();
        bool    coinFlip();
        void    computerTurn();
        string  getPrompt(string);
        bool    isInt(string);
        bool    isSet(int);
        string  play();
        void    printBoard();
        void    printSummary();
        void    printWelcome();
        int     promptIntInRange(string, int, int);
        bool    promptReplay();
        void    resetBoard();
        void    rules();
        bool    set(int, tile);
        string  strToUpper(string);
        void    userTurn();

    public:
        // Public Class Methods
        TicTacToe();
        void start();
};

class Logger{
  private:
    ofstream outfile;
    const string LOG_FILE = "Log.txt";

    Logger(){
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
    static Logger& getInstance() {
      static Logger instance;
          return instance;
      };
    void logMsg(string msg){
        time_t t = std::time(nullptr);
        tm tm = *std::localtime(&t);
        outfile << put_time(&tm, "%F %T") <<  "\t" << msg;
    }
};


int main() {
    const string PROGRAM_NAME = "TikTacToe.cpp";
    const string PROGRAM_AUTHOR = "John Glenn";

      // Set up logging
    clock_t start = clock();
    Logger& appLog = appLog.getInstance();
    announceFunction(__func__, "Started");
    
    // Program Greeting
    ProgramGreeting(PROGRAM_NAME, PROGRAM_AUTHOR);
    
    // Initialize and start game
    TicTacToe game;
    game.start();

    // Calculate total run time
    clock_t end = clock();
    double total_runtime = double(end-start) / CLOCKS_PER_SEC;
    cout << "\n\nTotal runtime: " << total_runtime << " sec";
    announceFunction(__func__, "Ended");

    // Exit
    return 0;
}

// Speciﬁcation C3 - Function Activity to Disk
void announceFunction(string funcName, string action){
    Logger& appLog = appLog.getInstance();
    appLog.logMsg("\tFunction " + funcName +"() " + action + ".\n");
}
void ProgramGreeting(string PROGRAM_NAME, string PROGRAM_AUTHOR) {
    announceFunction(__func__, "Started");
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
    cout << string('*',62) << "\nWelcome to  " << PROGRAM_NAME << "!!" 
    << "\nAuthor: " <<  PROGRAM_AUTHOR
    << "\nDate: " << put_time(&tm, "%F %T") << '\n'
    << string('*',62) << "\n\n\n";
    announceFunction(__func__, "Ended");
}
TicTacToe::tile TicTacToe::checkBoard(){
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
TicTacToe::TicTacToe(){
announceFunction(__func__,"Started");
resetBoard();
announceFunction(__func__,"Ended");
}
void TicTacToe::start(){
    announceFunction(__func__,"Started");
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
    announceFunction(__func__,"Ended");

}

// Specification A3 - Games Played Counter
void TicTacToe::printSummary(){
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
bool TicTacToe::coinFlip(){
    std::srand(time(nullptr));  // Seed with current time
    return (int)rand()%2;
}
string TicTacToe::strToUpper(string inStr){
    announceFunction(__func__,"Started");
    string outStr = "";

    for (int character = 0; character < inStr.size(); character++){
        outStr += toupper(inStr[character]);
    }
    announceFunction(__func__,"Ended");
    return outStr;
}
bool TicTacToe::promptReplay(){
    announceFunction(__func__,"Started");
    while (true){
        // Specification A2 - Play Again Option
        cout << "Do you want to play again? [Y/N] ";
        cin >> strChoice;
        strChoice = strToUpper(strChoice);
        if (strChoice == "Y"){
            announceFunction(__func__,"Ended");
            return true;
        }else if (strChoice == "N"){
            announceFunction(__func__,"Ended");
            return false;
        }else{
            //Speciﬁcation B2 - Valid Menu Choices
            cout << FG_RED << "Invalid Input. Try again...\n" << RST;
        }
    }
}
string TicTacToe::play(){
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
bool TicTacToe::isSet(int cell){
    row = decoder[cell-1][0];
    col = decoder[cell-1][1];
    announceFunction(__func__,"Started");
    if (gameBoard[row][col] == UNSET){
        announceFunction(__func__,"Ended");
        return false;
    }else{return true;}
}
void TicTacToe::computerTurn(){
    printBoard();
    srand(time(nullptr));
    do{
        choice = (int)(rand()%9+1);
    }while(isSet(choice));
    set(choice, O);
}
void TicTacToe::userTurn(){
    printBoard();
    do{
        prompt = "What space would you like to use? ";
        // Speciﬁcation B3 – Range Check Move
        choice = promptIntInRange(prompt, 1, 9);
    }while(!set(choice, X));
}
void TicTacToe::rules(){
    announceFunction(__func__,"Started");
    cout << "\n\nRULES\n=====\n\n1. The computer plays 'O'\n2. The player plays 'X'\n3. First player is random\n"
            << "4. Get 3 in a row to win!\n\n";
    announceFunction(__func__,"Ended");
}
void TicTacToe::printWelcome(){
    announceFunction(__func__,"Started");
    cout << setw(27) << "Welcome to TicTacToe!\n\n";
    announceFunction(__func__,"Ended");
}

// Speciﬁcation C2 - Simple Display
void TicTacToe::printBoard(){
    announceFunction(__func__,"Started");
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
    announceFunction(__func__,"Ended");
}
string TicTacToe::getPrompt(string prompt){
    announceFunction(__func__, "Started");
    string strIn;

    cout << prompt;
    cin >> strIn;
    announceFunction(__func__, "Ended");
    return strIn;
};
bool TicTacToe::isInt(string inStr){
    announceFunction(__func__, "Started");
    bool isValid;

    for (int ch = 0; ch <= inStr.size() - 1; ch++){
        isValid = isdigit(inStr[ch]);
    }
    announceFunction(__func__, "Ended");
    return isValid;
};
int TicTacToe::promptIntInRange(string prompt, int min, int max){
    announceFunction(__func__, "Started");
    	bool isValid = false;
	string inStr = "";
	int int_choice;

	while (!isValid){
		inStr = getPrompt(prompt);
		if (isInt(inStr)){
			int_choice = stoi(inStr);
			if (int_choice >= min && int_choice <= max){
				isValid = true;
			}else{
				// Specification A2 - Valid Menu Selection only
				cout << FG_RED << to_string(int_choice) << " is not a valid option. Must be between "
                     << to_string(min) << " and " <<  to_string(max) + "\n\nProgram Ended\n\n" << RST;
				exit(1);
			}
		}else{
		    cout << FG_RED << ("You have entered an invalid option [" + inStr + "]. \n\nPlease try again...\n\n") << RST;
		}
	}
    announceFunction(__func__, "Ended");
	return int_choice;
}
bool TicTacToe::set(int cell, TicTacToe::tile mark){
    announceFunction(__func__,"Started");
    if (!isSet(cell)){
        gameBoard[decoder[cell-1][0]][decoder[cell-1][1]] = mark;
        setTiles++;
        announceFunction(__func__,"Ended");
        return true;
    }else{
        // Specification A1 - Open Moves Only Check
        cout << FG_RED << "Invalid Input: Space is already taken!" << RST << endl;
        announceFunction(__func__,"Ended");
        return false;
    }    
}
void TicTacToe::resetBoard(){
    announceFunction(__func__,"Started");
    setTiles = 0;
    for (int r = 0; r < 3; r++){
        for (int c = 0; c < 3; c++){
            gameBoard[r][c] = UNSET;
        };    
    };
    announceFunction(__func__,"Ended");
}
