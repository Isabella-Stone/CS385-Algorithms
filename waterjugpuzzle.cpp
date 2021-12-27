/*******************************************************************************
 * Name        : waterjugpuzzle.cpp
 * Author      : Megan Sanford and Isabella Stone
 * Date        : October 16, 2021
 * Description : Using breadth-first search to solve the water jug problem. 
 * Pledge      : I pledge my honor that I have abided by the Stevens Honor Sytsem. 
 ******************************************************************************/

#include <iostream>
#include <sstream>
#include <queue>
#include <vector>
#include <string>
#include <algorithm>

using namespace std;

// Struct to represent state of water in the jugs.
struct State {
    int a, b, c;
    string directions;
    State *parent;
    
    State(int _a, int _b, int _c, string _directions) : 
        a{_a}, b{_b}, c{_c}, directions{_directions}, parent{nullptr} { }
    
    // String representation of state in tuple form.
    string to_string() {
        ostringstream oss;
        oss << directions << " " << "(" << a << ", " << b << ", " << c << ")";
        return oss.str();
    }
};

vector<State> bfs(int acap, int bcap, int ccap, State goal) {
   
    State* **array = new State**[acap + 1]; 
    for(int i = 0; i < acap + 1; i++) {
        array[i] = new State*[bcap + 1];
        // Initialize the new row.
        fill(array[i], array[i] + bcap+ 1, nullptr);
    }

    queue<State*> tree;
    vector<State> parentvec;
    bool found = false;

    State *pgoal = new State(goal.a, goal.b, goal.c, "");
    State *child;
    
    //put initial state in tree and array
    State *initial = new State(0, 0, ccap, "Initial state.");
    initial->parent = nullptr;
    tree.push(initial);
    array[0][0] = initial;

    State *current;
    
    //check if initial state IS the goal
    if ((initial->a == pgoal->a) && (initial->b == pgoal->b)) {
        parentvec.push_back(*initial);
        delete pgoal;

        for(int i = 0; i < acap+1; i++) {
            for(int j = 0; j < bcap+1; j++){
                delete array[i][j];
            }
            delete [] array[i];
        }    
        delete [] array;

        return parentvec;
    }
    
    //else find steps
    while (!(tree.empty())){
        current = tree.front(); //this will always stay the same 
        tree.pop();
        if(current == pgoal){  
            break;
        }
        //try the 6 ways to pour:
        //pour from c to a
        if(current->c!=0 && current->a != acap){
            int newa;
            int newc; 
            int numPoured;
            //if a is empty 
            if(current->a == 0 || (current->a + current->c <= acap)){
                //if what's in c is more than what a can hold
                if(current->c > acap){
                    if(current->a == 0){
                        newa = acap;    //fill it all the way
                        newc = current->c - newa;
                    }
                    //if c can fit into b
                    else{
                        newa = current->a + current->c;     //emptying c if you can
                        newc = 0;
                    }
                }
                else{
                    //this is when you empty c into b
                    newa = current->a + current->c;  
                    newc = 0;
                }
                numPoured = current->c - newc;
            }
            //a has some in it
            else{   //else, pour what you can
                newc = current->c - (acap - current->a);
                newa = current->a + (current->c - newc);
                numPoured = current->c - newc;
            }
            
            string str;
            if (numPoured == 1) {
                str = "Pour " + to_string(numPoured) + " gallon from C to A."; 
            } 
            else {
                str = "Pour " + to_string(numPoured) + " gallons from C to A."; 
            }
            //before you push it, make sure it hasnt been seen
            if(array[newa][current->b] == nullptr){
                child = new State(newa, current->b, newc, str);
                tree.push(child);
                child->parent = current; //points to address of current which is its parent
                array[newa][current->b] = child;
                if(child->a == pgoal->a && child->b == pgoal->b){
                    pgoal->directions = str;
                    found = true;
                    break;
                }
            }
        }
        if(current->b!=0 && current->a != acap){
            int newa;
            int newb; 
            int numPoured;
            //if a is empty 
            if(current->a == 0 || (current->a + current->b <= acap)){
                //if what's in c is more than what a can hold
                if(current->b > acap){
                    if(current->a == 0){
                        newa = acap;    //fill it all the way
                        newb = current->b - newa;
                    }
                    //if c can fit into b
                    else{
                        newa = current->a + current->b;     //emptying b if you can
                        newb = 0;
                    }
                }
                else{
                    //this is when you empty c into b
                    newa = current->a + current->b;  
                    newb = 0;
                }
                numPoured = current->b - newb;
            }
            //a has some in it
            else{   //else, pour what you can
                newb = current->b - (acap - current->a);
                newa = current->a + (current->b - newb);
                numPoured = current->b - newb;
            }
            
            string str;
            if (numPoured == 1) {
                str = "Pour " + to_string(numPoured) + " gallon from B to A."; 
            } 
            else {
                str = "Pour " + to_string(numPoured) + " gallons from B to A."; 
            }
            //before you push it, make sure it hasnt been seen
            if(array[newa][newb] == nullptr){
                child = new State(newa, newb, current->c, str);
                tree.push(child);
                child->parent = current; //points to address of current which is its parent
                array[newa][newb] = child;
                if(child->a == pgoal->a && child->b == pgoal->b){
                    pgoal->directions = str;
                    found = true;
                    break;
                }
            }
        }
        if(current->c!=0 && current->b != bcap){
            int newb;
            int newc; 
            int numPoured;
            //if b is empty 
            if(current->b == 0 || (current->b + current->c <= bcap)){
                //if what's in c is more than what b can hold
                if(current->c > bcap){
                    if(current->b == 0){
                        newb = bcap;    //fill it all the way
                        newc = current->c - newb;
                    }
                    //if c can fit into b
                    else{
                        newb = current->b + current->c;     //emptying c if you can
                        newc = 0;
                    }
                }
                else{
                    //this is when you empty c into b
                    newb = current->b + current->c; 
                    newc = 0;
                }
                numPoured = current->c - newc;
            }
            //a has some in it
            else{   //else, pour what you can
                newc = current->c - (bcap - current->b);
                newb = current->b + (current->c - newc);
                numPoured = current->c - newc;
            }
            
            string str;
            if (numPoured == 1) {
                str = "Pour " + to_string(numPoured) + " gallon from C to B."; 
            } 
            else {
                str = "Pour " + to_string(numPoured) + " gallons from C to B."; 
            } 
            //before you push it, make sure it hasnt been seen
            if(array[current->a][newb] == nullptr){
                child = new State(current->a, newb, newc, str);
                tree.push(child);
                child->parent = current; //points to address of current which is its parent
                array[current->a][newb] = child;
                if(child->a == pgoal->a && child->b == pgoal->b){
                    pgoal->directions = str;
                    found = true;
                    break;
                }
            }
        }
        if(current->a!=0 && current->b != bcap){
            int newb;
            int newa; 
            int numPoured;
            //if b is empty 
            if(current->b == 0 || (current->b + current->a <= bcap)){
                //if what's in c is more than what b can hold
                if(current->a > bcap){
                    if(current->b == 0){
                        newb = bcap;    //fill it all the way
                        newa = current->a - newb;
                    }
                    //if c can fit into b
                    else{
                        newb = current->b + current->a;     //emptying a if you can
                        newa = 0;
                    }
                }
                else{
                    //this is when you empty c into b
                    newb = current->b + current->a; 
                    newa = 0;
                }
                numPoured = current->a - newa;
            }
            //a has some in it
            else{   //else, pour what you can
                newa = current->a - (bcap - current->b);
                newb = current->b + (current->a - newa);
                numPoured = current->a - newa;
            }
            
            string str;
            if (numPoured == 1) {
                str = "Pour " + to_string(numPoured) + " gallon from A to B."; 
            } 
            else {
                str = "Pour " + to_string(numPoured) + " gallons from A to B."; 
            } 
            //before you push it, make sure it hasnt been seen
            if(array[newa][newb] == nullptr){
                child = new State(newa, newb, current->c, str);
                tree.push(child);
                child->parent = current; //points to address of current which is its parent???????????????
                array[newa][newb] = child;
                if(child->a == pgoal->a && child->b == pgoal->b){
                    pgoal->directions = str;
                    found = true;
                    break;
                }
            }
        }
        if(current->b!=0 && current->c != ccap){
            int newc;
            int newb; 
            int numPoured;
            //if c is empty 
            //if a is empty 
            if(current->c == 0 || (current->c + current->b <= ccap)){
                //if what's in c is more than what a can hold
                if(current->b > ccap){
                    if(current->c == 0){
                        newc = ccap;    //fill it all the way
                        newb = current->b - newc;
                    }
                    //if c can fit into b
                    else{
                        newc = current->c + current->b;     //emptying b if you can
                        newb = 0;
                    }
                }
                else{
                    //this is when you empty c into b
                    newc = current->c + current->b; //***********************
                    newb = 0;
                }
                numPoured = current->b - newb;
            }
            //a has some in it
            else{   //else, pour what you can
                newb = current->b - (ccap - current->c);
                newc = current->c + (current->b - newb);
                numPoured = current->b - newb;
            }
            
            string str;
            if (numPoured == 1) {
                str = "Pour " + to_string(numPoured) + " gallon from B to C."; 
            } 
            else {
                str = "Pour " + to_string(numPoured) + " gallons from B to C."; 
            }
            //before you push it, make sure it hasnt been seen
            if(array[current->a][newb] == nullptr){
                child = new State(current->a, newb, newc, str);
                tree.push(child);
                child->parent = current; //points to address of current which is its parent
                array[current->a][newb] = child;
                if(child->a == pgoal->a && child->b == pgoal->b){
                    pgoal->directions = str;
                    found = true;
                    break;
                }
            }
        }
        if(current->a!=0 && current->c != ccap){
            int newc;
            int newa; 
            int numPoured;
            //if c is empty or all of a can fit into c
            if(current->c == 0 || (current->c + current->a <= ccap)){
                //if what's in a is more than what c can hold
                if(current->a > ccap){
                    if(current->c == 0){
                        newc = ccap;    //fill c to its capacity
                        newa = current->a - newc;
                    }
                    //if a can fit into c
                    else{
                        newc = current->c + current->a;     //emptying a if you can
                        newa = 0;
                    }
                }
                else{
                    //this is when you empty a into c
                    //newc = current->a;***********************
                    newc = current->c + current->a;
                    newa = 0;
                }
                numPoured = current->a - newa;
            }
            //c has some in it
            else{   //else, pour what you can
                newa = current->a - (ccap - current->c);
                newc = current->c + (current->a - newa);
                numPoured = current->a - newa;
            }
            
            string str;
            if (numPoured == 1) {
                str = "Pour " + to_string(numPoured) + " gallon from A to C."; 
            } 
            else {
                str = "Pour " + to_string(numPoured) + " gallons from A to C."; 
            }
            //before you push it, make sure it hasnt been seen
            if(array[newa][current->b] == nullptr){
                child = new State(newa, current->b, newc, str);
                tree.push(child);
                child->parent = current; //points to address of current which is its parent
                array[newa][current->b] = child;
                if(child->a == pgoal->a && child->b == pgoal->b){
                    pgoal->directions = str;
                    found = true;
                    break;
                }
            }
        }
    }

    //fill parentvec with parents
    State* curr = array[pgoal->a][pgoal->b];
	
   if(found){
       curr = curr->parent;
       // State* follower = curr;
       parentvec.push_back(*pgoal);
       while (curr != nullptr) {
            parentvec.push_back(*curr);
            //follower = curr;
            curr = curr->parent;
            //delete follower;
        }
   }

    //loop through to delete rest of tree queue
    if(tree.size()!=0) {
        for (size_t i = 0; i < tree.size(); i++) {
            tree.pop();
        }
    }
    
   //delete stuff:
   if (initial->a == current->a && initial->b == current->b) {
        delete pgoal;
   }
   else {
        delete pgoal;
   }
    

    //delete array
    for(int i = 0; i < acap+1; i++) {
        for(int j = 0; j < bcap+1; j++){
            delete array[i][j];
        }
        delete [] array[i];
    }    
    delete [] array;

    //return vector
    return parentvec;
}


