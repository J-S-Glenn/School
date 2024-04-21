// EhRay.cpp -- Assignment 5
// 4/17/2024
// John Glenn
#include <stack>
#include <ctime>
#include <iostream>		// Any other libraties, too
#include <iomanip>
#include <fstream>
using namespace std;

// Global Variables
const string PROGRAM_NAME = "EhRay.cpp";
const string PROGRAM_AUTHOR = "John Glenn";
const string LOG_FILE = "Log.txt"; 
const string F_START = "Started";
const string F_END = "Ended";
const string FG_RED = "\033[1;31m";
const string FG_ORANGE = "\033[38;5;214m"; 
const string FG_BLACK = "\033[38;5;244m";
const string BG_DRK_GRAY = "\033[48;5;8m";
const string BG_LT_GRAY =  "\033[48;5;7m";
const string RST = "\033[0m";
const int RNG_MIN = 0;
const int RNG_MAX = 100;
stack<double> tempstack;
const double COMP_TOLERANCE = .05;
const int VAR_COL_WIDTH = 25;      // Width of columns in tableS
const int ARRAY_SIZE = 10;
// Function Prototypes
void ProgramGreeting(ofstream&);
void announceFunction(string, string, ofstream&);
string getDate();
bool isFloat(string, ofstream&);
bool isInt(string, ofstream&);
float promptFloatInRange(string, float, float, ofstream&);
void printRow(float, float, bool, ofstream&);
double prompt(string, double, double, ofstream&);
int prompt(const string, ofstream&);
int prompt(const string, int, int, ofstream&);
string  prompt(const string,const string[],const int, ofstream&);
string strToUpper(string, ofstream&);
bool valFlow(int, double, ofstream&);
void initLogFile(ofstream&);
void initializeArrays(int*& intArr,float*& fltArr, ofstream&);
void minAndMax(int [],float [], ofstream&);
void printArray(int [], ofstream&);
void printArray(float [], ofstream&);
void arraySum(int intArr[], ofstream&);
void arraySum(float intArr[], ofstream&);
// Specification A3 - Random Number in Singleton Pattern
class SpontaneousDigitDispenser{
	private:
		int intValue;
		float fltValue;
		
		SpontaneousDigitDispenser(){
			std::srand(time(nullptr));  // Seed with current time
		}

	public:
		static SpontaneousDigitDispenser& getInstance() {
			static SpontaneousDigitDispenser instance;
        	return instance;
    	}

		int dispenseInt(int min = RNG_MIN, int max = RNG_MAX){
			// Generate a random digit between 'min' and 'max' inclusive
			intValue = min + rand() % (max - min + 1);
			return intValue;
		}

		float dispenseFlt(int min = RNG_MIN, int max = RNG_MAX){
			// Generate a random digit between 'min' and 'max' inclusive
			int randInt = rand();
			fltValue = (min + static_cast<double>(randInt) / RAND_MAX * (max - min));
			return fltValue;
		}

		float getFltValue(){
			return fltValue;
		}

		int getIntValue(){
			return intValue;
		}
};



int main() {
	ofstream logFile;
	initLogFile(logFile);

	announceFunction(__func__, F_START, logFile);
	
	ProgramGreeting(logFile);

	int* arrInt = nullptr;
	float* arrFloat = nullptr;
	initializeArrays(arrInt, arrFloat, logFile);
	printArray(arrInt, logFile);
	printArray(arrFloat, logFile);
	minAndMax(arrInt, arrFloat, logFile);
	announceFunction(__func__, F_END, logFile);
}

