#include <iostream>
#include <fstream>
#include <string>
#include <vector>
using namespace std;
//#define SEQUENCE_LENGTH 4

struct DP_cell {
    int Sscore;       // field for Substitution (S) score
    int Dscore;      // field for Deletion (D) score
    int Iscore;        // field for Insertion (I) score
    //int Tscore;  // max of the s, d, i
};
struct path_T{
    char a;
    char b; // char in the sequence
};
//find the max in the matrix
enum score_type{sscore, dscore, iscore};
struct max_t{
    score_type score; // which s d i is max
    int i;
    int j; // where the score is tracking the position
    int max_val; // actual max value
 };
//find the max value
// return the max score and position, and the score type(s,d,i)
max_t find_max(vector<vector<DP_cell>> &matrix){
    max_t max = {sscore, 0, 0 , matrix[0][0].Sscore}; // initial the max as max_t
    //go over matrix to check
    for(int i = 0; i < matrix.size(); i++){
        for (int j =0 ; j < matrix[i].size();j++ ){
            if(matrix[i][j].Sscore > max.max_val){
                max.score = sscore;
                max.i = i;
                max.j = j;
                max.max_val = matrix[i][j].Sscore;
            }
            if(matrix[i][j].Dscore > max.max_val){
                max.score = dscore;
                max.i = i;
                max.j = j;
                max.max_val = matrix[i][j].Dscore;
            }
            if(matrix[i][j].Iscore > max.max_val){
                max.score = iscore ;
                max.i = i;
                max.j = j;
                max.max_val = matrix[i][j].Iscore;
            }
        }

    }
    return max;
}
//find the path for local
vector<path_T> find_path_local(vector<vector<DP_cell>> &matrix, string &x, string &y, max_t &max){
    vector<path_T> path;
    path_T pair;
    int i = max.i ;
    int j = max.j ;
    // start from the max value i, j then stop at 0
    while (i > 0 && j >0) {
        pair = {x[i - 1], y[j - 1]};
        i--;
        j--;
        path.push_back(pair);
    }
    return path;
}
//find path for global
vector<path_T> find_path(vector<vector<DP_cell>> &matrix, string &x, string &y){
    int m = matrix.size();
    int n = matrix[0].size();
    vector<path_T> path;
    path_T pair;
    int i = m -1 ;
    int j = n -1 ;
    while (i > 0 && j >0){
        //cout << i<< " ," << j << endl;
        int i_val = matrix[i][j-1].Iscore;
        int s_val = matrix[i-1][j-1].Sscore;
        int d_val = matrix[i-1][j].Dscore;

        int max_val = max(i_val, max(s_val,d_val));

        if(s_val == max_val){
            pair = {x[i-1], y[j-1]};
            i--;
            j--;
        }
        else if(i_val == max_val){
            pair = {'-', y[j-1]};
            j--;
        }
        else{
            pair ={x[i-1], '-'};
            i--;
        }
        path.push_back(pair);
    }
    return path;
}

void print_path(vector<path_T> path){
    int start;
    int end;
    int matches = 0 ;
    int mismatches = 0 ;
    int gaps = 0 ;
    int openinggaps = 0;

    int gap_counter = 0;

    start = path.size()-1;
    end = start - 59;
    if (end < 0){
        end = 0;
    }
    while(start >= 0){
        for(int i = start; i >= end ; i--){
            if(path[i].a != ' '){
                cout << path[i].a;
            }else{
                cout << "-";
                gaps++;
            }
        }
        cout<< endl;
        for (int i = start; i >= end; i--){
            if(path[i].a == path[i].b && path[i].a != ' ' && path[i].b != ' '){
                cout << "|" ;
                matches ++ ;
            }else{
                cout << " " ;
                mismatches ++;
            }
        }
        cout << endl;
        for(int i = start; i >=end ; i--){
            if(path[i].b != '-'){
                cout << path[i].b ;
            }else{
                cout << '-' ;
                gaps++;
            }
        }


        cout<< endl;
        start = start - 60;
        end = start - 59;
        if (end < 0){
            end = 0;
        }
    }
    cout << "The number of " << "matches: "<<matches << " mismatches: " << mismatches << " gap : " << gaps << " the opning gpas is : "<< openinggaps<<   endl;
}
// each tline except for the last can have most 60 char, any space inside the 60 consider the gap
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

int decision(char a, char b, int match, int mismatch){
    if (a == b){
        return match;
    }
    else return mismatch;
}
void print_matrix(vector<vector<DP_cell>> &matrix, int m, int n){
    for(int i = 0; i<= m; i++){
        for(int j = 0; j <= n; j++){
            //cout<< "i: " << matrix[i][j].Iscore ;
            //cout<<" d:" << matrix[i][j].Dscore ;
            //cout<< " S:"<< matrix[i][j].Sscore<< " ";
        }
        //cout << endl;
    }
}
//edit distance (two strings x, y) return a matrix A[M+1,N+1] where M = len(x), N=len(y) m is row
//h is the opening, g is the continue
vector<vector<DP_cell>> global_NW(string &x, string &y, int g, int match, int mismatch,int h){
    int m = x.length();
    int n = y.length();
    vector<vector<DP_cell>> a;
    // resize vector
    a.resize(m+1);
    //resize each row
    for(int i = 0; i< a.size(); i++){
        a[i].resize(n+1);
    }
    // initial matrix[0][0]
    a[0][0].Sscore = 0;
    a[0][0].Iscore = 0;
    a[0][0].Dscore = 0;
    //init first row and col
    for(int i=1; i<= m; i++){
        a[i][0].Sscore = -100000;
        a[i][0].Dscore = h + i * g;
        a[i][0].Iscore = -100000;
        //cout << a[i][0].Sscore << " ";
        //cout << a[i][0].Dscore << " ";
        //cout << a[i][0].Iscore << " ";
    }
    cout << endl;
    //row
    for (int j = 1; j<= n; j++){
        a[0][j].Sscore = -100000;
        a[0][j].Dscore = -100000;
        a[0][j].Iscore = h+j *g;
//        cout << a[0][j].Sscore << " ";
//        cout << a[0][j].Dscore << " ";
//        cout << a[0][j].Iscore << " ";
    }
    cout << endl;
    //main matrix

    for(int i = 1; i<=m; i++){
        for(int j =1; j<= n; j++) {

            a[i][j].Sscore = max(a[i-1][j-1].Sscore, max(a[i-1][j-1].Dscore,a[i-1][j-1].Iscore))
                    + decision(x[i-1],y[j-1], match, mismatch);
            a[i][j].Dscore = max(a[i-1][j].Dscore +g , max(a[i-1][j].Sscore+h+g,a[i-1][j].Iscore +h+ g));
            a[i][j].Iscore = max(a[i][j-1].Iscore +g , max(a[i][j-1].Sscore+h+g,a[i][j-1].Dscore +h+ g));
        }
    }
    print_matrix(a,m,n);
    return a;

}

