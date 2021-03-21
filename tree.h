//
// Created by Juno Wang on 3/19/21.
//

#ifndef CPTS471PROJECT2_TREE_H
#define CPTS471PROJECT2_TREE_H
#include <map>
#include <string>
struct Node{
    // create the new node with the parents and suffix
    Node(std::string const &_input, Node *_uPrime, size_t _i= std::string::npos,size_t _j = std::string::npos);//when build the node we give
    void findPath(size_t i);
    void compareInput(size_t i);
    void print() const;// call print won't change the node
    std::string const &input;
    Node *uPrime;//parent
    Node *v;//suffix link
    int node_id;
    int leaf_id;
    int string_depth;
    //std::pair<size_t,size_t> start;//not sure what this is for yet
    size_t i;//beginning of the string
    size_t j;//end of the string
    //we may need more children, perhaps a vector of em? three is good for a start
    std::map<char, Node*> u;//children
    static int max_nodes;
    static int max_leaves;


};
class Tree{
public:
    Tree(std::string const &seq);
    void print() const;//print won't change the tree

protected:// this is just for the tree
    std::string sequence; //whole sequence
//    std::string currentSequence; //the sequence after we drop the first letter
    Node *root;
//    Node *current; //where we are in the tree
    int nodeCount;

    void createHead();

    void buildNaiveTree();

    Node *findNode(Node *tryThis);






};

#endif //CPTS471PROJECT2_TREE_H
