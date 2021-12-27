/*******************************************************************************
 * Name    : sieve.cpp
 * Author  : Isabella Stone
 * Version : 1.0
 * Date    : September 9, 2021
 * Description : Find primes using the sieve of Eratosthenes
 * Pledge : I pledge my honor that I have abided by the Stevens Honor System.
 ******************************************************************************/
#include <cmath>
#include <iomanip>
#include <iostream>
#include <sstream>

using namespace std;

class PrimesSieve {
public:
    PrimesSieve(int limit);

    ~PrimesSieve() {
        delete [] is_prime_;
    }

    int num_primes() const {
        return num_primes_;
    }

    void display_primes() const;

private:
    // Instance variables
    bool * const is_prime_;
    const int limit_;
    int num_primes_, max_prime_;

    // Method declarations
    int count_num_primes() const;
    void sieve();
    static int num_digits(int num);
};

//constructor
PrimesSieve::PrimesSieve(int limit) :
        is_prime_{new bool[limit + 1]}, limit_{limit} {
    sieve();
}


void PrimesSieve::display_primes() const {
    // TODO: write code to display the primes in the format specified in the
    // requirements document.
    cout << "Number of primes found: " << count_num_primes() << endl; 
    cout << "Primes up to " << limit_ << ":" << endl;

    const int max_prime_width = num_digits(max_prime_);
    const int primes_per_row = 80 / (max_prime_width + 1);


    //if only needs one row:
    if (count_num_primes() <= primes_per_row) {
        for (int i = 2; i <= limit_; i++) {
            if (i == max_prime_) {
                cout << i;
                break;
            }
            if (is_prime_[i]) {
                cout << i << ' ';
            }
        }
    }
    else {
        int row_count = 0;
        for (int i = 2; i <= limit_; i++) {
            //if printing first prime
            if (is_prime_[i] && row_count==0) {
                cout << setw(max_prime_width) << i;
                row_count = 1;
            }
            //else if just continuing row
            else if (is_prime_[i] && row_count < primes_per_row) {
                row_count++;
                //if need to end row
                if (row_count == primes_per_row) {
                    cout << ' ' << setw(max_prime_width) << i << endl;
                    row_count = 0;
                }
                else {
                    cout << ' ' << setw(max_prime_width) << i;
                }
            }
        }
    }   
}




int PrimesSieve::count_num_primes() const {
    // TODO: write code to count the number of primes found
    //loop through is_prime and count how many trues there are
    int count = 0;
    for (int i = 0; i <= limit_; i++) {
        if (is_prime_[i]) {
        //if it's true, means prime is found so increase count
            count++;
        }
    }
    return count;
} 

void PrimesSieve::sieve() {
    // TODO: write sieve algorithm
    //first set all to true
    for (int i = 2; i <= limit_; i++) {
        is_prime_[i] = true;
    }

    //then set non-primes to false
    for (int i = 2; i <= sqrt(limit_); i++) {
        if (is_prime_[i]) {
            for (int j = i*i; j <= limit_; j+=i) {
                is_prime_[j] = false;
            }
        }
    }

    //loop through backwards to find first false to set max_prime_ to
    for (int i = limit_; i >= 2; i--) {
        if (is_prime_[i]) {
            //if false set max_prime_ to i
            max_prime_ = i;
            break;
        }
    }
}

int PrimesSieve::num_digits(int num) {
    // TODO: write code to determine how many digits are in an integer
    // Hint: No strings are needed. Keep dividing by 10.
    int count = 0;
    while (num != 0) {
        num = num/10;
        count = count + 1;
    }
    return count;
}

int main() {
    cout << "**************************** " <<  "Sieve of Eratosthenes" <<
            " ****************************" << endl;
    cout << "Search for primes up to: ";
    string limit_str;
    cin >> limit_str;
    int limit;

    // Use stringstream for conversion. Don't forget to #include <sstream>
    istringstream iss(limit_str);

    // Check for error.
    if ( !(iss >> limit) ) {
        cerr << "Error: Input is not an integer." << endl;
        return 1;
    }
    if (limit < 2) {
        cerr << "Error: Input must be an integer >= 2." << endl;
        return 1;
    }

    // TODO: write code that uses your class to produce the desired output.
    //print the index of each in is_prime_ that holds a true

    PrimesSieve s1(limit);
    cout << endl;
    s1.display_primes();
    return 0;
}