int main(int argc, char* argv[]) {
    int capa, capb, capc, goala, goalb, goalc;
    istringstream iss;

    if(argc != 7){
        cerr << "Usage: ./waterjugpuzzle <cap A> <cap B> <cap C> <goal A> <goal B> <goal C>" << endl;
        return 1;
    }
    iss.str(argv[1]);
        if(!(iss >> capa) || capa <= 0){
            cerr << "Error: Invalid capacity '" << argv[1] <<"' for jug A." << endl;
            return 1;
        }
    
    iss.clear();
    
    iss.str(argv[2]);
        if(!(iss >> capb) || capb <= 0){
            cerr << "Error: Invalid capacity '" << argv[2] <<"' for jug B." << endl;
            return 1;
        }
    
    iss.clear();
    iss.str(argv[3]);
        if(!(iss >> capc) || capc <=0){
            cerr << "Error: Invalid capacity '" << argv[3] << "' for jug C." << endl;
            return 1;
        }
    
    iss.clear();
    iss.str(argv[4]);
        if(!(iss >> goala) || goala < 0){
            cerr << "Error: Invalid goal '" << argv[4] << "' for jug A." << endl;
            return 1;
        }

    iss.clear();
    iss.str(argv[5]);
        if(! (iss >> goalb) || goalb < 0){
            cerr << "Error: Invalid goal '" << argv[5] << "' for jug B." << endl;
            return 1;
        }
    iss.clear();
    iss.str(argv[6]);
        if(! (iss >> goalc) || goalc < 0){
            cerr << "Error: Invalid goal '" << argv[6] << "' for jug C." << endl;
            return 1;
        }
    iss.clear();

    if(goala > capa){
        cerr << "Error: Goal cannot exceed capacity of jug A." << endl;
        return 1;
    }
    if(goalb > capb){
        cerr << "Error: Goal cannot exceed capacity of jug B." << endl;
        return 1;
    }
    if(goalc > capc){
        cerr << "Error: Goal cannot exceed capacity of jug C." << endl;
        return 1;
    }
    if((goala + goalb + goalc) != capc){
        cerr << "Error: Total gallons in goal state must be equal to the capacity of jug C." << endl;
        return 1;
    }

    State goal(goala, goalb, goalc, " ");
    vector<State> result = bfs(capa, capb, capc, goal);
    //if the only thing in result is the no_sol state:
    if (result.size() == 0) {
        cout << "No solution." << endl;
        return 0;
    }

    //else, loop through to properly print 
    reverse(result.begin(), result.end()); //reverse vector to get it in the right order
    for (size_t i = 0; i<result.size(); i++) {
        cout << result.at(i).to_string() << endl;
    }

    return 0;
}
