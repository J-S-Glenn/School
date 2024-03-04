// CurrencyConverter.cpp
// 3/3/2024
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
const int C_ALL = 4;
const int C_FLIP = 5;
const int OP_EXIT = 6;
const int MENU_FIRST = 1;
const int MENU_LAST = OP_EXIT;

// Speciﬁcation C1 - Main Menu
const string MENU_A = "\
1. USD --------------> Yen\n\
2. USD --------------> Euro\n\
3. USD --------------> British Pound\n\
4. USD --------------> Yen, Euro, and GBP\n\
5. Flip Conversion\n\
6. Quit w/o conversion\n\n" ;

// Speciﬁcation C2 - Reverse Menu
const string MENU_B = "\
1. Yen   --------------> USD\n\
2. Euro  --------------> USD\n\
3. Pound --------------> USD\n\
4. Yen, Euro, and GBP -> USD\n\
5. Flip Conversion\n\
6. Quit w/o conversion\n\n";

// Conversion constants
const float USD2YEN = 150.0980;    // 1 USD = 150.0980 Yen
const float USD2EURO = .92;        // 1 USD = .92 Euro
const float USD2GBP = 0.7899;      // 1 USD = 0.7899 British Pound Sterling 
const int INVALID = -1;
const int VAR_COL_WIDTH = 25;      // Width of columns in tableS

// Function Prototypes
// Speciﬁcation B1 - Three Functions
void autoHeader(string);
void convertAll(bool);
float currConvert(float, float, bool);
void displayMenu(int);
void genUnderline(string);
bool isFloat(string);
bool isInt(string);
void printRow(string, float, float, bool=false);
void printRow(string, string, bool=false);
void printRow(float, float, bool=false);
void ProgramGreeting();
string prompt(string);
int promptIntInRange(string, int=MENU_FIRST, int=MENU_LAST);
float promptFloatInRange(string, float=CURRENCY_MIN, float=CURRENCY_MAX);
void redPrompt(string);
string roundStr(string, int=3);
string strToUpper(string);

int main() {
	float srcAmount = 0;
	float newAmount = 0;
	float rate = 0;
	int menu = 1;          // Initialize w/ standard menu
	bool fromUSD = true;   // Specify if we are converting to or from USD
	bool runConversion = false;
	int int_choice = 0;    // Menu choice from user
	string dst, src;
	ProgramGreeting();

	
	while (int_choice != OP_EXIT){

		displayMenu(menu);
		int_choice = promptIntInRange("Enter your selection and press enter: ");
	
		switch (int_choice){
			case C_YEN:
				src = (fromUSD) ? STR_USD : STR_YEN;
				dst = (fromUSD) ? STR_YEN : STR_USD;
				rate = USD2YEN;
				runConversion = true;
				break;
			case C_EURO:
				src = (fromUSD) ? STR_USD : STR_EURO;
				dst = (fromUSD) ? STR_EURO : STR_USD;
				rate = USD2EURO;
				runConversion = true;
				break;
			case C_GBP:
				src = (fromUSD) ? STR_USD : STR_GBP;
				dst = (fromUSD) ? STR_GBP : STR_USD;
				rate = USD2GBP;
				runConversion = true;
				break;
			case C_FLIP:
				menu *= -1;
				fromUSD = !fromUSD;
				break;
			case C_ALL:
				convertAll(fromUSD);
				break;
			case OP_EXIT:
				cout << "Now Exiting...\n";
				return 0;
				break;
			default:
				cout << "Option not found...please try again...\n\n";
		}
		if (runConversion){
			srcAmount = promptFloatInRange("Enter value in " + src + " to be converted to " + dst + ": ");
			newAmount = currConvert(rate, srcAmount, fromUSD);
			printRow(src, dst, true);
			printRow(srcAmount, newAmount);
			cout << endl;
			runConversion = false;
		}
		
	}

	return 0;
}

void autoHeader(string header){
	cout << strToUpper(header) << endl;
	genUnderline(header);
}

