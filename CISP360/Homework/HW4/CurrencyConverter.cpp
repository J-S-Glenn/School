// CurrencyConverter.cpp
// 2/15/2024
// John Glenn

#include <iostream>
#include <iomanip>
using namespace std;

// Global Variables
const string PROGRAM_NAME = "CurrencyConverter.cpp";
const string PROGRAM_AUTHOR = "John Glenn";
const int CURRENCY_MIN = 0;
const int CURRENCY_MAX = 100000;
const int C_YEN = 1;
const int C_EURO = 2;
const int C_BPS = 3;
const int C_FLIP = 4;
const int OP_EXIT = 5;
const int MENU_FIRST = 1;
const int MENU_LAST = 5;

const string MENU_A = "\
1. USD -> Yen\n\
2. USD -> Euro\n\
3. USD -> British Pound\n\
4. Flip Conversion\n\
5. Quit w/o conversion\n\n" ;

const string MENU_B = "\
1. Yen -> USD\n\
2. Euro -> USD\n\
3. Pound -> USD\n\
4. Quit w/o conversion\n\
5. Quit w/o conversion\n\
";

// Conversion constants
const float USD2YEN = 150.1;       // 1 USD = 150.10 Yen
const float USD2EURO = .92;        // 1 USD = .92 Euro
const float USD2GPS = 0.790077;    // 1 USD = 0.790077 British Pound Sterling 
const int INVALID = -1;
const int VAR_COL_WIDTH = 25;      // Width of columns in tableS

// Function Prototypes
void autoHeader(string);
bool checkRange(int, int, int);
void displayMenu(int);
void genUnderline(string);
bool isInt(string);
void printRow(string, string, bool=false);
void ProgramGreeting();
int promptIntInRange(string, int=MENU_FIRST, int=MENU_LAST);
float promptFloatInRange(string, float=CURRENCY_MIN, float=CURRENCY_MAX);
string roundStr(string, int=3);
string strToUpper(string);

int main() {
	int menu = 1; // Initialize w/ standard menu

	string str_choice;
	int int_choice = 0;
	ProgramGreeting();

	
	while (int_choice != OP_EXIT){

		displayMenu(menu);
		str_choice = promptIntInRange("Enter your selection and press enter: ");
	
		switch (int_choice){
			case C_YEN:
				break;
			case C_EURO:
				break;
			case C_BPS:
				break;
			case C_FLIP:
				menu *= -1;
				break;
			case OP_EXIT:
				cout << "Now Exiting...\n";
				return 0;
				break;
			default:
				cout << "Option not found...please try again...\n\n";
		}
		
	}

	return 0;
}

void autoHeader(string header){
	cout << strToUpper(header) << endl;
	genUnderline(header);
}


void displayMenu(int menuChoice){
	if (menuChoice == 1){
		cout << MENU_A;
	}else{
		cout << MENU_B;
	}
}
void genUnderline(string inStr){
	for (int character = 0; character < inStr.size(); character++){
		if (inStr[character] != ' '){
			cout << '=';
		}else{
			cout << ' ';
		}
	}
	cout << endl;
}

bool isInt(string inStr){
	cout << "Checking to see if [" << inStr << "] is an int...\n\n";
	int intOut = stoi(inStr);
	cout << intOut;
	return false;
}

void printRow(string inStr, string inStr2, bool printCap){
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";    
    };
    cout << "|" << setw(VAR_COL_WIDTH) << inStr << "|" << setw(VAR_COL_WIDTH) << inStr2 << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
}

int promptIntInRange(string prompt, int min, int max){
	bool isValid = false;
	string inStr = "";
	int int_choice;

	while (!isValid){
		cout << prompt << endl << endl;
		cin >> inStr;
		if (isInt(inStr)){
			int_choice = stoi(inStr);
			if (int_choice >= min and int_choice <= max){
				isValid = true;
			}else{
				cout << int_choice << " is not a valid option. Must be between "<< min << "and" << max << endl;
			}
		}else{
			cout << "You have entered an invalid option [" << inStr << "]. \n\n Please try again...\n\n";
		}
	}

	return int_choice;
	
}
void ProgramGreeting() {
	cout << "Initiallizing...\n\nDecrypting...\n\nFeeding the dogs....\n\n"
	     << "Contemplating life choices...\n\nInitialization complete!\n\n"
	     << string('*',62) << "\nProgram Name: " << PROGRAM_NAME << "\nAuthor:" 
		 << PROGRAM_AUTHOR << endl << string('*',62) << endl << endl;
}

string roundStr(string num, int places){
	return num.substr(0, num.find('.') + places+1);
}

string strToUpper(string inStr)
{
	string outStr = "";

	for (int character = 0; character < inStr.size(); character++){
		outStr += toupper(inStr[character]);
	}
    return outStr;
}

/*
Example Output
*/