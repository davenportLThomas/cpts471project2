//
// Created by Juno Wang on 3/19/21.
//

#ifndef CPTS471PROJECT2_TREE_H
#define CPTS471PROJECT2_TREE_H

#include <map>
#include <string>

class Node {
public:
    Node(Node *_parent, std::string const &_input, size_t _i = 0, size_t _j = 0);
    Node *getRoot();
    size_t length() const { return j - i; }
    size_t lengthOfLongestMatch(size_t iParent) const;
    std::string ToString() const;
    std::string IdToString() const;
    void Match(size_t iParent);
    void NodeHops(Node *linkFrom, size_t iBetaPrime, size_t jBetaPrime);

    bool IsALeaf() const { return nodeId > 0; }
    void Display() const;
    void DisplayStringDepth() const;
    void DisplayBWTIndex() const;

    // FindPath(args): finds the path starting at the specified node
    // argument that spells out the longest possible prefix of the
    // specified string argument, and then insert the next suffix.

    void FindPath(size_t i);
    size_t Depth() const { return parent ? parent->Depth() + 1 : 0; }

    // NodeHops(args): does node hopping child to child until string
    // Beta (or Beta') is exhausted, depending on the case.

    // void NodeHops(args);

    static std::vector<Node *> allNodes;
    static std::vector<Node *> allLeaves;
    static Node *lastNewInternalNode;

protected:
    Node *parent;                 // nullptr if this is the root
    std::string const &input;     // the original input + "$"
    size_t i;                     // Index of start of the parent-to-here edge label
    size_t j;                     // Index of end of the parent-to-here edge label
    int nodeId;                   // the node id (across all nodes)
    Node *suffixLink;
    std::map<char, Node *> children; // Nodes of any children, index by 1st character

    static int nextLeafId;
    static int nextInternalId;
};

class SuffixTree {
public:
    SuffixTree(std::string const &_input, std::string const &_alphabet);
    std::string ToString() const;

    void Display() const;
    void DisplayStringDepth() const;
    void DisplayBWTIndex() const;

protected:
    std::string const input;
    std::string const alphabet;
    Node *root;
    // Node u;                       // Suffix leaf i-1's parent
    // Node v;                       // Suffix link SL(u)
    // Node uPrime;                  // Parent of u (if one exists)
    // Node vPrime;                  // SL(uPrime) - maight be parent of v
};

#endif // #ifndef
