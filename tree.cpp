#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Tree{
	string sequence;
	long unsigned int seqPosition = 0;
	struct Node{
		Node *parent; //uPrime
		vector<Node*> children;
		string object;
		//int i; //starting member of sequence
		//int j; //ending member of sequence
		int node_id;
		int leaf_id;
	};
	Node *root;
	Node *current;
	int nodeCount = 0;


	void createRoot()
	{
		root = new Node;
		current = root;
		current->parent = nullptr;
		current->object = "--";
		current->node_id = nodeCount;
		nodeCount++;
	}

	Node *findNode(Node *tryThis)
	{
		for(uint32_t i = 0; i < tryThis->children.size(); i++)
		{
			if(tryThis->children[i]->object[0] == sequence[0])
			{
				return tryThis->children[i];
			}
			else//look in children's children
			{
				findNode(tryThis->children[i]);
			}

		}	
		return root;
	}

	int matchLength(string object)
	{
		int n = 0;//this will determine string length
		for(uint32_t i = 0; i < sequence.length(); i++)//the sequencce length should be shorter
		{
			cout << object[i] << " < "  << sequence[i] << endl;
			if(object[i] != sequence[i])
				break;
			n++;
		}
		return n;
	}

	void createChild()
	{
		cout << endl;
		cout << "---------------------------" << endl;	
		current = findNode(root);
		int n = matchLength(current->object);
		cout << "We are using this node " << current->node_id << endl;
		cout << "Sequence: " << sequence << endl;
		cout << "This object: " << current->object << endl;
		current->children.push_back(new Node);//create a new child
		Node *temp = current;
		current = current->children[current->children.size() - 1];
		current->parent = temp;

		current->node_id = nodeCount;
		nodeCount++;

		string forCurrent = sequence;
		cout << "forCurrent: " << forCurrent << endl;	
		cout << "n: " << n << endl;
		string forParent = forCurrent.substr(0, n);
		//forCurrent.erase(0, n);

		cout << "current: " << forCurrent << " forParent: " << forParent <<endl;

		current->object = forCurrent;
		current->parent->object = forParent;

		if( n > 0)
		{
		current = current->parent;
		current->children.push_back(new Node);
		temp = current;
		current = current->children[current->children.size() - 1];
		current->parent = temp;
		current->object = "$";
		current->node_id = nodeCount;
		nodeCount++;
		}
	

		sequence.erase(0,1);
	}

	void buildTree()
	{
		cout << " Node count " << nodeCount << endl;
		//this is how to end
		if(seqPosition == sequence.length())
			return;
		if(nodeCount == 0)
			createRoot();
		else
			createChild();

	}


	public:
	Tree(string seq)
	{
		this->sequence = seq;
		while(sequence.length() > 0)
			buildTree();
		print(root);
	}

	void print(Node *toPrint)
	{
		for(uint32_t i = 0; i < toPrint->children.size(); i++)
			print(toPrint->children[i]);
		if(toPrint->node_id != 0)//root will break things
			cout << "Node: " << toPrint->node_id << " parent: " << toPrint->parent->node_id << " object: " << toPrint->object << endl;
			
		}
	
};
