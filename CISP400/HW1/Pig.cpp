// Pig.cpp -- Homework 1
// 8/30/2024
// John Glenn
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>		// Any other libraties, too
#include <string>
#include <limits>
using namespace std;


class jlogger{
	private:
		string log_file;
		string authName;
		string appName;
		string F_START = "Started";
		string F_END = "Ended";
		ofstream obLogFile;
		void initLogFile();
	public:
        static jlogger& getInstance(){
			static jlogger instance;
			return instance;
		}
		
		void initialize(string app_Name = "My Program", string auth_Name = "John S. Glenn", string logfile = "log.txt"){
			appName = app_Name;
			authName = auth_Name;
			log_file = logfile;
			obLogFile.open(log_file);
			if (!obLogFile.is_open()) {
 			   	cerr << "Error: Could not open log file " << log_file << endl;
    			exit(1);
			}
			initLogFile();
			ProgramGreeting();
		}

		//Specification B2 - Function Activity to Disk
		void announceFunction(string funcName, string action){
		time_t t = std::time(nullptr);
		tm tm = *std::localtime(&t);
		obLogFile <<  put_time(&tm, "%F %T") <<  "\tFunction " << funcName << "() " << action << "\n";
		}

		void ProgramGreeting(){
			announceFunction(__func__, F_START);
			std::time_t t = std::time(nullptr);
			std::tm tm = *std::localtime(&t);
			obLogFile << string('*',62) << "\nWelcome to  " << appName << "!!" << endl 
			<< "Author: " << authName << endl
			<< "Date: " << put_time(&tm, "%A %d, %Y") << '\n'
			<< string('*',62) << endl << endl << endl;
			cout << string('*',62) << "\nWelcome to  " << appName << "!!" << endl 
			<< "Author: " << authName << endl
			<< "Date: " << put_time(&tm, "%A %d, %Y") << '\n'
			<< string('*',62) << endl;
			announceFunction(__func__, F_END);
		}
};

class SpontaneousDigitDispenser{
  private:
  	const static int DEFAULT_MIN = 1;
	const static int DEFAULT_MAX = 10;
    int intValue = 0;
    float fltValue = 0;
	// Specification C1 - Fixed Seed
	unsigned int seed = 12345;
	//unsigned int seed = time(NULL);

    SpontaneousDigitDispenser(){
      std::srand(seed);  // Seed with current time
    }

  public:
    static SpontaneousDigitDispenser& getInstance(){
      static SpontaneousDigitDispenser instance;
          return instance;
      }

    int dispenseInt(int min = DEFAULT_MIN, int max = DEFAULT_MIN){
      // Generate a random digit between 'min' and 'max' inclusive
      intValue = min + rand() % (max - min + 1);
      return intValue;
    }

    float dispenseFlt(int min = DEFAULT_MIN, int max = DEFAULT_MIN){
      // Generate a random digit between 'min' and 'max' inclusive
      int randInt = rand();
      fltValue = (min + static_cast<double>(randInt) / RAND_MAX * (max - min));
      return fltValue;
    }

	int coinFlip(){
		return dispenseInt(0,1);
	}
};

class pigGame{
	private:
		enum action{
			HOLD,
			ROLL,
			QUIT
		};
		enum player{
			PLAYER,
			AI
		};
		const string PIG_ART = R"(         ,.
        (_|,.
       ,' /, )_______   _
    __j o``-'        `.'-)'
   (")                 \'
    `-j                |
      `-._(           /
         |_\  |--^.  /
        /_]'|_| /_)_/
           /_]'  /_]')""\n";
		string retry_menu = R"(
 .----------------. .----------------. .----------------. .----------------.                                       
| .--------------. | .--------------. | .--------------. | .--------------. |                                      
| |   ______     | | |   _____      | | |      __      | | |  ____  ____  | |                                      
| |  |_   __ \   | | |  |_   _|     | | |     /  \     | | | |_  _||_  _| | |                                      
| |    | |__) |  | | |    | |       | | |    / /\ \    | | |   \ \  / /   | |                                      
| |    |  ___/   | | |    | |   _   | | |   / ____ \   | | |    \ \/ /    | |                                      
| |   _| |_      | | |   _| |__/ |  | | | _/ /    \ \_ | | |    _|  |_    | |                                      
| |  |_____|     | | |  |________|  | | ||____|  |____|| | |   |______|   | |                                      
| |              | | |              | | |              | | |              | |                                      
| '--------------' | '--------------' | '--------------' | '--------------' |                                      
 '----------------' '----------------' '----------------' '----------------'                                       
 .----------------. .----------------. .----------------. .----------------. .-----------------..----------------. 
