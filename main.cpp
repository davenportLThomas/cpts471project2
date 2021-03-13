#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;

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
    for(int i = 0; i< lines.size()-1; i++){
        templine = lines[i];
        sequence += templine;
    }
    sequence += lines[lines.size()-1];
}
int main(int argc, char *argv[]) {
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "not  open" << endl;
        return 1;
    }
    string nameOfInput;
    string sequence;
    readInput(input, sequence, nameOfInput);
    cout << sequence << endl << nameOfInput << endl;
    return 0;
}
