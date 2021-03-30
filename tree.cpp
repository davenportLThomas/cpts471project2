#include<iostream>
#include<string>
#include<vector>
using namespace std;

class Tree{
	string sequence;
	long unsigned int seqPosition = 0;
	struct Node{
		Node *u; //uPrime
		vector<Node*> children;
		string object;
		Node *link;
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
		current->u = root;
		current->object = "";
		current->node_id = nodeCount;
		nodeCount++;
	}

	Node *findPath(Node *tryThis)
	{
		for(uint32_t i = 0; i < tryThis->children.size(); i++)
		{
			if(tryThis->children[i]->object[0] == sequence[0])
			{
				return tryThis->children[i];
			}
			else//look in children's children
			{
				findPath(tryThis->children[i]);
			}

		}	
		return root;
	}

	int matchLength(string object)
	{
		int n = 0;//this will determine string length
		for(uint32_t i = 0; i < sequence.length(); i++)//the sequencce length should be shorter
		{
//			cout << object[i] << " < "  << sequence[i] << endl;
			if(object[i] != sequence[i])
				break;
			n++;
		}
		return n;
	}

	Node *noParentString(string forThisNode)//this acts as a general node builder as well
	{	
		current->children.push_back(new Node);
		Node *temp = current;
		current = current->children[current->children.size() - 1];
		current->object = forThisNode + "$";
		current->u = temp;
		current->node_id = nodeCount;
		nodeCount++;
		return current;
	}

	Node *findNode(Node *tryThis, string findThis)
	{
		for(uint32_t i = 0; i < tryThis->children.size(); i++)
		{
			if(tryThis->children[i]->object[0] == findThis[0])
			{
				return tryThis->children[i];
			}
			else//look in children's children
			{
				findPath(tryThis->children[i]);
			}

		}	
		return root;
	}



	void nodeHop(char b)
	{
		

	}

	void createLink()
	{
		//case 1a - has suffix link and u(u) is not the root
		if(current->node_id != 0);

		//case 1b - has suffix link and it the root
		if(current->node_id == 0);

		//case 2a - does not have suffix link and u'(grandu) is not root
		if(current->node_id != 0);

		//case 2b - does not have suffix link and u'(grandu) is the root
		if(current->node_id == 0);

			
	}

	void uString(int n)
	{
		//split the string
	//	cout <<"Current object: " << current->node_id << endl;
		string forCurrent = current->object;
		string forParent = sequence;
		forCurrent.erase(0, n);
	//	cout << "sequence: " << sequence;
	//	cout << " current: " << forCurrent << " forParent: " << forParent <<endl;
	
		//create first child
		Node *childA = new Node;
		childA->object = forCurrent + "$";
		childA->u = current;
		childA->node_id = nodeCount;
		nodeCount++;
		if(forCurrent[forCurrent.length() - 1] == '$')
			forCurrent.erase(forCurrent.length() - 1, 1);

		//create second child
		Node *childB = new Node;
		childB->object = "$";
		childB->u = current;
		childB->node_id = nodeCount;
		nodeCount++;

		//reset current, which is now u
		current->object = forParent;
		current->children.push_back(childA);
		current->children.push_back(childB);
	}

	/*	
		//first child settings
		if(forCurrent[forCurrent.length() - 1] == '$')
			forCurrent.erase(forCurrent.length() - 1, 1);
		Node *childA = noParentString(forCurrent);	

		//second child settings
		current = current->u;
		cout <<  " The u before the second node is built " << current->object << endl;
		Node *childB = noParentString("");

		//fill u node with new string
		current->u->object = forParent;

		//set new us
		cout << "childA: " << childA->node_id << endl;
		cout << "childB: " << childB->node_id << endl;
		cout << "Temp: " << temp->node_id << endl;
//		if(temp->children.size() > 1)
//		{
//			childA->u = temp->children[1];
//			childB->u = temp->children[1];
//		}
		//create a suffix link if possible
		createLink();

	}*/

	void arrangeChildren()
	{
		current = current->u;
	//	cout << "ready to arrange: " << current->object << endl;
		for(uint32_t i = 0; i < current->children.size() - 1; i++)
		{	
			if(current->children[i]->object[0] > current->children[i + 1]->object[0] ||
					current->children[i + 1]->object[0] == '$')
			{
				Node *temp;
				temp = current->children[i];
				current->children[i] = current->children[i+1];
				current->children[i+1] = temp;
			}
		}	
	}

	void createChild()
	{
//		cout << "------------------------" << endl;
		current = findPath(root);
		int n = matchLength(current->object);
//		cout << "n: " << n << endl;
		if(n == 0)
			noParentString(sequence);
		else if(n > 0)
			uString(n);
		arrangeChildren();
		sequence.erase(0,1);
	}

	void buildTree()
	{
	//	cout << " Node count " << nodeCount << endl;
		//this is how to end
		if(seqPosition == sequence.length())
			return;
		if(nodeCount == 0)
			createRoot();
		else
			createChild();
//		print(root);

	}


	public:
	Tree(string seq)
	{
		this->sequence = seq;
		while(sequence.length() > 0)//this should be zero, changing for testing
			buildTree();
//		print(root);
	}


	void print(Node *toPrint)
	{
		if(toPrint->node_id != 0 )
		{
			for(int i = 0; i < toPrint->u->node_id; i++)
				cout << "   ";
		}
		if(toPrint->node_id != 0)//root will break things
			cout << "Node: " << toPrint->node_id << " u: " << toPrint->u->node_id << " object: " << toPrint->object << endl;
		else
			cout << "Node: 0" << endl;
		for(uint32_t i = 0; i < toPrint->children.size(); i++)
			print(toPrint->children[i]);
	}
	
};