| .--------------. | .--------------. | .--------------. | .--------------. | .--------------. | .--------------. |
| |      __      | | |    ______    | | |      __      | | |     _____    | | | ____  _____  | | |    ______    | |
| |     /  \     | | |  .' ___  |   | | |     /  \     | | |    |_   _|   | | ||_   \|_   _| | | |   / _ __ `.  | |
| |    / /\ \    | | | / .'   \_|   | | |    / /\ \    | | |      | |     | | |  |   \ | |   | | |  |_/____) |  | |
| |   / ____ \   | | | | |    ____  | | |   / ____ \   | | |      | |     | | |  | |\ \| |   | | |    /  ___.'  | |
| | _/ /    \ \_ | | | \ `.___]  _| | | | _/ /    \ \_ | | |     _| |_    | | | _| |_\   |_  | | |    |_|       | |
| ||____|  |____|| | |  `._____.'   | | ||____|  |____|| | |    |_____|   | | ||_____|\____| | | |    (_)       | |
| |              | | |              | | |              | | |              | | |              | | |              | |
| '--------------' | '--------------' | '--------------' | '--------------' | '--------------' | '--------------' |
 '----------------' '----------------' '----------------' '----------------' '----------------' '----------------' )";
		SpontaneousDigitDispenser& dice = dice.getInstance();
		int WIN = 100000;
		int game_count;
		bool playAgain;
		bool turnEnd;
		int roll = 0;
		int player_grand_total = 0;
		int ai_grand_total = 0;
		int player_total = 0;
		int ai_total = 0;
		action actionChoice;
		player currentPlayer;
		string F_START = "Started";
		string F_END = "Ended";
		string hPlayer;
		string FG_RED = "\033[1;31m";
		string RST = "\033[0m";
		// Specification C4 - Three Functions
		jlogger& myScribe = myScribe.getInstance();
		int promptIntInRange(string, int, int);
		bool promptYN(string);
        bool isInt(string);
		string getPrompt(string prompt);
		bool exitGame();
		int D6();
		int RandomNumber(int, int);
		void getPlayerName();
		void getAction();
		void playerTurn();
		void startGame(int* hiScore);
		void getCurrentScores();
		void rollDice();
		void AITurn();
		void welcome();
		void getFirstPlayer();
	public:
		pigGame();
};

int main() {
    // Set up logging
    clock_t start = clock();
    jlogger& myScribe = myScribe.getInstance();
	myScribe.initialize("Pig");

    myScribe.announceFunction(__func__, "Started");
	pigGame myGame = pigGame();
    myScribe.announceFunction(__func__, "Ended");

	clock_t end = clock();

  	double total_runtime = double(end-start) / CLOCKS_PER_SEC;
  	cout << "\n\nTotal runtime: " << total_runtime << " sec";
  	myScribe.announceFunction(__func__, "Total runtime: " + to_string(total_runtime) + " sec");
}

int pigGame::promptIntInRange(string prompt, int min, int max){
  myScribe.announceFunction(__func__, F_START);
  bool isValid = false;
  string inStr = "";
  float floatIn;

  while (!isValid){
    do{
	inStr = getPrompt(prompt);
	}while(inStr.length() == 0);
    if (isInt(inStr)){
      floatIn = stof(inStr);
      if (floatIn >= min && floatIn <= max){
        isValid = true;
      }else{
        cout << FG_RED << to_string(floatIn) + " is not a valid option. Must be between " + to_string(min) + " and " + to_string(max) << RST;
      }
    }else{
      cout << FG_RED << "You have entered an invalid option [" + inStr + "]. Please try again...\n\n" << RST;
    }
  }
  myScribe.announceFunction(__func__, F_END);
  return floatIn;
}

