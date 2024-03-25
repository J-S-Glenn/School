// TempCalc.cpp -- Assignment 5
// 3/23/2024
// John Glenn
#include <stack>
#include <ctime>
#include <iostream>		// Any other libraties, too
#include <iomanip>
using namespace std;

// Global Variables
const string PROGRAM_NAME = "TempCalc.cpp";
const string PROGRAM_AUTHOR = "John Glenn";
const float FTC = (5.0/9.0);       // Fahrenheit to Celcsius
const float CTK = -273.15;         // Kelvin = Celsius - 273.15
const float FTR = 459.67;          // Rankine = Fahrenheit + 459.67
const string F_START = "Started";
const string F_END = "Ended";
const string FG_RED = "\033[1;31m";
const string FG_ORANGE = "\033[38;5;214m"; 
const string FG_BLACK = "\033[38;5;244m";
const string objPrompt = "What object would you like to calculate for? Cat, Cot, or Cap?";
const string TEMP_SCALE_PROMPT = "What temperature scale would you like to convert to?";
const string BG_DRK_GRAY = "\033[48;5;8m";
const string BG_LT_GRAY =  "\033[48;5;7m";
const string RST = "\033[0m";
const int CNT_VALID_WORDS = 4;
const int CNT_VALID_SCALES = 4;
const string VALID_TEMPS[] = {"Celsius", "Rankine", "Kelvin", "All"};
const string VALID_WORDS[CNT_VALID_WORDS] = {"bad input","cat", "cap", "cot"};
const int IDX_VALID[CNT_VALID_WORDS] = {1, 2, 3};
const int BAD_INPUT = 0;
// Specification A3 - Stack
stack<double> tempstack;
const double OBJ_TEMPS[4][2] = {{},{86,102},{72,88},{54,80}};
const int HI_TEMP = 1;
const int LOW_TEMP = 0;
//const double CAT_LOW = 86;
//const double CAT_HIGH = 102;
//const double COT_LOW = 54;
//const double COT_HIGH = 80;
//const double CAP_LOW = 72;
//const double CAP_HIGH = 88;
const double TEMP_TOLERANCE = .02;
const int VAR_COL_WIDTH = 25;      // Width of columns in tableS

// Speciﬁcation C3 – Three Functions
// Function Prototypes
void ProgramGreeting();
void announceFunction(string, string);
string getDate();
bool isFloat(string);
void ftoc(double, double, double);
void ctok(double, double, double);
void ftor(double, double, double);
bool isInt(string);
float promptFloatInRange(string, float, float);
int promptForTempScale(const string);
int promptForTemp(string);
double promptForFTemp();
float promptForFTemp(int);
void printRow(float, float, bool);
// Speciﬁcation B3 - Overloaded Prompt Functions
double prompt(string, double, double);
int prompt(const string);
int prompt(const string, int, int);
string  prompt(const string,const string[],const int);
string strToUpper(string);
float ftoc(float);
void runConversion(int, int, float);
bool valFlow(int, double);

int main() {
	int objCode, tempCode;
	float fTemp=0;
	announceFunction(__func__, F_START);
	ProgramGreeting();
	objCode = prompt(objPrompt);
	tempCode = promptForTempScale(TEMP_SCALE_PROMPT);
	fTemp = promptForFTemp(objCode);
	if (valFlow(objCode, fTemp)) runConversion(objCode, tempCode, fTemp);
	cout << "Now Exiting...\n\n";
	announceFunction(__func__, F_END);
}

float promptForFTemp(int objCode){
	announceFunction(__func__, F_START);
	float floatIn;
	cout << "What is the temperature of the " << VALID_WORDS[objCode] << " in fahrenheit? ";
	cin >> floatIn;
	announceFunction(__func__, F_END);
	return floatIn;
}

bool valFlow(int objCode, double temp){
	announceFunction(__func__, F_START);
	bool isValid = true;
	double low = VALID_TEMPS[objCode][LOW_TEMP]*(1-TEMP_TOLERANCE);
	double high = VALID_TEMPS[objCode][HI_TEMP]*(1+TEMP_TOLERANCE);
	cout << "Making sure that the " << VALID_WORDS[objCode] << "is within the acceptable range." << endl;
	if (temp < low || temp > high){
		isValid = false;
		cout << FG_RED << "Invalid temperature! Must be between " << low << " and " << high << endl;		
	}
	announceFunction(__func__, F_END);
	return isValid;
}

void runConversion(int objCode, int tempCode, float fTemp){
	announceFunction(__func__, F_START);
	switch (tempCode){
		case 1:
			break;
		case 2:
			break;
		case 3:
			break;
		case 4:
			break;
	}
	announceFunction(__func__, F_END);
}