void minAndMax(int intArr[],float fltArr[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	for (int i = 0; i<ARRAY_SIZE; i++){
		cout << intArr[i];
	}
	cout << endl;
	announceFunction(__func__, F_END, logFile);
}

void arraySum(float fltArr[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	announceFunction(__func__, F_END, logFile);
}

void arraySum(int intArr[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	announceFunction(__func__, F_END, logFile);
}

void printArray(int intArr[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	for (int i=0; i<ARRAY_SIZE; i++){
		cout << intArr[i] << " ";
		logFile << intArr[i] << " ";
	}
	cout << endl;
	logFile << endl;
	announceFunction(__func__, F_END, logFile);
}

void printArray(float fltArr[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	cout << fixed << setprecision(3);
	for (int i=0; i<ARRAY_SIZE; i++){
		cout << fltArr[i] << " ";
		logFile << fltArr[i] << " ";
	}
	cout << endl;
	logFile << endl;
	announceFunction(__func__, F_END, logFile);
	
}

void initializeArrays(int*& intArr, float*& fltArr, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	intArr = new int[ARRAY_SIZE];
	fltArr = new float[ARRAY_SIZE];
	SpontaneousDigitDispenser& rng = rng.getInstance(); 
	for (int i=0; i<ARRAY_SIZE; i++){
		rng.dispenseInt();
		intArr[i] = rng.getIntValue();
	}
	for (int i=0; i<ARRAY_SIZE; i++){
		rng.dispenseFlt();
		fltArr[i] = rng.getFltValue(); 
	}
	announceFunction(__func__, F_END, logFile);
}

void initLogFile(ofstream& outfile){
	time_t t = std::time(nullptr);
    tm tm = *std::localtime(&t);
	outfile.open(LOG_FILE);
	outfile << "New log started at " << put_time(&tm, "%F %T") << endl;
}

bool valFlow(int objCode, double temp, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	bool isValid = true;
	//double low = VALID_TEMPS[objCode][LOW_TEMP]*(1-COMP_TOLERANCE);
	//double high = VALID_TEMPS[objCode][HI_TEMP]*(1+COMP_TOLERANCE);
	//cout << "Making sure that the " << VALID_WORDS[objCode] << "is within the acceptable range." << endl;
	//if (temp < low || temp > high){
	//	isValid = false;
	//	cout << FG_RED << "Invalid temperature! Must be between " << low << " and " << high << endl;		
	//}
	announceFunction(__func__, F_END, logFile);
	return true;
}

void ProgramGreeting(ofstream& logFile) {
	announceFunction(__func__, F_START, logFile);
    std::time_t t = std::time(nullptr);
    std::tm tm = *std::localtime(&t);

	cout << string('*',62) << "\nWelcome to  " << PROGRAM_NAME << "!!" << endl 
		 << "Author: " << PROGRAM_AUTHOR << endl
		 << "Date: " << put_time(&tm, "%A %d, %Y") << '\n'
		 << string('*',62) << endl;

	announceFunction(__func__, F_END, logFile);
}

// Specification A1 - Function Activity to Disk
void announceFunction(string funcName, string action, ofstream& log){
	time_t t = std::time(nullptr);
    tm tm = *std::localtime(&t);
 
	
	log <<  put_time(&tm, "%F %T") <<  "\tFunction " << funcName << "() " << action << RST << ".\n";

}

int prompt(string prompt, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	string strIn;
	int objIdx;
	bool objFound = false;
	// Speciﬁcation C1 – Only Valid Words
	do{cout << prompt;
	cin >> strIn;
	//for (int i = 1; i<CNT_VALID_WORDS; i++){
	//	if (strToUpper(VALID_WORDS[i]) == strToUpper(strIn)){
	//		objFound = true;
	//		objIdx = i;
	//	}
	//}
	if (!objFound) cout << FG_RED << "Invalid Input! Enter Cat, Cot, or Cap" << RST << endl;
	} while (!objFound);
	announceFunction(__func__, F_END, logFile);
	return objIdx;
}

string prompt(string prompt,const string validWords[], const int count, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	string strIn;
	bool objFound = false;
	cout << prompt;
	cin >> strIn;
	announceFunction(__func__, F_END, logFile);
	return strIn;
}

int prompt(string prompt, int min, const int max, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	int intIn = 0;
	
	do{
		cout << prompt;
		cin >> intIn;
		if (intIn <= min || intIn > max) cout << FG_RED << "Invalid Input! Number must be between " << min << " and " << max << RST << endl;
	}while (intIn <= min || intIn > max);
	announceFunction(__func__, F_END, logFile);
	return intIn;
}
bool isFloat(string inStr, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
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
	announceFunction(__func__, F_END, logFile);
	return isValid;
}

bool isInt(string inStr, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	bool isValid;

	for (int ch = 0; ch <= inStr.size() - 1; ch++){
		isValid = isdigit(inStr[ch]);
	}
	announceFunction(__func__, F_END, logFile);
	return isValid;
}

void printRow(float inFlt1, float inFlt2, bool printCap, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";    
    };
    cout << fixed << setprecision(3)  << "|" << setw(VAR_COL_WIDTH) << inFlt1 << "|" << setw(VAR_COL_WIDTH);
	cout << inFlt2 << "|\n|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
	announceFunction(__func__, F_END, logFile);
}

string strToUpper(string inStr, ofstream& logFile)
{
	announceFunction(__func__, F_START, logFile);
	string outStr = "";

	for (int character = 0; character < inStr.size(); character++){
		outStr += toupper(inStr[character]);
	}
	announceFunction(__func__, F_END, logFile);
    return outStr;
}