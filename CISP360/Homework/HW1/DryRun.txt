// Speciﬁcation C2 – Source File Header
// DryRun.cpp -- HW1
// John Glenn, CISP360
// 1/19/2024

#include <iostream>

using namespace std;

// Global Variables
string PROGRAM_NAME = "DryRun.cpp";
string PROGRAM_AUTHOR = "John Glenn";

// Function Prototypes
void ProgramGreeting();

int main() {
	// Speciﬁcation C1 – Program Greeting
	ProgramGreeting();  

	// Speciﬁcation B1 – Variables
	int johnsInt       = 88;
	float johnsFloat   = 132442355.24145656;
	double johnsDouble = 11324131343.2565456;
	bool johnsBool     = false;
	char johnsChar     = 'J';
	string johnsString = "This is my fancy string!";

	// Speciﬁcation B2 – Output Variables
	cout << "Displaying Current Variables...\n"
	     << "\njohnsInt:\t"    << johnsInt
		 << "\njohnsFloat:\t"  << johnsFloat
		 << "\njohnsDouble:\t" << johnsDouble
		 << "\njohnsBool:\t"   << johnsBool
		 << "\njohnsChar:\t"   << johnsChar
		 << "\njohnsString:\t" << johnsString << endl;
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

// Specification A - Commented Sample Run
/*
Initiallizing...

Decrypting...

Feeding the dogs....

Contemplating life choices...

Initialization complete!

==============================================================
Program Name: DryRun.cpp
Author:John Glenn
==============================================================

Current Variables
johnsInt:   88
johnsFloat: 1.32435e+06
johnsDouble:    11223.3
johnsBool:  0
johnsChar:  J
johnsString:    This is my fancy string!
*/