vector<vector<DP_cell>> local_SM(string &x, string &y, int match, int mismatch, int g, int h){
    int m = x.length();
    int n = y.length();
    vector<vector<DP_cell>> a;
    // resize vector
    a.resize(m+1);
    //resize each row
    for(int i = 0; i< a.size(); i++){
        a[i].resize(n+1);
    }
    // initial matrix[0][0]
    a[0][0].Sscore = 0;
    a[0][0].Iscore = 0;
    a[0][0].Dscore = 0;
    //init first row and col
    for(int i=1; i<= m; i++){
        a[i][0].Sscore = 0;
        a[i][0].Dscore = 0;
        a[i][0].Iscore = -100000;
//       // cout << a[i][0].Sscore << " ";
//        cout << a[i][0].Dscore << " ";
//        cout << a[i][0].Iscore << " ";
    }
    cout << endl;
    //row
    for (int j = 1; j<= n; j++){
        a[0][j].Sscore = 0;
        a[0][j].Dscore = -100000;
        a[0][j].Iscore = 0;
//        cout << a[0][j].Sscore << " ";
//        cout << a[0][j].Dscore << " ";
//        cout << a[0][j].Iscore << " ";
    }
    cout << endl;
    //main matrix

    for(int i = 1; i<=m; i++){
        for(int j =1; j<= n; j++) {

            a[i][j].Sscore = max(a[i-1][j-1].Sscore, max(a[i-1][j-1].Dscore,a[i-1][j-1].Iscore))
                             + decision(x[i-1],y[j-1], match, mismatch);
            a[i][j].Dscore = max(a[i-1][j].Dscore +g , max(a[i-1][j].Sscore+h+g,a[i-1][j].Iscore +h+ g));
            a[i][j].Iscore = max(a[i][j-1].Iscore +g , max(a[i][j-1].Sscore+h+g,a[i][j-1].Dscore +h+ g));
            a[i][j].Sscore = max(0,a[i][j].Sscore);
            a[i][j].Dscore = max(0,a[i][j].Dscore);
            a[i][j].Iscore = max(0,a[i][j].Iscore);
        }
    }
    return a;
}

int main(int argc, char *argv[]) {

    //cout << " hello" << endl;
    // input file in the argument
    ifstream input(argv[1]);
    if (!input.is_open()) {
        cout << "not  open" << endl;
        return 1;
    }
// the name of the sequence 1
    string name_input_1;
    string name_input_2;
// actual sequence 1
    string sequence1;
    string sequence2;
// read what is the actual input
    readInput(input, sequence1, name_input_1);
    readInput(input, sequence2, name_input_2);
    cout << name_input_1 << endl << sequence1 << endl;
    cout << name_input_2 << endl << sequence2 << endl;

    int choice = atoi(argv[2]);
    ifstream parameter(argv[3]);
// get parameters from the parameter file and print out
    int match;
    int mismatch;
    int g;
    int h;

    string label;
    parameter >> label >> match;
    parameter >> label >> mismatch;
    parameter >> label >> h;
    parameter >> label >> g;

    cout << " Match is " << match << " Mismatch is " << mismatch << " The g is " << g << " The h is " << h << endl;

    //start global alignment
    vector<vector<DP_cell>> matrix = global_NW(sequence1, sequence2, g, match, mismatch,h);
    //vector<vector<DP_cell>> matrix_sm = local_SM(sequence1, sequence2,g,match, mismatch,);
    int m = sequence1.length();
    int n = sequence2.length();

    // the struct need to select the value in it
    //cout << "the matrix final value " << matrix[m][n].Tscore << endl;
    vector<path_T> path = find_path(matrix,sequence1, sequence2);
    print_path(path);
    int optimal = max(matrix[m][n].Sscore, max(matrix[m][n].Iscore,matrix[m][n].Dscore));
    cout << "the optimal score is " << optimal << endl;

    //start local alignment
    vector<vector<DP_cell>> local_matrix = local_SM(sequence1,sequence2,match,mismatch,g,h);
    //int m_local = sequence1.length();
    //int n_local = sequence2.length();

    //need the max
    max_t max = find_max(local_matrix);
    vector<path_T> path_local = find_path_local(local_matrix,sequence1,sequence2,max);
    print_path(path_local);
    cout<< "the optimal local is " <<  max.max_val << endl;

    return 0;
}


