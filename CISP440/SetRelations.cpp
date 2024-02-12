// SetTheory.cpp -- Example C++ code template
// 2/3/2024	*Assignment Date*
// John Glenn

#include <iostream>
#include <iomanip>
#include <set>
#include <tuple>
#include <vector>
using namespace std;

const string PROGRAM_NAME = "SetRelations.cpp";
const string PROGRAM_AUTHOR = "John Glenn";
const int COL_WIDTH = 8;

typedef vector< tuple<int, char> > tuple_list;

// Function Prototypes
int main();
void ProgramGreeting();
void question1();
void question2();
int main(){
    ProgramGreeting();

    question1();
    question2();

    return 0;


}

void ProgramGreeting() {
	cout << "Initiallizing...\n\nDecrypting...\n\nFeeding the dogs....\n\n"
	     << "Contemplating life choices...\n\nInitialization complete!\n\n"
	     << "=============================================================="
		 << "\nProgram Name: " << PROGRAM_NAME
	     << "\nAuthor:" << PROGRAM_AUTHOR
		 << "\n==============================================================\n\n";
}

void question1(){
    int currentNumber;
    int currentChar;
    
    // Input from assignment
    set<int> numbers={1, 2, 3, 4 };
    set<char> chars={ 'a', 'b', 'c'};
    tuple_list relations = { make_tuple(1,'a') , make_tuple( 2,'c') , make_tuple(3, 'b') };
    tuple_list::const_iterator ptr = relations.begin();
    cout << "Size is: " << relations.end() - ptr << endl;
    // Declare Matrix
    // while (ptr != relations.end()){
    //     cout << get<int>(ptr[0]) << ", " << get<char>(ptr[0])<<endl;
    //     ptr++;
    // }

    cout << "\n=========================";
    cout << "\n|     |  A  |  B  |  C  |";

    for (int row = 0; row < numbers.size(); row++){
        currentNumber = get<int>(ptr[row]);
        cout << "\n|    " << row + 1;
        for (int col = 'a'; col < 'd'; col++){
            currentChar = get<char>(ptr[row]);
            //cout << "Int: " << row << "Char: " << char(col) << endl;
            if ((currentNumber == row+1) and (currentChar == char(col))){
                cout << "|" << setw(5) << 1;
            }else{
                cout << "|" << setw(5) << 0;
            } 
        }
        cout << "|\n=========================";
    }

    cout << "\nDONE";
}

void question2(){

}
