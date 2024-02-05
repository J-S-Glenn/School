// DrakeEq.cpp -- HW2
// John Glenn, CISP360
// 2/4/2024

#include <iostream>
#include <iomanip>

using namespace std;

// Global Variables
const string PROGRAM_NAME = "DrakeEq.cpp";
const string PROGRAM_AUTHOR = "John Glenn";

// Speciﬁcation C3 - Constant Variables
const int   STR_CR = 7,             // rate of star creation (R)
            VAR_COL_WIDTH = 20;     // Width of columns in variable table
const float PCT_Str_WPlanet = 0.4,  // percentage of stars with planets (p)
            PCT_WLife = .13;        // percent plantes which actually develop life (f)

const string COIL_HDR = "CHANCE OF INTELLIGENT LIFE";
const string SENS_ANALYSIS_HDR = "SENSITIVITY ANALYSIS";



// Function Prototypes
void ProgramGreeting();
float runDrakeEquation(int, float, float, float);
void printDrakeSummary(float);
void printHeader(string);
void printRow(string, float, bool=false);
void printRow(string, int, bool=false);
void printRow(string, string, bool=false);
void printSensSummary(float, float);
void printVariables(int, float, float, float);

int main() {
	ProgramGreeting();  

    // Speciﬁcation C2 - Variable Initialization
    // Speciﬁcation C1 - Variable Declaration
    int   expCivilianLT = 10000; // expected civilivation lifetime (years) (L)
    float cntAvgPWLife = .9,     // avg number of planets capable of supporting life per star (n)
          pctWIntelLife = .5,    // percent develop intelligent life (i)
          pctComm = .8,          // percent willing to communicate (c)
          etCiv = 0;             // Number of potential alien civilizations (N)

    // Speciﬁcation B1 - Calculation
    etCiv = runDrakeEquation(expCivilianLT, cntAvgPWLife, pctWIntelLife, pctComm);

    // Specification B2 - Drake Equation Heading
    printHeader(COIL_HDR);
    cout << "Estimated number of detectable civilizations in the universe:\n";
    cout << fixed << setprecision(3) << etCiv << endl;

    // Speciﬁcation B3 - Double and Half Output and Headings
    printHeader(SENS_ANALYSIS_HDR);
    cout << "Double Results:" << etCiv * 2 << endl;
    cout << "Half Results: " << etCiv / 2 << endl << endl;

    
    // Specification A1 - Variable Table
    printVariables(expCivilianLT, cntAvgPWLife, pctWIntelLife, pctComm);

    // Specification A2 - Output Table
    printDrakeSummary(etCiv);

    // Specification A3 - Sensitivity Analysis Table
    printSensSummary(etCiv / 2, etCiv * 2);
}

void printVariables(int expCivilianLT, float cntAvgPWLife, float pctWIntelLife, float pctComm){
    printRow("Variable Name", "Value", true); 
    printRow("expCivilianLT", expCivilianLT);
    printRow("cntAvgPWLife", cntAvgPWLife);
    printRow("pctWIntelLife",pctWIntelLife);
    printRow("pctComm",pctComm);
    printRow("STR_CR_RATE",STR_CR);
    printRow("PCT_Str_WPlanet",PCT_Str_WPlanet);
    printRow("PCT_WLife",PCT_WLife);
    cout << endl;
}

float runDrakeEquation(int expCivilianLT, float cntAvgPWLife, float pctWIntelLife, float pctComm)
{
    return STR_CR * PCT_Str_WPlanet * PCT_WLife * expCivilianLT * cntAvgPWLife * pctWIntelLife * pctComm;
}

void printDrakeSummary(float result){
    printRow("Drake Equation Value",to_string(result), true);
    cout << endl;
}

void ProgramGreeting() {
	// ProgramGreeting1
	cout << "Initiallizing...\n\nDecrypting...\n\nFeeding the dogs....\n\n"
	     << "Contemplating life choices...\n\nInitialization complete!\n\n"
	     << "=============================================================="
		 << "\nProgram Name: " << PROGRAM_NAME
	     << "\nAuthor:" << PROGRAM_AUTHOR
		 << "\n==============================================================\n";
}
void printRow(string inStr, float inStr2, bool printCap){
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";    
    };
    cout << "|" << setw(VAR_COL_WIDTH) << inStr << "|" << setw(VAR_COL_WIDTH) << inStr2 << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,div) << "|" << string(VAR_COL_WIDTH,div) << "|\n";
}
void printRow(string inStr, int inStr2, bool printCap){
    char div = (printCap) ? '=':'-';
    if (printCap){
        cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";    
    };
    cout << "|" << setw(VAR_COL_WIDTH) << inStr << "|" << setw(VAR_COL_WIDTH) << inStr2 << "|\n";
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
void printHeader(string header){
    cout << endl << header;
    cout << endl << string(header.size(),'=') << endl;
}
void printSensSummary(float halved, float doubled){
    printRow(SENS_ANALYSIS_HDR, "", true); 
    printRow("Double Result", doubled);
    printRow("Half Result", halved);
}

/*
Initiallizing...

Decrypting...

Feeding the dogs....

Contemplating life choices...

Initialization complete!

==============================================================
Program Name: DrakeEq.cpp
Author:John Glenn
==============================================================

CHANCE OF INTELLIGENT LIFE
==========================
Estimated number of detectable civilizations in the universe:
1310.400

SENSITIVITY ANALYSIS
====================
Double Results:2620.800
Half Results: 655.200

|====================|====================|
|       Variable Name|               Value|
|====================|====================|
|       expCivilianLT|               10000|
|--------------------|--------------------|
|        cntAvgPWLife|               0.900|
|--------------------|--------------------|
|       pctWIntelLife|               0.500|
|--------------------|--------------------|
|             pctComm|               0.800|
|--------------------|--------------------|
|         STR_CR_RATE|                   7|
|--------------------|--------------------|
|     PCT_Str_WPlanet|               0.400|
|--------------------|--------------------|
|           PCT_WLife|               0.130|
|--------------------|--------------------|

|====================|====================|
|Drake Equation Value|         1310.400024|
|====================|====================|

|====================|====================|
|SENSITIVITY ANALYSIS|                    |
|====================|====================|
|       Double Result|            2620.800|
|--------------------|--------------------|
|         Half Result|             655.200|
|--------------------|--------------------|
*/


