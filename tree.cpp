#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Tree{
	struct Node{
		string value;
		Node *uPrime;//parent
		//we may need more children, perhaps a vector of em? three is good for a start
		vector<Node*> u;//handles up to 3 children
		Node *v;//suffix link
		Node *vPrime;//suffix link of uPrime, if it exists
		int leafNumber;
	};

	string sequence; //whole sequence
	string currentSequence; //the sequence after we drop the first letter
	Node *head;
	Node *current; //where we are in the tree
	int nodeCount;

	void createHead()
	{
		head = new Node;
		head->vPrime = nullptr; //this will not change
		head->v = nullptr;
		current = head;
		current->value = "HEAD";
		current->leafNumber = -1;//the head it -1
		nodeCount = 1;
		//lets build a tree
		buildTree();
	};

	void buildTree()
	{
		//findNode function here
		addChild();
	}

	void findNode()
	{
		//use this function to find the proper node, cases can go here
		//set currentNode appropriately
	}

	void addChild()
	{
		nodeCount++;
		Node *child = new Node;
		current->u.push_back(child);
		int vectorLast = current->u.size() -1;
		current = current->u[vectorLast];
		current->value.assign(currentSequence);
	// 	cout << head->u[0]->value << endl;
	}

	void printTree()//this is currently VERY VERY rudimentary
	{
		cout << "Head: " << head->value << endl;
		cout << current->value << endl;

	}

	public:
		Tree(string seq)
		{
			sequence.assign(seq);
			currentSequence.assign(seq);
			createHead();
			printTree();
		}
};
