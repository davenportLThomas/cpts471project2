#include"tree.h"
#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include <sstream>

using namespace std;
int Node::max_leaves = 0;
int Node::max_nodes = 0;
std::vector<Node*> Node:: nodes;
Node::Node(string const &_input, Node *_uPrime, size_t _i,size_t _j):
input(_input),
uPrime(_uPrime),
i(_i == string::npos ? 0: _i),// if we dont have the arg, return 0;
j(_j== string::npos ? input.size(): _j),
node_id(max_nodes++),
leaf_id(-1) // no leaf id until assigned
{
if(uPrime == nullptr) {
    //this is the root
}else {
   // this is not the root
}
nodes.push_back(this); //
}
string Node::tostring() const {
    std::stringstream out;
    out<< " ( i = " << i
        << ", j = " << j
        << ", node_id = "<< node_id
        << ", leaf_id= " << leaf_id
        << ")" << input.substr(i,j-i) ;
    return out.str();
}
void Node::print() const {

//    for(size_t c = 0; c < u.size(); ++c){
//        u[c] -> print();
//    }
    string const spaces("                                               ");
    if(uPrime != nullptr){
        cout<< spaces.substr(0,2*i);
        cout<< tostring() << endl;


    }
    for (auto const kv: u){
        kv.second->print();
    }


}
void Tree::createHead() {
//    root = new Node;
//    root->v = nullptr;
//    current = root;
//    current->value = "ROOT";
//    current->id = -1;//the head it -1
//    current->string_depth = 0;
//    nodeCount = 1;
//    //lets build a tree
//    buildNaiveTree();
};

void Tree::buildNaiveTree() {
    //findNode function here
}

Node *Tree::findNode(Node *tryThis) {
    //check the current string in the node for a match, this algo doesn't feel right
//    for (uint32_t i = 0; i < currentSequence.size(); i++) {
//        if (currentSequence[i] != tryThis->value[i])
//            break;
//        return (tryThis);
//    }
//    //actually traverse the tree is match is not found
//    if (tryThis != nullptr) {
//        for (uint32_t i = 0; i < tryThis->u.size(); i++) {
//            findNode(tryThis->u[i]);
//        }
//    }
        return root;
}

void Node::findPath(size_t i) {
    //naive tree
    char c = input[i];
    if(u.find(c)==u.end()){
        u[c] = new Node(input,this,i); // parts a and b
        u[c] -> leaf_id = max_leaves++; //assgin a leaf id  the node is a leaf now
        cout << "node :: findpath(" << i << "): "  << u[c] -> tostring()<< endl;
        return ;
    }// if this not in the chidren
    u[c]-> compareInput(i); // j will be the npos if the edge label is exhausted
//    cout<<"findPath(" << i << " ('" << input[i]<< "')) j=" << j << endl; // print the char
}
//compareInput will do: if mismatch, break the edge, create a new internal node, create new leaf for s under that node
//then return
void Node::compareInput(size_t iParent){
    if(iParent == i){
        return ; // return end of the child
    }
    //remember where the parent start and end
    size_t iChild;
    size_t jParent;
    for(iChild = i, jParent =iParent ; iChild < j; jParent++, iChild++){
        if(input[iChild] != input[jParent]){
            break;
        }
    }
    cout << "node :: compareInput(" << iParent << "): matchLinks = "<< iChild -i << ", " << tostring()<< endl;

    //the distance between iChild and i is the length of the match
    //if iChild = j, then it's a compelete match otherwise split.
    size_t matchLength = iChild - i;
    if(iChild == j){
        cout << " matchs" << endl;
        findPath(i+matchLength);
        return;
    }
    //split  tail become the child
    Node* tail = new Node(input,this,i+matchLength);
    tail -> leaf_id = leaf_id; // change the leaf id of the tail
    leaf_id = -1; //  if -1, this is a internal node
//    cout<< "node :: compareInput( iParent = " << iParent << ")" << endl;
//    tail->print();
    u[input[i+matchLength]] = tail;
    j = i + matchLength;
    cout << "split: " << tostring() << ", " << tail->tostring()<< endl;
//    findPath(i+matchLength);
}

void Tree::print() const//this is currently VERY VERY rudimentary
{
cout << " tree :: print" << endl;
root -> print(); // telling this root to print


}

Tree::Tree(string const &seq) :
sequence(seq + "$"),
root(new Node(sequence,nullptr))
{
    for(size_t i = 0; i < sequence.size();++i){
        root->findPath(i);// add a child start with the ith char

    }
//    sequence.assign(seq);
//    currentSequence.assign(seq);
//    createHead();
//    printTree();
}

