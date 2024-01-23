// BinaryToDecimal.cpp
// John Glenn - CISP310
// 1/23/2024

#include <iostream>
#include <string>
using namespace std;

void binaryToHexadecimal(string inputString);

int main(){
    string inputString;  // String provided by user that is to be converted

    // Priming Read
    cout << "\nPlease enter your binary number and press enter or 'q' to quit: ";
    cin >> inputString;

    while (inputString != "q"){
        binaryToHexadecimal(inputString);
        cout << "\nPlease enter your binary number and press enter or 'q' to quit: ";
        cin >> inputString;
    }
    cout << "Now Exiting...";
}

void binaryToHexadecimal(string inputString){

    int currentPower = 1;
    char currentChar = '0';
    int currentInt = 0;
    int decimalOutput = 0;

    for (int i=inputString.size()-1; i>=0; i--){
        currentChar = inputString[i];
        if (currentChar == '1'){
            currentInt = 1;
        }else if (currentChar == '0'){
            currentInt = 0;
        }else{
            cout << "'" << currentChar << "' is not a valid character. Aborting...";
        }
        decimalOutput += (currentInt * currentPower);
        currentPower *= 2;
    }
    
    cout << inputString << " is " << hex << decimalOutput << " in hexadecimal." ;
}