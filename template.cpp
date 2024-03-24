// C++Tem.cpp -- Example C++ code template
// 1/1/2020	*Assignment Date*
// John Glenn

#include <iostream>		// Any other libraties, too
#include <iomanip>
using namespace std;

struc somestruct {

};

Class someclass {

};

// Global Variables
const string PROGRAM_NAME = "CurrencyConverter.cpp";
const string PROGRAM_AUTHOR = "John Glenn";

// Function Prototypes
void ProgramGreeting();		// All programs will have this method
void Unittest();			// All P400 programs should have this, too


int main() {
	ProgramGreeting();		// Should go somewhere around here
	Unittest();				// Follows ProgrmGreeting
	
}


void ProgramGreeting() {
	cout << "Initiallizing...\n\nDecrypting...\n\nFeeding the dogs....\n\n"
	     << "Contemplating life choices...\n\nInitialization complete!\n\n"
	     << string('*',62) << "\nProgram Name: " << PROGRAM_NAME << "\nAuthor:" 
		 << PROGRAM_AUTHOR << endl << string('*',62) << endl << endl;
}

void Unittest() {
// All test code here
}