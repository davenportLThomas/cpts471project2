#include "tree.h"
#include <iostream>
#include <fstream>
#include "tree.cpp"
using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

int main(int argc, char *const argv[]) {
    ifstream fString(argv[1]);
    if (!fString.is_open()) {
        cerr << "Unable to open string input!" << endl;
        exit(1);
    }

    ifstream fAlphabet(argv[2]);
    if (!fAlphabet.is_open()) {
        cerr << "Unable to open alphabet input!" << endl;
        exit(1);
    }

    string iString;
    string iAlphabet;
    getline(fString, iString);
    getline(fAlphabet, iAlphabet);

    SuffixTree tree(iString, iAlphabet);

    cout << endl << "All nodes:" << endl;
    for (size_t i = 0; i < Node::allNodes.size(); ++i) {
        cout << i << ": " << Node::allNodes[i]->ToString() << endl;
    }

    cout << endl << "All leaves:" << endl;
    for (size_t i = 0; i < Node::allLeaves.size(); ++i) {
        cout << i << ": " << Node::allLeaves[i]->ToString() << endl;
    }

    cout << endl << "Tree:" << endl;
    tree.Display();
    return 0;
}