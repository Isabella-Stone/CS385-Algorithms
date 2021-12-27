/*******************************************************************************
 * Name          : shortestpaths.cpp
 * Author        : Isabella Stone and Megan Sanford
 * Pledge        : I pledge my honor that I have abided by the Stevens Honor System.
 * Date          : 12/5/21
 * Description   : Implements the shortestpath floyd algorithm.
 ******************************************************************************/
#include <iostream>
#include <fstream>
#include <sstream>
#include <algorithm>
#include <vector>
#include <limits>
#include <iomanip>
#include <string>

using namespace std;

int num;
long INF = std::numeric_limits<long>::max();
long **path;
long **intermediates;

void deletematrix(long** x){
   for(int i = 0; i < num; i++){
       delete[] x[i];
   }
   delete[] x;
}

int len(long num) {
   
   int counter = 0;
    while(num != 0){
        num = num / 10;
        counter += 1;
    }
    return counter;
}

void floyd(long** distance){
    
    //initializes path to be equal to distance matrix
    path = new long*[num];
    for(int i = 0; i < num; i++){
        path[i] = new long[num];
    }
    for(int i = 0; i < num; i++){
        for(int j = 0; j < num; j++){
            path[i][j] = distance[i][j];
        }
    }

    //initializes intermediates to be filled with inf
    intermediates = new long*[num];
    for(int i = 0; i < num; i++){
        intermediates[i] = new long[num];
        fill(intermediates[i], intermediates[i] + num, INF);
    }

    //this was described in the textbook
    for(int k = 0; k < num; k++){
        for(int i = 0; i < num; i++){
            for(int j = 0; j < num; j++){

                if(path[i][k] == INF || path[k][j] == INF){
                    continue;
                }
                
                if(path[i][k]+path[k][j] < path[i][j]){
                    path[i][j] = path[i][k]+path[k][j];
                    intermediates[i][j] = k;
                }
            }
        }
    }
}
string final_(int initial, int final, string ans) {
    //int initial is the ascii num of the starting letter
    //int final is the ascii val of what we want to get to
    //string ans is result

       if (intermediates[initial-65][final-65] == INF) {
            ans.push_back(char(final));
            return ans;
       }
       else{
           char middle = char(intermediates[initial-65][final-65] + 65);
            string one = final_(initial, middle, "");
            string two = final_(middle, final, "");

            ans += one + " -> " + two;

            return ans;
       }
}

void printer(long** distance){
    int initial_ascii = 65;

   for (int j = initial_ascii; j < num+65; j++) {

       for (int i = 65; i < num+65; i++) {
            if (i==initial_ascii) {
                cout << char(initial_ascii) << " -> " << char(i) << ", distance: 0, path: " << char(initial_ascii) << endl;      

            }
            else {
                if(path[initial_ascii-65][i-65] == INF){
                    cout << char(initial_ascii) << " -> " << char(i) << ", distance: infinity, path: none" << endl;   
                }
                else{
                    string str = "";
                    str.push_back(initial_ascii);
                    str += " -> ";
                    cout << char(initial_ascii) << " -> " << char(i) << ", distance: " << path[initial_ascii-65][i-65];
                    cout << ", path: " << final_(initial_ascii, i, str) <<endl;     
                }
            }
        }
        initial_ascii++;
   }
}


/**
* Displays the matrix on the screen formatted as a table.
*
*/
void display_table(long** const matrix, const string &label, const bool use_letters = false) {

    cout << label << endl;
    long max_val = 0;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            long cell = matrix[i][j];
            if (cell < INF && cell > max_val) {
                max_val = matrix[i][j];
            }
        }
    }
    int max_cell_width = use_letters ? len(max_val) :
    len(max(static_cast<long>(num), max_val));
    cout << " ";
    for (int j = 0; j < num; j++) {
        if (num==1 && matrix[0][0]==INF) {
            cout << setw(max_cell_width + 2) << static_cast<char>(j + 'A');
        }
        else {
            cout << setw(max_cell_width + 1) << static_cast<char>(j + 'A');
        }
    }
    cout << endl;
    for (int i = 0; i < num; i++) {
        cout << static_cast<char>(i + 'A');
        for (int j = 0; j < num; j++) {
            cout << " " << setw(max_cell_width);
            if (matrix[i][j] == INF) {
                cout << "-";
            } else if (use_letters) {
                cout << static_cast<char>(matrix[i][j] + 'A');
            } else {
                cout << matrix[i][j];
            }
        }    
        cout << endl;
    }
    cout << endl;
    
}

