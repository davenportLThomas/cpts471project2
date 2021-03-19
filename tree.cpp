#include"tree.h"
#include<iostream>
#include<vector>
#include<string>
#include<utility>

using namespace std;
int Node::max_leaves = 0;
int Node::max_nodes = 0;
Node::Node(string const &_input, Node *_uPrime, size_t _i,size_t _j):
input(_input),
uPrime(_uPrime),
i(_i == string::npos ? 0: _i),// if we dont have the arg, return 0;
j(_j== string::npos ? input.size(): _j),
node_id(max_nodes++),
leaf_id(max_leaves++)
{
if(uPrime == nullptr) {
    //this is the root
}else {
   // this is not the root
}
}
void Node::print() const {
//    for(size_t c = 0; c < u.size(); ++c){
//        u[c] -> print();
//    }
    for (auto const kv: u){
        kv.second->print();
    }
    if(uPrime != nullptr){
        cout << input.substr(i)<< endl;
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
        return ;
    }// if this not in the chidren
    size_t j = u[c]-> compareInput(i); // j will be the npos if the edge label is exhausted
    cout<<"findPath(" << i << " ('" << input[i]<< "')) j=" << j << endl; // print the char
    // need to do part d in findpath if mismatch
}
size_t Node::compareInput(size_t iParent) const{
    if(iParent == i){
        return j; // return end of the child
    }
    for(size_t iChild = i; iChild < j; iParent++, iChild++){
        if(input[iChild] != input[iParent]){
            return iParent;
        }
    }
    return iParent ;
}

void Tree::print() const//this is currently VERY VERY rudimentary
{
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

