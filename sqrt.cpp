/*******************************************************************************
 * Name    : sqrt.cpp
 * Author  : Isabella Stone
 * Version : 1.0
 * Date    : September 1, 2021
 * Description : Computes the square root of the command-line argument.
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <iomanip>
#include <limits>
#include <sstream>
using namespace std;


double sqrt(double num, double epsilon) {
	//first check that num is vaild integer
	if (num < 0) {
		return numeric_limits<double>::quiet_NaN();
	}
	
	//if num is 0 or 1, return num
	if (num == 0 || num == 1) {
		return num; 
	}
	
	double last_guess = num;
	double next_guess = (last_guess + (num/last_guess)) / 2;
	while (!(abs(last_guess - next_guess) <= epsilon)) {
		last_guess = next_guess;
		next_guess = (last_guess + (num/last_guess)) / 2;
	}

	return next_guess;
}

int main(int argc, char* argv[]) {
	double num, epsilon;
	istringstream iss;
	//check for right amount of args
	if (argc > 3 || argc < 2) {
		cerr << "Usage: " << argv[0] << " <value> [epsilon]" << endl;
		return 1;
	}

	//if epsilon not given
	if (argc == 2) {
		epsilon = 0.0000001;
		//check first arg
		iss.str(argv[1]);  
		if (!(iss >> num)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1; 
		}

	}
	//if epsilon is given
	else {
		//check first arg
		iss.str(argv[1]);  
		if (!(iss >> num)) {
			cerr << "Error: Value argument must be a double." << endl;
			return 1; 
		}
		
		//check second arg
		iss.clear();
		iss.str(argv[2]);
		if (!(iss >> epsilon)) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1; 
		}
		//then if epsilon was made 0 or negative
		if (epsilon <= 0) {
			cerr << "Error: Epsilon argument must be a positive double." << endl;
			return 1;
		}
		
	}
	
	cout << fixed << setprecision(8) << sqrt(num, epsilon) << endl;
	return 0;
}
