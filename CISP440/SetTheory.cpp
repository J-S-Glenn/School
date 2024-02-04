// SetTheory.cpp -- Example C++ code template
// 2/3/2024	*Assignment Date*
// John Glenn

#include <iostream>		// Any other libraties, too
#include <set>
using namespace std;

// Global Variables
const set<int> U = {1, 2, 3, 4, 5 ,6 ,7, 8, 9, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 20};
int MENU_FIRST = 1;
int MENU_LAST = 6;
int EXIT = 6;
const string PROGRAM_NAME = "SetTheory.cpp";
const string PROGRAM_AUTHOR = "John Glenn";

// Function Prototypes
void calculateDifference(set<int>, set<int>);
void displayUnion(set<int>, set<int>);
void displayIntersection(set<int>, set<int>);
void displayComplements(set<int>, set<int>);
bool isInRange(int);
bool isInteger(string);
int main();
void printMenu(set<int>, set<int>);
void ProgramGreeting();
int promptMenu(set<int>, set<int>);
void printSetContents(set<int>, set<int>);
string setToString(set<int>);
void showSymmetricDifference(set<int>, set<int>);
bool validateSet(set<int>);
set<int> cloneSet(set<int>);
int main() {
    ProgramGreeting();

    set<int> setA = {1,2,9, 11, 13, 3,4,5};
    set<int> setB = {3,4,5,6,7};
    
    if (!validateSet(setA)){
        cout << "An item in setA is not valid. It is not included in the universal set.";
        exit(1);
    }else if (!validateSet(setB)){
        cout << "An item in setB is not valid. It is not included in the universal set.";
        exit(1);
    };

    int menuChoice = -1;
    do {
        menuChoice = promptMenu(setA, setB);
        switch(menuChoice){
            case 1:
                displayUnion(setA, setB);
                break;
            case 2:
                displayIntersection(setA, setB);
                break;
            case 3:
                displayComplements(setA, setB);
                break;
            case 4:
                calculateDifference(setA, setB);
                break;
            case 5:
                showSymmetricDifference(setA, setB);
                break;
            case 6:
                cout << "Now exiting..." << endl;
                exit(0);
            default:
                cout << "Something went wrong..." << endl;
                exit(1);
        }
        cout << endl << string(100, '*') << endl << endl;
        
    }
    while (menuChoice != EXIT);
}

void displayUnion(set<int> setA, set<int> setB){
    set<int> setOut = {};

    for (set<int>::iterator point=setA.begin(); point != setA.end(); point++){
        setOut.insert(*point);
    }

    for (set<int>::iterator point=setB.begin(); point != setB.end(); point++){
        setOut.insert(*point);
    }

    cout << "\nThe union of sets A and B is " << setToString(setOut) << endl;
}

void displayIntersection(set<int> setA, set<int> setB){
    set<int> setOut = {};
    for (set<int>::iterator point=setA.begin(); point != setA.end(); point++){
        
        if (setB.count(*point)){
            setOut.insert(*point);
        }
    }
    cout << "\nThe intersection of sets A and B is " << setToString(setOut) << endl;
}

void displayComplements(set<int> setA, set<int> setB){
    string outString = "";
    set<int> uSet = cloneSet(U);
    for (set<int>::iterator point=setA.begin(); point != setA.end(); point++){
        uSet.erase(*point);
    }
    cout << "\nThe complement of set A is " << setToString(uSet);

    uSet = cloneSet(U);
    for (set<int>::iterator point=setB.begin(); point != setB.end(); point++){
        uSet.erase(*point);
    }

    
    cout << "\nThe complement of set B is " << setToString(uSet) << endl;
}

void calculateDifference(set<int> setA, set<int> setB){
    set<int> outSet = cloneSet(setA);

    for (set<int>::iterator point=setB.begin(); point != setB.end(); point++){
        if (outSet.count(*point)){
            outSet.erase(*point);
        }
    }
    cout << "\nThe result of 'A - B' is " << setToString(outSet) << endl;
    outSet = cloneSet(setB);

    for (set<int>::iterator point=setA.begin(); point != setA.end(); point++){
        if (outSet.count(*point)){
            outSet.erase(*point);
        }
    }

    cout << "The result of 'B - A' is " << setToString(outSet) << endl;

}

set<int> cloneSet(set<int> srcSet){
    set<int> newSet = {};
    for (set<int>::iterator point=srcSet.begin(); point != srcSet.end(); point++){
        newSet.insert(*point);
    }
    return newSet;
}

void showSymmetricDifference(set<int> setA, set<int> setB){
    set<int> outSet = {};
    for (set<int>::iterator point=setA.begin(); point != setA.end(); point++){
        if (setB.count(*point)){
            continue;
        }else{
            outSet.insert(*point);
        }
    }
    for (set<int>::iterator point=setB.begin(); point != setB.end(); point++){
        if (setA.count(*point)){
            continue;
        }else{
            outSet.insert(*point);
        }
    }
    cout << "\nThe symmetric union (\u0394) of sets A and B is " << setToString(outSet) << endl;
}

bool isInteger(string inString){
    int strLength = inString.size();
    char currentChar;
    if (strLength > 0){
        for (char current=0; current < strLength - 1; current++){
            currentChar = inString[current];
            if (isdigit(currentChar)){
                continue;
            }else{
                cout << "'" << currentChar << "' is an invalid character...";
                return false;
            }
        }
    }else{
        cout << "No input detected...";
        return false;
    }
    return true;
}

string setToString(set<int> inSet){
    string outString = "{";
    bool first = true;
    for (set<int>::iterator point=inSet.begin(); point != inSet.end(); point++){
        if (!first){
            outString += ", ";
        }
        outString += to_string(*point);
        first = false;
    }
    outString += "}";
    return outString;
}

void printSetContents(set<int> setA, set<int> setB)
{
    cout << "SetA: " << setToString(setA) << endl;
    cout << "SetB: " << setToString(setB) << endl;
}

void printMenu(set<int> setA, set<int> setB){
    printSetContents(setA, setB);
    cout << "\n1. Display Union of A and B." << endl;
    cout << "2. Display Intersection of A and B." << endl;
    cout << "3. Display Complements of A and B." << endl;
    cout << "4. Calculate difference between A and B, B and A." << endl;
    cout << "5. Display symmetric difference between A and B." << endl;
    cout << "6. Exit";
}

void ProgramGreeting() {
	cout << "Initiallizing...\n\nDecrypting...\n\nFeeding the dogs....\n\n"
	     << "Contemplating life choices...\n\nInitialization complete!\n\n"
	     << "=============================================================="
		 << "\nProgram Name: " << PROGRAM_NAME
	     << "\nAuthor:" << PROGRAM_AUTHOR
		 << "\n==============================================================\n\n";
}
int promptMenu(set<int> setA, set<int> setB){
    string choice;
    int intChoice;
    bool isInt = true;
    bool isValid = true;
    do {
        printMenu(setA, setB);
        cout << "\n\nWhat would you like to do? ";
        cin >> choice;
        isInt = isInteger(choice);
        intChoice = (isInt) ? stoi(choice):0;
        isValid = isInRange(intChoice);
    }
    while (!isValid or !isInt);

    return intChoice;
}


bool isInRange(int choice){
    return (choice <= MENU_LAST and choice >= MENU_FIRST);
}

bool validateSet(set<int> testSet){
    for (set<int>::iterator point=testSet.begin(); point != testSet.end(); point++){
        if (U.count(*point)){
            continue;
        }else{
            cout << "\n\033[1;31mERROR: \033[0m" << *point << " is not part of the universal set.\n";
            return false;
        }
    }
    return true;
}