#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include "tree.h"
#include "tree.cpp"
using namespace std;

struct suffixTree{
    
};

void readInput(ifstream &file, string &sequence, string &name) {
    vector<string> lines;
    string templine;
    getline(file, name);
    sequence = "";
    getline(file, templine);
    while (isalpha(templine[0])) {
        lines.push_back(templine);
        getline(file, templine);
    }
    for(size_t i = 0; i< lines.size()-1; i++){
        templine = lines[i];
        sequence += templine;
    }
    sequence += lines[lines.size()-1];
}
int main(int argc, char *argv[]) {
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "not  open 1: alphabet" << endl;
        return 1;
    }
    ifstream input2(argv[2]);
    if (!input2.is_open()){
        cout << "not  open 2: alphabet " << endl;
        return 1;
    }
    string alphabet;
    getline(input2,alphabet);
    cout << alphabet<< endl;
    string nameOfInput;
    string sequence;
    readInput(input, sequence, nameOfInput);
  
    cout << "name " <<nameOfInput << endl;
    Tree tree(sequence);
    tree.print();

    return 0;
}
