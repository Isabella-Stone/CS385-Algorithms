/*******************************************************************************
 * Name        : stairclimber.cpp
 * Author      : Isabella Stone
 * Date        : 9/25/21
 * Description : Lists the number of ways to climb n stairs.
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <iostream>
#include <vector>
#include <algorithm>
#include <sstream>
#include <iomanip>

using namespace std;


vector< vector<int> > get_ways(int num_stairs) {
    // TODO: Return a vector of vectors of ints representing
    // the different combinations of ways to climb num_stairs
    // stairs, moving up either 1, 2, or 3 stairs at a time

    //intialize ways & result vectors
    vector<vector<int>> ways = {};
    vector<vector<int>> result = {{}};
    
    //if there are 0 stairs return empty vector of vectors
    //base case
    if (num_stairs <= 0) {
        ways.push_back({});
    }
    //else find solutions
    for (int i = 1; i <= 3; i++) {
        if (num_stairs >= i) {
            result = get_ways(num_stairs - i);
            for (size_t j = 0; j < result.size(); j++) {
                //need to do i += result[j] and result[j] += i
                result[j].insert(result[j].begin(), i); //result[j] = [i] + result[j]
            }
            //add whats in result to ways (final vector to return)
            for (size_t i =0; i < result.size(); i++) {
                ways.push_back(result[i]);
            }
        }
    }
    return ways;
}


void display_ways(const vector< vector<int> > &ways) {
    // TODO: Display the ways to climb stairs by iterating over
    // the vector of vectors and printing each combination.
    //ways of i of 0 is max num stairs
    int num_ways = ways.size();
    int num_stairs = ways[0].size();

    if (num_ways == 1) {
        cout << "1 way to climb 1 stair." << endl;
    }
    else {
        cout << num_ways << " ways to climb " << num_stairs << " stairs." << endl;
    }

    for (size_t i = 0; i < ways.size(); i++) {
        int num = i+1;
        cout << setw(to_string(num_ways).length()) << num << ". [";
        //now loop through each way
        for (size_t j = 0; j < ways[i].size(); j++) {
            if (j==(ways[i].size()-1)) {
                cout << ways[i][j];
            }
            else {
                cout << ways[i][j] << ", "; 
            }
        }
        cout << "]" << endl;
    }
}

int main(int argc, char * const argv[]) {
    //check arg count to throw errors
    if (argc==1 || argc>2) {
        cerr << "Usage: " << argv[0] << " <number of stairs>" << endl;
        return 1;
    }
   
    int numStairs;
    istringstream iss;
    iss.str(argv[1]);

    //Check for valid input:
    //if its not an int
    if (!(iss >> numStairs) || numStairs <= 0) {
        cerr << "Error: Number of stairs must be a positive integer." << endl;
        return 1;
    }
    //free iss to avoid memory leaks
    iss.clear();
    display_ways(get_ways(numStairs));
    return 0;
}
