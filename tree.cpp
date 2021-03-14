#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Tree{
	string sequence;
	struct Node{
		string value;
		Node *parent;
		//we may need more children, perhaps a vector of em? three is good for tests
		Node *childa;
		Node *childb;
		Node *childc;
	}node;

	public:
		Tree(string seq)
		{
			sequence.assign(seq);
			cout << "in tree" << sequence << endl;
		}
};
