// DrakeEq.cpp -- HW2
// John Glenn, CISP360
// 2/2/2024

#include <iostream>
#include <iomanip>

using namespace std;

// Global Variables
const string PROGRAM_NAME = "DrakeEq.cpp";
const string PROGRAM_AUTHOR = "John Glenn";

// Specification C3 - Constant Variables
const int   STR_CR = 7,        // rate of star creation (R)
            VAR_COL_WIDTH = 15;     // Width of columns in variable table
const float PCT_Str_WPlanet = 0.4,  // percentage of stars with planets (p)
            PCT_WLife = .13;        // percent plantes which actually develop life (f)

const string COIL_HDR = "CHANCE OF INTELLIGENT LIFE";
const string SENS_ANALYSIS_HDR = "SENSITIVITY ANALYSIS";



// Function Prototypes
void ProgramGreeting();
float runDrakeEquation(int, float, float, float);
void printHeader(string);
void printVariables(int, float, float, float);

int main() {
	ProgramGreeting();  

    // Specification C2 - Variable Initialization
    // Specification C1 - Variable Declaration
    int   expCivilianLT = 10000;   // expected civilivation lifetime (years) (L)
    float cntAvgPWLife = .9,   // avg number of planets capable of supporting life per star (n)
          pctWIntelLife = .5,  // percent develop intelligent life (i)
          pctComm = .8,        // percent willing to communicate (c)
          etCiv = 0;   // Number of potential alien civilizations (N)

    // Specification B1 - Calculation
    etCiv = runDrakeEquation(expCivilianLT, cntAvgPWLife, pctWIntelLife, pctComm);

    // Specification B2 - Drake Equation Heading
    printHeader(COIL_HDR);
    cout << "Estimated number of detectable civilizations in the universe:\n";
    cout << fixed << setprecision(3) << etCiv << endl;

    printHeader(SENS_ANALYSIS_HDR);
    cout << "Double Results:" << etCiv * 2 << endl;
    cout << "Half Results: " << etCiv / 2 << endl;

    printVariables(expCivilianLT, cntAvgPWLife, pctWIntelLife, pctComm);
}

void printVariables(int expCivilianLT, float cntAvgPWLife, float pctWIntelLife, float pctComm){
    cout << "\n|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
    cout << "|" << setw(VAR_COL_WIDTH) << "Variable" << "|" << setw(VAR_COL_WIDTH) << "Value" << "|\n" ;
    cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
    cout << "|" << setw(VAR_COL_WIDTH) << "expCivilianLT" << "|" << setw(VAR_COL_WIDTH) << expCivilianLT << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
    cout << "|" << setw(VAR_COL_WIDTH) << "cntAvgPWLife" << "|" << setw(VAR_COL_WIDTH) << cntAvgPWLife << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
    cout << "|" << setw(VAR_COL_WIDTH) << "pctWIntelLife" << "|"  << setw(VAR_COL_WIDTH) << pctWIntelLife << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
    cout << "|" << setw(VAR_COL_WIDTH) << "pctComm" << "|" << setw(VAR_COL_WIDTH) << pctComm << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
    cout << "|" << setw(VAR_COL_WIDTH) << "STR_CR_RATE" << "|" << setw(VAR_COL_WIDTH) << STR_CR << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
    cout << "|" << setw(VAR_COL_WIDTH) << "PCT_Str_WPlanet" << "|" << setw(VAR_COL_WIDTH) << setw(VAR_COL_WIDTH) << PCT_Str_WPlanet << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
    cout << "|" << setw(VAR_COL_WIDTH) << "PCT_WLife" << "|" << setw(VAR_COL_WIDTH) << setw(VAR_COL_WIDTH) << PCT_WLife << "|\n";
    cout << "|" << string(VAR_COL_WIDTH,'-') << "|" << string(VAR_COL_WIDTH,'-') << "|\n";
}

float runDrakeEquation(int expCivilianLT, float cntAvgPWLife, float pctWIntelLife, float pctComm)
{
    return STR_CR * PCT_Str_WPlanet * PCT_WLife * expCivilianLT * cntAvgPWLife * pctWIntelLife * pctComm;
}

void ProgramGreeting() {
	// ProgramGreeting1
	cout << "Initiallizing...\n\nDecrypting...\n\nFeeding the dogs....\n\n"
	     << "Contemplating life choices...\n\nInitialization complete!\n\n"
	     << "=============================================================="
		 << "\nProgram Name: " << PROGRAM_NAME
	     << "\nAuthor:" << PROGRAM_AUTHOR
		 << "\n==============================================================\n\n";
}

void printHeader(string header){
    cout << endl << header;
    cout << endl << string(header.size(),'=') << endl;
}


/*

*/


