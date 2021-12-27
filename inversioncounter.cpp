/*******************************************************************************
 * Name        : inversioncounter.cpp
 * Author      : Isabella Stone
 * Version     : 1.0
 * Date        : 10/24/21
 * Description : Counts the number of inversions in an array.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <algorithm>
#include <sstream>
#include <vector>
#include <cstdio>
#include <cctype>
#include <cstring>

using namespace std;


// Function prototype.
static long mergesort(int array[], int scratch[], int low, int high);

//Counts the number of inversions in an array in theta(n^2) time.
long count_inversions_slow(int array[], int length) {
    long inversions = 0;
    //look at each element
     for (int i = 0; i < length; i++) {
         //look at each element after it
        for (int j = i+1; j < length; j++) {
            if (array[i] > array[j]) {
                inversions++;
            }
        }
    }
    return inversions;
}

//Counts the number of inversions in an array in theta(n lg n) time.
long count_inversions_fast(int array[], int length) {
    // TODO
    // Hint: Use mergesort
    int* scratch = new int[length];
    long answer = mergesort(array, scratch, 0, length-1);
    delete [] scratch;
    return answer;
}

static long mergesort(int array[], int scratch[], int low, int high) {
    // TODO
    long inversions = 0;
    int mid, L, H;
    if (low < high) {
        mid = low + ((high - low) / 2);
        //accumulate inversions from each half 
        inversions += mergesort(array, scratch, low, mid);
        inversions += mergesort(array, scratch, mid+1, high);
        //merge 2 sorted halves into a whole
        L = low;
        H = mid + 1;
        for (int i = low; i <= high; i++) {
            if (L<=mid && (H>high || array[L] <= array[H])) {
                scratch[i] = array[L];
                L++;
            } 
            else {
                scratch[i] = array[H];
                H++;
                //if taking from high side increment inversions
                inversions += (mid - L + 1);
            }
        }
        for (int i = low; i <= high; i++) {
            array[i] = scratch[i];
        }
    }
    return inversions;
}


int main(int argc, char *argv[]) {
    // TODO: parse command-line argument

    //if not enough arguments passed
    if (argc > 2) {
        cerr << "Usage: " << argv[0] << " [slow]" << endl;
        return 1;
    }

    //if argc is 2 and argv1 is not slow, cerr unrecognized val
    if (argc==2 && (string(argv[1]).compare("slow") != 0)) {
        cerr << "Error: Unrecognized option '" << argv[1] << "'." << endl;
        return 1;
    }

    cout << "Enter sequence of integers, each followed by a space: " << flush;
    
    istringstream iss;
    int value, index = 0;
    vector<int> values;
    string str;
    str.reserve(11);
    char c;
    while (true) {
        c = getchar();
        const bool eoln = c == '\r' || c == '\n';
        if (isspace(c) || eoln) {
            if (str.length() > 0) {
                iss.str(str);
                if (iss >> value) {
                    values.push_back(value);
                } else {
                    cerr << "Error: Non-integer value '" << str
                         << "' received at index " << index << "." << endl;
                    return 1;
                }
                iss.clear();
                ++index;
            }
            if (eoln) {
                break;
            }
            str.clear();
        } else {
            str += c;
        }
    }



    //if str is empty, error seq of ints not received
    if (str.size() == 0) {
        cerr << "Error: Sequence of integers not received." << endl;
        return 1;
    }

    // TODO: produce output
    long answer;
    if (argc==1) {
        answer = count_inversions_fast(&values[0], values.size());
    }
    else {
        answer = count_inversions_slow(&values[0], values.size());
    }

    //output final formatted answer
    cout << "Number of inversions: " << answer << endl;
    
    return 0;
}
