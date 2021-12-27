/*******************************************************************************
 * Name        : unique.cpp
 * Author      : Isabella Stone
 * Date        : 9/20/21
 * Description : Determining uniqueness of chars with int as bit vector.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <cctype>

using namespace std;

bool is_all_lowercase(const string &s) {
    // TODO: returns true if all characters in string are lowercase
    // letters in the English alphabet; false otherwise.
    // range of 97-122 for lowercase letters
    int val;
    for (size_t i = 0; i < s.size(); i++) {
        val = int(s[i]);
        //if out of range, it's not a lowercase letter
        if (val<97 || val>122) {
            //cerr << "Error: String must contain only lowercase letters." << endl;
            return false;
        }
    }
    //if no bad vals found, return true
    return true;
}

bool all_unique_letters(const string &s) {
    // TODO: returns true if all letters in string are unique, that is
    // no duplicates are found; false otherwise.
    // You may use only a single int for storage and work with bitwise
    // and bitshifting operators.
    // No credit will be given for other solutions.
    unsigned int vector = 0;
    unsigned int setter;

    for (size_t i = 0; i < s.length(); i++) {
        setter = 1 << (int('a') - int(s[i]));
        //if vector&setter not equal to 0, means there's a repeat
        if ((vector & setter) != 0) {
            cerr << "Duplicate letters found." << endl;
            return false;
        }
        vector = vector | setter;
    }
    //if never found a duplicate, now return true
    cout << "All letters are unique." << endl;
    return true;
}

int main(int argc, char * const argv[]) {
    // TODO: reads and parses command line arguments.
    // Calls other functions to produce correct output.

    //if there's no input or multiple words
    if (argc==1 || argc>2) {
        cerr << "Usage: " << argv[0] << " <string>" << endl;
        return 1;
    }
    //check if all lowercase
    if (! is_all_lowercase(argv[1])) {
        cerr << "Error: String must contain only lowercase letters." << endl;
        return 1;
    }
    //check if all unique
    all_unique_letters(argv[1]);
    return 0;
}