// Speciﬁcation C2 – Select Temp Scale Menu 
int promptForTempScale(const string promptOut){
	announceFunction(__func__, F_START);
	cout << "The following temperature scales are available:\n\n";
	for (int i = 1; i <= CNT_VALID_SCALES; i++){
		cout << "\t\t" << i << ". " << VALID_TEMPS[i-1] << endl;
	}
	cout << endl;
	announceFunction(__func__, F_END);
	return prompt(promptOut, 0, CNT_VALID_SCALES);
}

float ftoc(float fahrenheit){
	announceFunction(__func__, F_START);
	float newValue = (fahrenheit - 32.0) * FTC;
	announceFunction(__func__, F_END);
	return newValue; 
}

float ctok(float celsius){
	announceFunction(__func__, F_START);
	float newValue = celsius + CTK;
	announceFunction(__func__, F_END);
	return newValue;
}

float ftor(float fahrenheit){
	announceFunction(__func__, F_START);
	float newValue = fahrenheit + FTR;
	announceFunction(__func__, F_END);
	return newValue;
}

void ProgramGreeting() {
	announceFunction(__func__, F_START);
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);
 
	cout << string('*',62) << "\nWelcome to  " << PROGRAM_NAME << "!!" << endl 
		 << "Author: " << PROGRAM_AUTHOR << endl
		 << "Date: " << put_time(&tm, "%A %d, %Y") << '\n'
		 << string('*',62) << endl;
	announceFunction(__func__, F_END);
}

// Speciﬁcation B1 – Display Function Activity
void announceFunction(string funcName, string action){
	//cout << FG_ORANGE << "Function " << __func__ << "() " << F_START << RST << ".\n";
	cout << FG_ORANGE << "Function " << funcName << "() " << action << RST << ".\n";
	//cout << FG_ORANGE << "Function " << __func__ << "() " << F_END << RST << ".\n";
}

// Speciﬁcation C1 – Only Valid Words
int prompt(string prompt){
	announceFunction(__func__, F_START);
	string strIn;
	int objIdx;
	bool objFound = false;
	// Speciﬁcation C1 – Only Valid Words
	do{cout << prompt;
	cin >> strIn;
	for (int i = 1; i<CNT_VALID_WORDS; i++){
		if (strToUpper(VALID_WORDS[i]) == strToUpper(strIn)){
			objFound = true;
			objIdx = i;
		}
	}
	if (!objFound) cout << FG_RED << "Invalid Input! Enter Cat, Cot, or Cap" << RST << endl;
	} while (!objFound);
	announceFunction(__func__, F_END);
	return objIdx;
}

string prompt(string prompt,const string validWords[], const int count){
	announceFunction(__func__, F_START);
	string strIn;
	bool objFound = false;
	cout << prompt;
	cin >> strIn;
	announceFunction(__func__, F_END);
	return strIn;
}

int prompt(string prompt, int min, const int max){
	announceFunction(__func__, F_START);
	int intIn = 0;
	
	do{
		cout << prompt;
		cin >> intIn;
		if (intIn <= min || intIn > max) cout << FG_RED << "Invalid Input! Number must be between " << min << " and " << max << RST << endl;
	}while (intIn <= min || intIn > max);
	announceFunction(__func__, F_END);
	return intIn;
}
bool isFloat(string inStr){
	announceFunction(__func__, F_START);
	bool isValid = false;
	bool foundDot = false;
	string currentNumber;
	for (int ch = 0; ch <= inStr.size() - 1; ch++){
		if (!isdigit(inStr[ch])){
			if (inStr[ch] == '.'){
				if (foundDot){
					cout << FG_RED << "INVALID INPUT! Found more than one 'dot'!\n\n " << RST;
					isValid = false;
					break;
				}else{
					foundDot = true;
					isValid = true;
				}
			}
		}
	}
	announceFunction(__func__, F_END);
	return isValid;
}

bool isInt(string inStr){
	announceFunction(__func__, F_START);
	bool isValid;

	for (int ch = 0; ch <= inStr.size() - 1; ch++){
		isValid = isdigit(inStr[ch]);
	}
	announceFunction(__func__, F_END);
	return isValid;
}

void printRow(float inFlt1, float inFlt2, bool printCap){
	announceFunction(__func__, F_START);
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";    
    };
    cout << fixed << setprecision(3)  << "|" << setw(VAR_COL_WIDTH) << inFlt1 << "|" << setw(VAR_COL_WIDTH);
	cout << inFlt2 << "|\n|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
	announceFunction(__func__, F_END);
}

string strToUpper(string inStr)
{
	announceFunction(__func__, F_START);
	string outStr = "";

	for (int character = 0; character < inStr.size(); character++){
		outStr += toupper(inStr[character]);
	}
	announceFunction(__func__, F_END);
    return outStr;
}