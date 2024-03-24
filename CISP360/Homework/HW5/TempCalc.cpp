// TempCalc.cpp -- Assignment 5
// 3/23/2024
// John Glenn

#include <iostream>		// Any other libraties, too
#include <iomanip>
using namespace std;

// Global Variables
const string PROGRAM_NAME = "TempCalc.cpp";
const string PROGRAM_AUTHOR = "John Glenn";
const string F_START = "Started";
const string F_END = "Ended";
const string RED = "\033[1;31m";
const string RST = "\0ff[1;31m";
const int CNT_VALID_WORDS = 3;
const string VALID_WORDS[CNT_VALID_WORDS+1] = {"cat", "cap", "cot"};
const int IDX_VALID[CNT_VALID_WORDS+1] = {1, 2, 3};
const int BAD_INPUT = 0;
const double CAT_LOW = 86;
const double CAT_HIGH = 102;
const double COT_LOW = 54;
const double COT_HIGH = 80;
const double CAP_LOW = 72;
const double CAP_HIGH = 88;

// Function Prototypes
void ProgramGreeting();
void announceFunction(string, string);
string getPrompt(string prompt);
bool isFloat(string);
bool isInt(string);
float promptFloatInRange(string, float, float);

int main() {
	announceFunction(__func__, F_START);
	ProgramGreeting();
	announceFunction(__func__, F_END);
}


void ProgramGreeting() {
	announceFunction(__func__, F_START);
	cout << __func__ << endl;;
	cout << RED << "Initiallizing...\n\nDecrypting...\n\nFeeding the dogs....\n\n"
	     << RST << "Contemplating life choices...\n\nInitialization complete!\n\n"
	     << string('*',62) << "\nProgram Name: " << PROGRAM_NAME << "\nAuthor:" 
		 << PROGRAM_AUTHOR << endl << string('*',62) << endl << endl;
	announceFunction(__func__, F_END);
}

void announceFunction(string funcName, string action){
	cout << "Function " << funcName << " " << action << ".\n";
}

string getPrompt(string prompt){
	string strIn;

	cout << prompt;
	cin >> strIn;

	return strIn;
}

bool isFloat(string inStr){
	bool isValid = false;
	bool foundDot = false;
	string currentNumber;
	for (int ch = 0; ch <= inStr.size() - 1; ch++){
		if (!isdigit(inStr[ch])){
			if (inStr[ch] == '.'){
				if (foundDot){
					cout << RED << "INVALID INPUT! Found more than one 'dot'!\n\n");
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


float promptFloatInRange(string prompt, float min, float max){
	announceFunction(__func__, F_START);
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
				cout << floatIn << " is not a valid option. Must be between " << min << " and " << max;
				cout << "Program Ended\n\n";
				exit(1);
			}
		}else{
			cout << "You have entered an invalid option [" + inStr + "]. Please try again...\n\n");
		}
	}
	announceFunction(__func__, F_END);
	return floatIn;
}