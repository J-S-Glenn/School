// SetTheory.cpp -- Example C++ code template
// 1/1/2020	*Assignment Date*
// John Glenn

#include <iostream>		// Any other libraties, too
using namespace std;

// Global Variables
int MENU_FIRST = 1;
int MENU_LAST = 6;
// Function Prototypes
void printMenu();
int promptMenu();
bool isInRange(int, int, int);
bool isInteger(string);
int main() {
    do {
        int menuChoice = promptMenu();
        switch(menuChoice){
            case 1:
                continue;
            case 2:
                continue;
            case 3:
                continue;
            case 4:
                continue;
            case 5:
                continue;
            case 6:
                cout << "Now exiting...";
            default:
                cout << "Something went wrong...";
        }
    }
    (while menuChoice != 6)
    
	
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

void printMenu(){
    cout << "1. Display Union" << endl;
    cout << "2. Display Intersection" << endl;
    cout << "3. Display Complement" << endl;
    cout << "4. Calculate difference" << endl;
    cout << "5. Display symmetric difference" << endl;
    cout << "6. Exit"
}
int promptMenu(){
    string choice;
    int intChoice;
    bool isInt = true;
    bool isValid = true;
    do {
        printMenu();
        cout << "\n\nWhat would you like to do?";
        cin >> choice;
        isInt = isInteger(choice);
        intChoice = (isInt) ? stoi(choice):0;
        isValid = isInRange(intChoice);
    }
    while (!isValid or !isInt);

    return stoi(choice);
}

bool isInRange(int choice){
    return (choice <= MENU_LAST and choice >= MENU_FIRST);
}
