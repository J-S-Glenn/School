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
stack<int> tempstack;
const double COMP_TOLERANCE = .05;
const int VAR_COL_WIDTH = 9;      // Width of columns in tableS
const int ARRAY_SIZE = 10;
const int STACK_SIZE = 20;
// Function Prototypes
void ProgramGreeting(ofstream&);
void announceFunction(string, string, ofstream&);
string getDate();
bool isFloat(string, ofstream&);
bool isInt(string, ofstream&);
float promptFloatInRange(string, float, float, ofstream&);
void printRow(float [], ofstream&);
void printRow(int [], ofstream&);
void printStackRow(int [], ofstream&);
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
void arraySum(int [], ofstream&);
void arraySum(float [], ofstream&);
void arraySum(int [], ofstream&);
void arraySum(float [], ofstream&);
void arrayRev(int*& , ofstream&);
void arrayRev(float*& , ofstream&);
void arrayShiftRight(int*&, ofstream&);
void arrayShiftRight(float*&, ofstream&);
void loadStack(ofstream&);
void printStack(ofstream&);
void numberSearch(int [], float [], ofstream&);
string getPrompt(string prompt, ofstream&);
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

	// Speciﬁcation C1 – Display Array
	cout << FG_ORANGE << "Specification C1 Start" << RST << endl;
	printArray(arrInt, logFile);
	printArray(arrFloat, logFile);
	cout << FG_ORANGE << "Specification C1 End" << RST << endl;

	// Speciﬁcation C2 – Sum
	cout << FG_RED << "Specification C2 Start" << RST << endl;
	arraySum(arrInt, logFile);
	arraySum(arrFloat, logFile);
	cout << FG_RED << "Specification C2 End" << RST << endl;

	// Speciﬁcation C3 – Min and Max
	cout << FG_ORANGE << "Specification C3 Start" << RST << endl;
	minAndMax(arrInt, arrFloat, logFile);
	announceFunction(__func__, F_END, logFile);
	cout << FG_ORANGE << "Specification C3 End" << RST << endl;

	// Speciﬁcation B2 – A Ray Reversal 
	cout << FG_RED << "Specification B2 Start" << RST << endl;
	arrayRev(arrInt, logFile);
	arrayRev(arrFloat, logFile);
	cout << FG_RED << "Specification B2 End" << RST << endl;
	
	// Speciﬁcation B3 - Element Shift
	cout << FG_ORANGE << "Specification B3 Start" << RST << endl;
	arrayShiftRight(arrInt, logFile);
	arrayShiftRight(arrFloat, logFile);
	cout << FG_ORANGE << "Specification B3 End" << RST << endl;

	// Specification A2 - Implement a Stack
	cout << FG_RED << "Specification A2 Start" << RST << endl;
	loadStack(logFile);
	printStack(logFile);
	cout << FG_RED << "Specification A2 End" << RST << endl;

	cout << FG_ORANGE << "Specification B1 Start" << RST << endl;
	printArray(arrInt, logFile);
	printArray(arrFloat, logFile);
	numberSearch(arrInt, arrFloat, logFile);
	cout << FG_ORANGE << "Specification B1 End" << RST << endl;
}

