// AlGoresRevenge.cpp
// 2/15/2024
// John Glenn

#include <iostream>
#include <iomanip>
using namespace std;

// Global Variables
const string PROGRAM_NAME = "AlGoresRevenge.cpp";
const string PROGRAM_AUTHOR = "John Glenn";

// Average temperatures over past year
const float JLY_TMP_AVG_NYC = 85.0;   // New York City
const float JLY_TMP_AVG_DNV = 88.0;   // Denver
const float JLY_TMP_AVG_PHX = 106.0;  // Phoenix
const float JLY_TMP_AVG_SAC = 92.0;   // Sacramento

// Temperature and Ocean level increase constants
const float OCEAN_INC_PER_YEAR = 3.1; // milimeters / year;
const float TEMP_INC_PER_YEAR = .13;  // Degrees / year

// Speciﬁcation C1 - const Conversions
// Conversion constants
const float MM2IN = 0.03937;      // Millimeters to inches
const float FTC = (5.0/9.0);      // Fahrenheit to Celcsius

const int VAR_COL_WIDTH = 25;     // Width of columns in tableS

// Function Prototypes
void autoHeader(string);
float ftoc(float);
void genUnderline(string);
void oceanRiseEval(int);
void printRow(string, string, bool=false);
void ProgramGreeting();
string roundStr(string, int=3);
string strToUpper(string);
void tempRiseEval(int);

int main() {
	int yrCount = 15;  // Number of years to forcast
	ProgramGreeting();

	// Speciﬁcation C2 - 5 year ocean rise
	autoHeader("Yearly AVG Temps in July");
	tempRiseEval(yrCount);

	// Speciﬁcation C3 - 5 year temp 
	autoHeader("Yearly Ocean Level Increases");
	oceanRiseEval(yrCount);
	
	return 0;
}

// Speciﬁcation B3 - Auto Heading Function
void autoHeader(string header){
	cout << strToUpper(header) << endl;
	genUnderline(header);
}

float ftoc(float fahrenheit){
	return (fahrenheit - 32.0) * FTC; 
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

void printRow(string inStr, string inStr2, bool printCap){
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";    
    };
    cout << "|" << setw(VAR_COL_WIDTH) << inStr << "|" << setw(VAR_COL_WIDTH) << inStr2 << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
}

void printTempForcast(float startTemp, string location, int years){
	printRow(location + " Forcast", "Degrees F (C)",true);
	for (int count = 0; count < years; count++){
		startTemp += TEMP_INC_PER_YEAR;
		// Speciﬁcation B2 - Mixed temperature output
		printRow("Year " + to_string(count+1),roundStr(to_string(startTemp)) + " F ("+ roundStr(to_string(ftoc(startTemp))) + " C)");
	}
	cout << endl;
}

void oceanRiseEval(int years){
	float oceanLevel = 0;
	// Specification A1 - Ocean Rise Table
	printRow("Ocean Level Forcast", "Millimeters (Inches)",true);
	for (int count = 0; count < years; count++){
		oceanLevel += OCEAN_INC_PER_YEAR;
		printRow("Year " + to_string(count+1),roundStr(to_string(oceanLevel)) + " mm ("+ roundStr(to_string(MM2IN * oceanLevel)) + " In)");
	}
	cout << endl;
}

void ProgramGreeting() {
	// ProgramGreeting1
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

void tempRiseEval(int years){
	// Specification A2 - July Temp Table
	printTempForcast(JLY_TMP_AVG_DNV, "Denver", years);
    printTempForcast(JLY_TMP_AVG_NYC, "New York City", years);
	printTempForcast(JLY_TMP_AVG_PHX, "Phoenix", years);
	printTempForcast(JLY_TMP_AVG_SAC, "Sacramento", years);
}