// Speciﬁcation B3 - Convert All 
void convertAll(bool fromUSD){
	float srcAmount = 5;
	string src, dst;
	float newAmount;
	
	srcAmount = promptFloatInRange("Enter value in " + src + " to be converted to " + dst + ": ");

	printRow("Conversion", "Results", true);

	src = (fromUSD) ? STR_USD : STR_YEN;
	dst = (fromUSD) ? STR_YEN : STR_USD;
	newAmount = currConvert(USD2YEN, srcAmount, fromUSD);
	printRow((src + " -> " + dst), srcAmount, newAmount);

	src = (fromUSD) ? STR_USD : STR_EURO;
	dst = (fromUSD) ? STR_EURO : STR_USD;
	newAmount = currConvert(USD2EURO, srcAmount, fromUSD);
	printRow((src + " -> " + dst), srcAmount, newAmount);
	
	src = (fromUSD) ? STR_USD : STR_GBP;
	dst = (fromUSD) ? STR_GBP : STR_USD;
	newAmount = currConvert(USD2GBP, srcAmount, fromUSD);
	printRow((src + " -> " + dst), srcAmount, newAmount);
}

// Speciﬁcation B2 - Conversion Function(s)
float currConvert(float rate, float amount, bool fromUSD){
	float newValue;

	if (fromUSD){
		newValue = amount * rate;
	}else{
		newValue = amount / rate;
	}

	return newValue;
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
	bool isValid = false;
	bool foundDot = false;
	string currentNumber;
	for (int ch = 0; ch <= inStr.size() - 1; ch++){
		if (!isdigit(inStr[ch])){
			if (inStr[ch] == '.'){
				if (foundDot){
					redPrompt("INVALID INPUT! Found more than one 'dot'!\n\n");
					isValid = false;
					break;
				}else{
					foundDot = true;
					isValid = true;
				}
			}
		}
	}
	return isValid;
}

bool isInt(string inStr){
	bool isValid;

	for (int ch = 0; ch <= inStr.size() - 1; ch++){
		isValid = isdigit(inStr[ch]);
	}
	return isValid;
}

void printRow(string inStr, float inFlt1, float inFlt2, bool printCap){
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";    
    };
    cout << fixed << setprecision(3) << "|" << setw(VAR_COL_WIDTH) << inStr << "|" << setw(VAR_COL_WIDTH/3) << inFlt1 << setw(VAR_COL_WIDTH/3) <<  " -> " << setw(VAR_COL_WIDTH/3+1) << inFlt2 << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
}

void printRow(string inStr, string inStr2, bool printCap){
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";    
    };
    cout << "|" << setw(VAR_COL_WIDTH) << inStr << "|" << setw(VAR_COL_WIDTH) << inStr2 << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
}

void printRow(float inFlt1, float inFlt2, bool printCap){
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";    
    };
    cout << fixed << setprecision(3)  << "|" << setw(VAR_COL_WIDTH) << inFlt1 << "|" << setw(VAR_COL_WIDTH);
	cout << inFlt2 << "|\n|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
}

// Speciﬁcation C3 - Input Prompt Function
string getPrompt(string prompt){
	string strIn;

	cout << prompt;
	cin >> strIn;

	return strIn;
}

// Specification A3 - Red Error Text
void redPrompt(string prompt){
	cout << "\n\033[1;31m" << prompt << "\033[0m\n";
}

float promptFloatInRange(string prompt, float min, float max){
	bool isValid = false;
	string inStr = "";
	float floatIn = INVALID;

	while (!isValid){
		inStr = getPrompt(prompt);
		if (isInt(inStr) or isFloat(inStr)){
			floatIn = stof(inStr);
			if (floatIn >= min and floatIn <= max){
				isValid = true;
			}else{
				// Specification A1 - Sanity Check
				redPrompt(to_string(floatIn) + " is not a valid option. Must be between " + to_string(min) + " and " + to_string(max));
				cout << "Program Ended\n\n";
				exit(1);
			}
		}else{
			redPrompt("You have entered an invalid option [" + inStr + "]. Please try again...\n\n");
		}
	}

	return floatIn;
}

int promptIntInRange(string prompt, int min, int max){
	bool isValid = false;
	string inStr = "";
	int int_choice;

	while (!isValid){
		inStr = getPrompt(prompt);
		if (isInt(inStr)){
			int_choice = stoi(inStr);
			if (int_choice >= min and int_choice <= max){
				isValid = true;
			}else{
				// Specification A2 - Valid Menu Selection only
				redPrompt((to_string(int_choice) + " is not a valid option. Must be between " + to_string(min) + " and " +  to_string(max) + "\n\n"));
				cout << "Program Ended\n\n";
				exit(1);
			}
		}else{
			redPrompt("You have entered an invalid option [" + inStr + "]. \n\n Please try again...\n\n");
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