void numberSearch(int intArray[], float fltArray[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	string tmpprompt = "Enter a number to see if it is in the array: ";
	float guess = promptFloatInRange(tmpprompt, RNG_MIN, RNG_MAX, logFile);
	int intGuess = guess;
	bool found = false;
	cout << "Checking integer array for " << intGuess << endl;
	for (int i=0; i<ARRAY_SIZE; i++){
		if (intArray[i] == guess){
			found = true;
		}
	}
	if (found){
		cout << "Number was found in the integer array!\n";
	}else{
		cout << "Number was NOT found in the integer array!\n";
	}

	found=false;
	float max = (1+COMP_TOLERANCE)*guess;
	float min = (1-COMP_TOLERANCE)*guess;
	cout << fixed << setprecision(3) << "Checking float array for a number between " << min << " and " << max << endl;
	for (int i=0; i<ARRAY_SIZE; i++){
		if (fltArray[i] > min && fltArray[i] < max){
			found = true;
		}
	}
	if (found){
		cout << "Number was found in the float array!\n";
	}else{
		cout << "Number was NOT found in the float array!\n";
	}
	announceFunction(__func__, F_END, logFile);
}

void arraySum(int intArray[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	int sum = 0;
	for (int i = 0; i < ARRAY_SIZE; i++){
		sum += intArray[i];
	}
	cout << "The total of all integers in the integer array is: " << sum << endl;;
	announceFunction(__func__, F_END, logFile);
}
void arraySum(float floatArray[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	float sum = 0;
	for (int i = 0; i < ARRAY_SIZE; i++){
		sum += floatArray[i];
	}
	cout << "The total of all floats in the float array is: " << sum << endl;
	announceFunction(__func__, F_END, logFile);
}

void arrayRev(int*& intArray, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	int* tmp = nullptr;
	tmp = new int[ARRAY_SIZE];
	cout << "Integer array contents before reversal:\n";
	printRow(intArray, logFile);
	for (int i = 0; i < ARRAY_SIZE; i++){
		tmp[ARRAY_SIZE-1-i] = intArray[i];
	}
	delete [] intArray;
	intArray = tmp;
	tmp = nullptr;
	cout << "\nInteger array contents after reversal:\n";
	printRow(intArray, logFile);
	announceFunction(__func__, F_END, logFile);
}
void arrayRev(float*& floatArray, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	float* tmp = nullptr;
	tmp = new float[ARRAY_SIZE];
	cout << "\n\nFloat array contents before reversal:\n";
	printRow(floatArray, logFile);
	for (int i = 0; i < ARRAY_SIZE; i++){
		tmp[ARRAY_SIZE-1-i] = floatArray[i];
	}
	delete [] floatArray;
	floatArray = tmp;
	tmp = nullptr;
	cout << "\nFloat array contents after reversal:\n";
	printRow(floatArray, logFile);
	announceFunction(__func__, F_END, logFile);
}

void arrayShiftRight(int*& intArray, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	int* tmp = nullptr;
	tmp = new int[ARRAY_SIZE];
	cout << "\n\nInteger array contents before shift:\n";
	printRow(intArray, logFile);
	for (int i = 0; i < ARRAY_SIZE; i++){
		if (i == ARRAY_SIZE-1){
			tmp[0] = intArray[i];
		}else{
			tmp[i+1] = intArray[i];
		}
	}
	delete [] intArray;
	intArray = tmp;
	tmp = nullptr;
	cout << "\nInteger array contents after shift:\n";
	printRow(intArray, logFile);
	announceFunction(__func__, F_END, logFile);
}
void arrayShiftRight(float*& floatArray, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	float* tmp = nullptr;
	tmp = new float[ARRAY_SIZE];
	cout << "\n\nFloat array contents before shift:\n";
	printRow(floatArray, logFile);
	for (int i = 0; i < ARRAY_SIZE; i++){
		if (i == ARRAY_SIZE-1){
			tmp[0] = floatArray[i];
		}else{
			tmp[i+1] = floatArray[i];
		}
	}
	delete [] floatArray;
	floatArray = tmp;
	tmp = nullptr;
	cout << "\nFloat array contents after shift:\n";
	printRow(floatArray, logFile);
	announceFunction(__func__, F_END, logFile);
}

void minAndMax(int intArr[],float fltArr[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	float min = RNG_MAX;
	float max = RNG_MIN;
	for (int i = 0; i<ARRAY_SIZE; i++){
		if (intArr[i] < min) min = intArr[i];
		if (intArr[i] > max) max = intArr[i];
	}
	cout << "The max integer is: " << max << endl;
	cout << "The min integer is: " << min << endl;
	cout << endl;

	min = RNG_MAX;
	max = RNG_MIN;
	for (int i = 0; i<ARRAY_SIZE; i++){
		if (fltArr[i] < min) min = fltArr[i];
		if (fltArr[i] > max) max = fltArr[i];
	}
	cout << "The max float is: " << max << endl;
	cout << "The min float is: " << min << endl;

	announceFunction(__func__, F_END, logFile);
}

void printArray(int intArr[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	printRow(intArr, logFile);
	cout << endl;
	logFile << endl;
	announceFunction(__func__, F_END, logFile);
}

void printArray(float fltArr[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	printRow(fltArr, logFile);
	cout << endl;
	logFile << endl;
	announceFunction(__func__, F_END, logFile);
	
}

void loadStack(ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	SpontaneousDigitDispenser& rng = rng.getInstance(); 
	for (int i=0; i<STACK_SIZE; i++){
		rng.dispenseInt();
		cout << "Pushing " << rng.getIntValue() << " to the stack.\n";
		tempstack.push(rng.getIntValue());
	}
	announceFunction(__func__, F_END, logFile);
}
void printStack(ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	int* tmp = new int[STACK_SIZE];
	for (int i=0; i<STACK_SIZE; i++){
		tmp[i] = tempstack.top();
		tempstack.pop();
	}
	cout << "Displaying contents of stack:\n";
	printStackRow(tmp, logFile);
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
		 << string('*',62) << endl << endl << endl;

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

void printStackRow(int inInt[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	char div = '=';

	for (int i=0; i<=STACK_SIZE; i++){
		cout << "|" << string(VAR_COL_WIDTH-4, div);
	}
	cout << "|" << endl;

	for (int i=0; i<=STACK_SIZE; i++){
		if (i){
		cout << "|" << setw(VAR_COL_WIDTH-4) << i-1;
		}else{
			cout << "|" << setw(VAR_COL_WIDTH-4) << "Index";
		}
	}
	cout << "|" << endl;
	for (int i=0; i<=STACK_SIZE; i++){
		cout << "|" << string(VAR_COL_WIDTH-4, div);
	}
	cout << "|" << endl;
    
    cout << fixed << setprecision(3) << "|";
	for (int i=0; i<STACK_SIZE; i++){
		if (i){
			cout << setw(VAR_COL_WIDTH-4) << inInt[i] << "|";	
		}else{
			cout << setw(VAR_COL_WIDTH-4) << " " << "|" << setw(VAR_COL_WIDTH-4) << inInt[i] << "|";
		}
		
	}

	cout << endl;
	for (int i=0; i<=STACK_SIZE; i++){
			cout << "|" << string(VAR_COL_WIDTH-4, div);
	}
    cout << "|" << endl;
	announceFunction(__func__, F_END, logFile);
}

void printRow(float inFlt[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	char div = '=';

	cout << "Contents of float array: \n";
	for (int i=0; i<=ARRAY_SIZE; i++){
		cout << "|" << string(VAR_COL_WIDTH, div);
	}
	cout << "|" << endl;

	for (int i=0; i<=ARRAY_SIZE; i++){
		if (i){
		cout << "|" << setw(VAR_COL_WIDTH) << i-1;
		}else{
			cout << "|" << setw(VAR_COL_WIDTH) << "Index";
		}
	}
	cout << "|" << endl;
	for (int i=0; i<=ARRAY_SIZE; i++){
		cout << "|" << string(VAR_COL_WIDTH, div);
	}
	cout << "|" << endl;
    
    cout << fixed << setprecision(3) << "|";
	for (int i=0; i<ARRAY_SIZE; i++){
		if (i){
			cout << setw(VAR_COL_WIDTH) << inFlt[i] << "|";	
		}else{
			cout << setw(VAR_COL_WIDTH) << " " << "|" << setw(VAR_COL_WIDTH) << inFlt[i] << "|";
		}
		
	}

	cout << endl;
	for (int i=0; i<=ARRAY_SIZE; i++){
			cout << "|" << string(VAR_COL_WIDTH, div);
	}
    cout << "|" << endl;
	announceFunction(__func__, F_END, logFile);
}

void printRow(int inInt[], ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	char div = '=';

	cout << "Contents of integer array: \n";
	for (int i=0; i<=ARRAY_SIZE; i++){
		cout << "|" << string(VAR_COL_WIDTH, div);
	}
	cout << "|" << endl;

	for (int i=0; i<=ARRAY_SIZE; i++){
		if (i){
		cout << "|" << setw(VAR_COL_WIDTH) << i-1 ;
		}else{
			cout << "|" << setw(VAR_COL_WIDTH) << "Index";
		}
	}
	cout << "|" << endl;
	for (int i=0; i<=ARRAY_SIZE; i++){
		cout << "|" << string(VAR_COL_WIDTH, div);
	}
	cout << "|" << endl;
    
    cout << fixed << setprecision(3) << "|";
	for (int i=0; i<ARRAY_SIZE; i++){
		if (i){
			cout << setw(VAR_COL_WIDTH) << inInt[i] << "|";	
		}else{
			cout << setw(VAR_COL_WIDTH) << " " << "|" << setw(VAR_COL_WIDTH) << inInt[i] << "|";
		}
		
	}

	cout << endl;
	for (int i=0; i<=ARRAY_SIZE; i++){
			cout << "|" << string(VAR_COL_WIDTH, div);
	}
    cout << "|" << endl;
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

float promptFloatInRange(string prompt, float min, float max, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	bool isValid = false;
	string inStr = "";
	float floatIn;

	while (!isValid){
		inStr = getPrompt(prompt, logFile);
		if (isInt(inStr, logFile) or isFloat(inStr, logFile)){
			floatIn = stof(inStr);
			if (floatIn >= min and floatIn <= max){
				isValid = true;
			}else{
				cout << FG_RED << to_string(floatIn) + " is not a valid option. Must be between " + to_string(min) + " and " + to_string(max) << RST;
			}
		}else{
			cout << FG_RED << "You have entered an invalid option [" + inStr + "]. Please try again...\n\n" << RST;
		}
	}
	announceFunction(__func__, F_END, logFile);
	return floatIn;
}

string getPrompt(string prompt, ofstream& logFile){
	announceFunction(__func__, F_START, logFile);
	string strIn;

	cout << prompt;
	cin >> strIn;
	announceFunction(__func__, F_END, logFile);
	return strIn;
}