bool pigGame::promptYN(string prompt){
	myScribe.announceFunction(__func__, F_START);
	bool isValid = false;
    string strIn;
	do{
        cout << prompt;
		getline(cin, strIn);
	}while((strIn.length() > 1) || (strIn.length() == 1 && (tolower(strIn[0]) != 'n' && tolower(strIn[0]) != 'y' )));
	myScribe.announceFunction(__func__, F_END);
	if (strIn.length() == 0 || tolower(strIn[0]) == 'y'){
		return true;
	}else{
		return false;
	}

}

bool pigGame::isInt(string inStr){
  myScribe.announceFunction(__func__, F_START);
  bool isValid;

  for (int ch = 0; ch <= inStr.size() - 1; ch++){
    isValid = isdigit(inStr[ch]);
  }
  myScribe.announceFunction(__func__, F_END);
  return isValid;
}
string pigGame::getPrompt(string prompt){
  myScribe.announceFunction(__func__, F_START);
  string strIn;
  cout << prompt;
  getline(cin,strIn);
  myScribe.announceFunction(__func__, F_END);
  return strIn;
}

bool pigGame::exitGame(){
	myScribe.announceFunction(__func__, F_START);
	myScribe.announceFunction(__func__,"Game Exiting...");
	myScribe.announceFunction(__func__, F_END);
	return false;
}

// Specification A1 - D6() function
int pigGame::D6(){
	myScribe.announceFunction(__func__, F_START);
	cout << "Rolling dice!\n";
	int result = RandomNumber(1,6);
	if (currentPlayer == PLAYER){
		cout << hPlayer << " has rolled a " << result << endl;
	}else{cout << "AI has rolled a " << result << endl;}

	myScribe.announceFunction(__func__, F_END);
    return result;
}

// Specification A2 - RandomNumber() function
int pigGame::RandomNumber(int hi, int low){
	myScribe.announceFunction(__func__, F_START);
	int result = dice.dispenseInt(hi,low);
	myScribe.announceFunction(__func__, ("Getting number between " + to_string(low) + " and " + to_string(hi)));
	myScribe.announceFunction(__func__, ("Number generated:  " + to_string(result)));
	myScribe.announceFunction(__func__, F_END);
	return result;
}

// Specification C2 - Student Name
void pigGame::getPlayerName(){
	myScribe.announceFunction(__func__, F_START);
	bool name = false;
	do{
		cout << "What is your name (First Last)? ";
		getline(cin, hPlayer);
		cout << "Name entered: " << hPlayer << "\n";
		name = promptYN("Is this correct? [Y/n]");
	} while (!name);
	myScribe.announceFunction(__func__, F_END);
}

void pigGame::startGame(int* hiScore){
	myScribe.announceFunction(__func__, F_START);
	getFirstPlayer();
	do{
		do{
			getCurrentScores();
			if (currentPlayer == PLAYER){
				playerTurn();
			}else{
				AITurn();
			}
		}while(!turnEnd);
		if (currentPlayer == PLAYER){
			currentPlayer = AI;
		}else if (currentPlayer == AI){
			currentPlayer = PLAYER;
		}
	}while(player_grand_total < WIN && ai_grand_total < WIN);
	if (*hiScore < ai_grand_total){*hiScore = ai_grand_total;}
	if (*hiScore < player_grand_total){*hiScore = player_grand_total;}
	ai_grand_total = 0;
	player_grand_total = 0;
	myScribe.announceFunction(__func__, F_END);
};

void pigGame::rollDice(){
	myScribe.announceFunction(__func__, F_START);
	roll = D6();
	if(currentPlayer == PLAYER){
		if (roll > 1){
			cout << roll << " points added to score!\n";
			player_total += roll*1000;
		}else{
			cout << "Turn Lost!\n";
			player_total =0;
			turnEnd = true;
		}

	}else{
		if (roll > 1){
			cout << roll << " points added to score!\n";
			ai_total += roll*1000;
		}else{
			ai_total = 0;
			cout << "Turn Lost!\n";
			turnEnd = true;
		}

    }
	myScribe.announceFunction(__func__, F_END);
}

