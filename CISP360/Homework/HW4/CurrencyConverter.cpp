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
const string STR_YEN = "Yen";
const int C_EURO = 2;
const string STR_EURO = "Euro";
const int C_GBP = 3;
const string STR_GBP = "GBP";
const string STR_USD = "USD";
const int C_FLIP = 4;
const int OP_EXIT = 5;
const int MENU_FIRST = 1;
const int MENU_LAST = 5;

// Speciﬁcation C1 - Main Menu
const string MENU_A = "\
1. USD -> Yen\n\
2. USD -> Euro\n\
3. USD -> British Pound\n\
4. Flip Conversion\n\
5. Quit w/o conversion\n\n" ;

// Speciﬁcation C2 - Reverse Menu
const string MENU_B = "\
1. Yen -> USD\n\
2. Euro -> USD\n\
3. Pound -> USD\n\
4. Quit w/o conversion\n\
5. Quit w/o conversion\n";

// Conversion constants
const float USD2YEN = 150.0980;    // 1 USD = 150.0980 Yen
const float USD2EURO = .92;        // 1 USD = .92 Euro
const float USD2GBP = 0.7899;      // 1 USD = 0.7899 British Pound Sterling 
const int INVALID = -1;
const int VAR_COL_WIDTH = 25;      // Width of columns in tableS

// Function Prototypes
// Speciﬁcation B1 - Three Functions
void autoHeader(string);
void currConvert(float, string, bool);
bool checkRange(int, int, int);
void displayMenu(int);
void genUnderline(string);
bool isFloat(string);
bool isInt(string);
void printRow(string, string, bool=false);
void ProgramGreeting();
int promptIntInRange(string, int=MENU_FIRST, int=MENU_LAST);
float promptFloatInRange(string, float=CURRENCY_MIN, float=CURRENCY_MAX);
string roundStr(string, int=3);
string strToUpper(string);

int main() {
	int menu = 1;          // Initialize w/ standard menu
	bool fromUSD = true;   // Specify if we are converting to or from USD
	int int_choice = 0;    // Menu choice from user
	ProgramGreeting();

	
	while (int_choice != OP_EXIT){

		displayMenu(menu);
		int_choice = promptIntInRange("Enter your selection and press enter: ");
	
		switch (int_choice){
			case C_YEN:
				currConvert(USD2YEN, STR_YEN, fromUSD);
				break;
			case C_EURO:
				currConvert(USD2EURO, STR_EURO, fromUSD);
				break;
			case C_GBP:
				currConvert(USD2GBP, STR_GBP, fromUSD);
				break;
			case C_FLIP:
				menu *= -1;
				fromUSD = !fromUSD;
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

void currConvert(float rate, string currName, bool fromUSD){
	float newValue, srcAmount;
	string src, dst, prompt;

	if (fromUSD){
		src = STR_USD;
		dst = currName;
	}else{
		src = currName;
		dst = STR_USD;
	}

	prompt = "Enter value in " + src + " to be converted to " + dst + ": ";
	srcAmount = promptFloatInRange(prompt);

	if (fromUSD){
		newValue = srcAmount * rate;
	}else{
		newValue = srcAmount / rate;
	}

	cout << fixed << setprecision(3) << srcAmount << " in " << src << " is " << newValue << " in " << dst << endl << endl;
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

bool isFloat(string inStr){
	cout << "Checking to see if [" << inStr << "] is a float...\n\n";
	bool isValid = false;
	bool foundDot = false;
	string currentNumber;
	for (int ch = 0; ch <= inStr.size() - 1; ch++){
		if (!isdigit(inStr[ch])){
			isValid = false;
			break;
		}
		else if (inStr[ch] == '.'){
			if (foundDot){
				cout << "\n\033[1;31m INVALID INPUT! Found more than one 'dot'. \033[0m";
				isValid = false;
				break;
			}else{
				foundDot = true;
			}
		}
	}
	return isValid;
}

bool isInt(string inStr){
	bool isValid;
	cout << "Checking to see if [" << inStr << "] is an int...\n\n";

	for (int ch = 0; ch <= inStr.size() - 1; ch++){
		isValid = isdigit(inStr[ch]);
	}
	return isValid;
}

void printRow(string inStr, string inStr2, bool printCap){
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";    
    };
    cout << "|" << setw(VAR_COL_WIDTH) << inStr << "|" << setw(VAR_COL_WIDTH) << inStr2 << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
}

// Speciﬁcation C3 - Input Prompt Function
float promptFloatInRange(string prompt, float min, float max){
	bool isValid = false;
	string inStr = "";
	float floatIn = INVALID;

	while (!isValid){
		cout << prompt << endl << endl;
		cin >> inStr;
		if (isInt(inStr) or isFloat(inStr)){
			floatIn = stof(inStr);
			if (floatIn >= min and floatIn <= max){
				isValid = true;
			}else{
				cout << floatIn << " is not a valid option. Must be between "<< min << "and" << max << endl;
			}
		}else{
			cout << "You have entered an invalid option [" << inStr << "]. \n\n Please try again...\n\n";
		}
	}

	return floatIn;
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