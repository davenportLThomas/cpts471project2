#include<iostream>
#include<vector>
#include<string>
#include<utility>

using namespace std;

class Tree{
	struct Node{
		string value;
		int id;
		int string_depth;
		pair<int,int> start;//not sure what this is for yet
		Node *uPrime;//parent
		//we may need more children, perhaps a vector of em? three is good for a start
		vector<Node*> u;//children
		Node *v;//suffix link
	};

	string sequence; //whole sequence
	string currentSequence; //the sequence after we drop the first letter
	Node *root;
	Node *current; //where we are in the tree
	int nodeCount;

	void createHead()
	{
		root = new Node;
		root->v = nullptr;
		current = root;
		current->value = "ROOT";
		current->id = -1;//the head it -1
		current->string_depth = 0;
		nodeCount = 1;
		//lets build a tree
		buildNaiveTree();
	};

	void buildNaiveTree()
	{
		//findNode function here
		Node *thisNode = findNode(root);
		cout << "This Node: " << thisNode->value << endl;
		addChild();
	}

	Node *findNode(Node *tryThis)
	{
		//check the current string in the node for a match, this algo doesn't feel right
		for(uint32_t i = 0 ; i < currentSequence.size(); i++)
		{
			if(currentSequence[i] != tryThis->value[i])
				break;
			return(tryThis);
		}
		//actually traverse the tree is match is not found
		if(tryThis != nullptr)
		{
			for(uint32_t i = 0; i < tryThis->u.size(); i++)
			{
				findNode(tryThis->u[i]);
			}
		}
		return root;
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
		cout << "ROOT: " << root->value << endl;
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