// Specification B1 - Display Turn Stats
void pigGame::getCurrentScores(){
	myScribe.announceFunction(__func__, F_START);
	cout << "-------Player-------|---Total---|Grand Total-\n"
	     << "|" << setw(19) << hPlayer << "|" << setw(11) << player_total << "|" << setw(11) << player_grand_total << "|\n"
		 <<  "-" << string(19,'-') << "|" << string(11,'-') << "|------------\n"
		 << "|" << setw(19) << "AI" << "|" << setw(11) << ai_total << "|" << setw(11) << ai_grand_total << "|\n"
		 <<  "-" << string(19,'-') << "|" << string(11,'-') << "|------------\n" ;
		 myScribe.announceFunction(__func__, F_END);
} 

// Specification C3 - Numeric Menu
void pigGame::getAction(){
	myScribe.announceFunction(__func__, F_START);
	int choice = promptIntInRange("What would you like to do?\n\n\t1. Hold\n\t2. Roll\n\t3. Quit\n\nEnter selection and press ENTER: ",1,3);
	actionChoice = static_cast<action>(choice-1);
	myScribe.announceFunction(__func__, F_END);
}

void pigGame::playerTurn(){
	myScribe.announceFunction(__func__, F_START);
	getAction();
	turnEnd = false;
	if (actionChoice == HOLD){
		player_grand_total += player_total;
		player_total = 0;
		turnEnd = true;
	}else if(actionChoice == ROLL){
		rollDice();
	}else if(actionChoice == QUIT){
		myScribe.announceFunction(__func__, F_END);
		exit(0);
	}
	myScribe.announceFunction(__func__, F_END);
}

void pigGame::AITurn(){
	myScribe.announceFunction(__func__, F_START);
	int choice;
	turnEnd = false;
	
	do{
	cout << "AI is deciding whether or not to hold.\n";
	choice = D6();
	if (choice >= 1 && choice <= 3){
		cout << "AI is holding.\n";
		turnEnd = true;
		ai_grand_total += ai_total;
		ai_total = 0;
	}else{
		cout << "AI is NOT holding.\n";
		actionChoice = ROLL;
		rollDice();
	}}while(!turnEnd);
	myScribe.announceFunction(__func__, F_END);
}

void pigGame::welcome(){
	myScribe.announceFunction(__func__, F_START);
	cout << "\n\tWelcom to Pig!\n\n" << PIG_ART << "\n\n";
	myScribe.announceFunction(__func__, F_END);
}

void pigGame::getFirstPlayer(){
	myScribe.announceFunction(__func__, F_START);
	cout << "Let's get started by deciding who goes first.\n";
	int pick = promptIntInRange("Choose heads or tails! [0 = heads, 1 = tails]",0,1);
	if (pick){
		cout << "The coin landed on tails!";
	}else{
		cout << "The coin landed on heads!";
	}

	bool flip = dice.coinFlip();

	if (pick == flip){
		cout << "Player goes first!\n";
		currentPlayer = PLAYER;
	}else{
		cout << "The AI goes first!\n";
		currentPlayer = AI;
	}
	myScribe.announceFunction(__func__, F_END);
}

pigGame::pigGame(){
	myScribe.announceFunction(__func__, F_START);
	// Specification B3 - hiScore on Heap
	int* hiScore;
	hiScore = new int(0);
	myScribe.announceFunction(__func__, "Initializing Pig");
	welcome();
	getPlayerName();
	game_count = 0;
	do{
		startGame(hiScore);
		// Specification A3 - Games Played Counter
		game_count++;
		// Specification A4 - Play Again Option
		// Specification B4 – Display hiScore
		playAgain = promptYN((retry_menu + "\nGames Played: " + to_string(game_count) + "\nCurrent High Score: " + to_string(*hiScore) + "\nWould you like to play again? [Y|n]"));
	}while(playAgain);
	delete hiScore;
	myScribe.announceFunction(__func__, "Exiting Pig");
}


void jlogger::initLogFile(){
	announceFunction(__func__, F_START);
	time_t t = std::time(nullptr);
	tm tm = *std::localtime(&t);
	cout << "New log started at " << put_time(&tm, "%F %T") << endl;
	obLogFile << "New log started at " << put_time(&tm, "%F %T") << endl;
	announceFunction(__func__, F_END);
}



