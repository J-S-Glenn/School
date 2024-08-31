// Pig.cpp -- Homework 1
// 8/30/2024
// John Glenn
#include <ctime>
#include <fstream>
#include <iomanip>
#include <iostream>		// Any other libraties, too
#include <string>
using namespace std;


class jlogger{
	private:
		string log_file;
		string authName;
		string appName;
		string F_START = "Started";
		string F_END = "Ended";
		ofstream obLogFile;

		void initLogFile(){
			time_t t = std::time(nullptr);
			tm tm = *std::localtime(&t);
			cout << "New log started at " << put_time(&tm, "%F %T") << endl;
			obLogFile << "New log started at " << put_time(&tm, "%F %T") << endl;
		}

	public:
        static jlogger& getInstance(){
			      static jlogger instance;
				  return instance;
        }
        
		void initialize(string app_Name = "My Program", string auth_Name = "John S. Glenn Jr", string logfile = "log.txt"){
			appName = app_Name;
			authName = auth_Name;
			log_file = logfile;
			obLogFile.open(log_file);
			initLogFile();
			ProgramGreeting();
        }

		void announceFunction(string funcName, string action){
			time_t t = std::time(nullptr);
			tm tm = *std::localtime(&t);
			obLogFile <<  put_time(&tm, "%F %T") <<  "\tFunction " << funcName << "() " << action << "\n";
		}

		void ProgramGreeting() {
			announceFunction(__func__, F_START);
			std::time_t t = std::time(nullptr);
			std::tm tm = *std::localtime(&t);
			obLogFile << string('*',62) << "\nWelcome to  " << appName << "!!" << endl 
			<< "Author: " << authName << endl
			<< "Date: " << put_time(&tm, "%A %d, %Y") << '\n'
			<< string('*',62) << endl << endl << endl;
			cout << string('*',62) << "\nWelcome to  " << appName << "!!" << endl 
			<< "Author: " << authName << endl
			<< "Date: " << put_time(&tm, "%A %d, %Y") << '\n'
			<< string('*',62) << endl;
			announceFunction(__func__, F_END);
		}
};

class SpontaneousDigitDispenser{
  private:
  	const static int DEFAULT_MIN = 1;
	const static int DEFAULT_MAX = 10;
    int intValue = 0;
    float fltValue = 0;

    SpontaneousDigitDispenser(){
      std::srand(time(nullptr));  // Seed with current time
    }

  public:
    static SpontaneousDigitDispenser& getInstance() {
      static SpontaneousDigitDispenser instance;
          return instance;
      }

    int dispenseInt(int min = DEFAULT_MIN, int max = DEFAULT_MIN){
      // Generate a random digit between 'min' and 'max' inclusive
      intValue = min + rand() % (max - min + 1);
      return intValue;
    }

    float dispenseFlt(int min = DEFAULT_MIN, int max = DEFAULT_MIN){
      // Generate a random digit between 'min' and 'max' inclusive
      int randInt = rand();
      fltValue = (min + static_cast<double>(randInt) / RAND_MAX * (max - min));
      return fltValue;
    }
};

class pigGame{
	private:
		SpontaneousDigitDispenser& dice = dice.getInstance();
		int game_count;
		string F_START = "Started";
		string F_END = "Ended";
		jlogger& myScribe = myScribe.getInstance();
			void exitGame(){
			myScribe.announceFunction(__func__,"Game Exiting...");
		}
		int D6();
		int RandomNumber(int, int);
	public:
		pigGame(){
			myScribe.announceFunction(__func__, "Initializing Pig");
			int someNumber = D6();
			myScribe.announceFunction(__func__, "Playing Pig");
			someNumber = D6();
			someNumber = D6();
			someNumber = D6();
			myScribe.announceFunction(__func__, "Exiting Pig");
		}


};

int main() {

    // Set up logging
    clock_t start = clock();
    jlogger& myScribe = myScribe.getInstance();
	myScribe.initialize("Pig");

    myScribe.announceFunction(__func__, "Started");
	pigGame myGame = pigGame();
    myScribe.announceFunction(__func__, "Ended");

	clock_t end = clock();

  	double total_runtime = double(end-start) / CLOCKS_PER_SEC;
  	cout << "\n\nTotal runtime: " << total_runtime << " sec";
  	myScribe.announceFunction(__func__, "Total runtime: " + to_string(total_runtime) + " sec");
}

int pigGame::D6()
{
	myScribe.announceFunction(__func__, F_START);
	cout << "Rolling dice!\n";
	int result = RandomNumber(1,6);
	cout << "Player has rolled a " << result << endl;
	myScribe.announceFunction(__func__, F_END);
    return result;
}

int pigGame::RandomNumber(int hi, int low)
{
	myScribe.announceFunction(__func__, F_START);
	int result = dice.dispenseInt(hi,low);
	myScribe.announceFunction(__func__, ("Getting number between " + to_string(low) + " and " + to_string(hi)));
	myScribe.announceFunction(__func__, ("Number generated:  " + to_string(result)));
	myScribe.announceFunction(__func__, F_END);
	return result;
}
