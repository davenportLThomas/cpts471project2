#include "tree.h"
#include <iostream>
#include <fstream>
#include "tree.cpp"
#include <chrono>

using std::cerr;
using std::cout;
using std::endl;
using std::ifstream;
using std::string;

void readInput(string const &path, string &sequence, string &name) {
    ifstream file(path);
    if (!file.is_open()) {
        cerr << "Unable to open path" << path << "!" << endl;
        exit(1);
    }
    vector<string> lines;
    string templine;
    getline(file, name);
    sequence = "";
    getline(file, templine);
    while (isalpha(templine[0])) {
        lines.push_back(templine);
        getline(file, templine);
    }
    for (int i = 0; i < lines.size() - 1; i++) {
        templine = lines[i];
        sequence += templine;
    }
    sequence += lines[lines.size() - 1];
}

int main(int argc, char *const argv[]) {
    // Start measuring time
    auto begin = std::chrono::high_resolution_clock::now();

    string alph_Sequence, alph_name;
    readInput(argv[1], alph_Sequence, alph_name);
    string seq_sequence, seq_name;
    vector<string> seq_sequences, seq_names;
    string all_sequence;
    // put all sequence into one vector and as a big string of sequence
    for (int a = 2; a < argc; ++a) {
        readInput(argv[a], seq_sequence, seq_name);
        seq_sequences.push_back(seq_sequence);
        seq_names.push_back(seq_name);
        all_sequence.append(seq_sequence + "$");
    }


    SuffixTree tree(all_sequence, alph_Sequence);
    //part2 take the tree as arg
    tree.p2_process_children();

    // Stop measuring time and calculate the elapsed time

    auto end = std::chrono::high_resolution_clock::now();
    auto elapsed = std::chrono::duration_cast<std::chrono::nanoseconds>(end - begin);
    printf("Time measured: %.3f seconds.\n", elapsed.count() * 1e-9);
    return 0;
}