int main(int argc, const char *argv[]) {

    // Make sure the right number of command line arguments exist.
    if (argc != 2) {
        cerr << "Usage: " << argv[0] << " <filename>" << endl;
        return 1;
    }
    // Create an ifstream object.
    ifstream input_file(argv[1]);
    // If it does not exist, print an error message.
    if (!input_file) {
        cerr << "Error: Cannot open file '" << argv[1] << "'." << endl;
        return 1;
    }
    // Add read errors to the list of exceptions the ifstream will handle.
    input_file.exceptions(ifstream::badbit);
    string line;
    getline(input_file, line);
    istringstream iss(line.data());

    
    bool badvertex = false;
    bool badweight = false;
    string badvert;
    string word1, word2, word3, word4, max_word, startend, word1error, word2error, word3error;
    unsigned int line_number = 1;
    unsigned int error_line;

    if (!(iss>>num)) {
        //if its not an integer:
        cerr << "Error: Invalid number of vertices '" << line.data() << "'" << " on line 1." << endl;       
        return 1;
    }
    if (num==0) {
        //if its an integer but it is 0
        cerr << "Error: Invalid number of vertices '" << line.data() << "'" << " on line 1." << endl;
        return 1;
    }

    //initialized every value to inf
    long** distance = new long*[num];
    for(int i = 0; i < num; i++){
        distance[i] = new long[num];
        fill(distance[i], distance[i] + num, INF);
    }

    //this one puts 0s on the diagonal
    for(int i = 0; i < num; i++){
        distance[i][i] = 0;
    }

    try {
        
        // Use getline to read in a line.
        // See http://www.cplusplus.com/reference/string/string/getline/
        //cout << "************" << endl;
        while (getline(input_file, line)) {
            ++line_number;
            //i++;
            //use the geeks for geeks code and then cite the link to check the characters in each line
            
            if (line.length()==3) {
                cerr << "Error: Invalid edge data '" << line.data() << "'" << " on line 5." << endl;
                deletematrix(distance);
                return 1;
            }               
            
            //the 3 foreach loops below were modified from code on geeksforgeeks: https://www.geeksforgeeks.org/split-a-sentence-into-words-in-cpp/

            int index1 = 0;
            for(auto x: line){
                if(x == ' '){
                    break;
                }
                index1++;
            }
            word1 = line.substr(0, index1);
            index1++;

            int index2 = 0;
            for(auto x: line.substr(index1)){
                if(x == ' '){
                    break;
                }
                index2++;
            }
            word2 = line.substr(index1, index2);
            index2++;

            word3 = "";
            for(auto x: line.substr(index2+1)){
                //index3++;
               word3 += x;
            }
            //to take out space for single digit weights
            if (word3[0]==' ') {
                word3 = word3.substr(1);
            }
            
            word4 = max(word1, (max(word2, word3)));
            if (max(word4, max_word)==word4 && word4.size()==1 && (int(word4[0]) >= 65 && int(word4[0]) <= 90)) {
                max_word = word4;
            }

            if(int(word1[0]) > (num+65) || int(word1[0]) < 65){

                cerr << "Error: Starting vertex '" << word1 << "' on line " << line_number << " is not among valid values A-" << char(num+64) << "." << endl;
                deletematrix(distance);
                return 1;
            }
            else if(int(word2[0]) > (num+65) || int(word2[0]) < 65){

                cerr << "Error: Ending vertex '" << word2 << "' on line " << line_number << " is not among valid values A-" << char(num+64) << "." << endl;
                deletematrix(distance);
                return 1;
            }
            else if(int(word1[0]) < 65 || int(word1[0]) > 90 || word1.length() > 1){
                word1error = word1;
                badvertex = true;
                badvert = word1;
                error_line = line_number;
            }
            else if(word2.length() > 1 || int(word2[0]) < 65 || int(word2[0]) > 90){
                word2error = word2;
                badvertex = true;
                badvert = word2;
                error_line = line_number;
            }    
            
            
            istringstream iss2(word3);
            int number;
            if(!(iss2>>number) || number <= 0) {
                word3error = word3;
                badweight = true;
                badvert = word3;
                error_line = line_number;
                break;
            }

            //ADD IN THE DISTANCES INTO THE MATRIX   
            distance[int(word1[0])-65][int(word2[0])-65] = number; 
        }
        if (badvertex) {
                //needs to happen at last iteration**
                if (badvert==word1error) {
                    startend = "Starting";
                }
                if (badvert==word2error) {
                    startend = "Ending";
                }
                cerr << "Error: " << startend << " vertex '" << badvert << "' on line " << error_line << " is not among valid values A-" << max_word << "." << endl;
                deletematrix(distance);
                return 1;
        }
        if(badweight){
            cerr << "Error: Invalid edge weight '" << word3error << "' on line " << error_line << "." << endl;
            deletematrix(distance);
            return 1;
        }
        
        // Don't forget to close the file
        input_file.close();
    } catch (const ifstream::failure &f) {
        cerr << "Error: An I/O error occurred reading '" << argv[1] << "'.";
        return 1;
    }

    floyd(distance);

    display_table(distance, "Distance matrix:" , false);
    display_table(path, "Path lengths:" , false);
    display_table(intermediates, "Intermediate vertices:" , true);

    printer(distance);

    bool equal = true;
    for (int i = 0; i < num; i++) {
        for (int j = 0; j < num; j++) {
            if (distance[i][j] != path[i][j]) {
                equal = false;
            }        
        }
    }
    if (equal) {
        deletematrix(distance);
        deletematrix(path);
        deletematrix(intermediates);
    }
    else {
        deletematrix(distance);
        deletematrix(path);
        deletematrix(intermediates);
    }

    return 0;
}
