#include"tree.h"
#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include <sstream>

using std::cout;
using std::endl;
using std::map;
using std::string;
using std::vector;

int Node::nextLeafId = 0;
int Node::nextInternalId = 0;
vector<Node *> Node::allNodes;
vector<Node *> Node::allLeaves;
//Node *Node::lastNewInternalNode = nullptr;

//use size t to store the max size
Node::Node(Node *_parent, std::string const &_input, size_t _i, size_t _j) :
        parent(_parent),
        input(_input),
        i(_i),
        j(_j == 0 ? input.size() : _j),
        color(j < input.size() ? -1 : current_color),
        nodeId(0),
        suffixLink(parent ? nullptr : this) {
    assert(j <= input.size());
    assert(i <= j);


    if (parent) {
        parent->children[input[i]] = this;
    }

    allNodes.push_back(this);
    // if there is a $, new node get new color
    if (input[i] == '$') {
        current_color++;
    }
}

int Node::p2_process() {

    // find if we got any children
    if (children.empty()) {
        // if children empty, return the color of the leaf. doesnt have the children.
        return color;
    }
    // get a pair of each children char that starts the child substring(first char of child)
    //second part is the pointer to the child node
    //
    // getting the color of the first child, setting the ourcolor to the color of the first child
    color = children.begin()->second->p2_process();
    for (auto child: children) {
        int c = child.second->p2_process();
        // same color with the child
        if (color != c) {
            //current color -1  mix color
            color = -1;
        }
    }
    return color;
}

Node *Node::getRoot() {
    Node *root;
    for (root = this; root->parent; root = root->parent) {}
    return root;
}

string Node::IdToString() const {
    std::stringstream out;
    if (nodeId <= 0) {
        out << "U" << -nodeId;
    } else {
        out << "L" << nodeId;
    }
    return out.str();
}

//print out the tree and parent
string Node::ToString() const {
    std::stringstream out;
    out << "nodeId=" << IdToString()
        << ", parentId=" << (parent ? parent->IdToString() : "<none>")
        << ", depth=" << Depth();
    if (!IsALeaf()) {
        out << ", suffixLink=" << (suffixLink ? suffixLink->IdToString() : "<unknown>");
    }
    out << ", i=" << i
        << ", j=" << j
        << ", '" << input.substr(i, j - i)
        << "'";
    return out.str();
}

size_t Node::lengthOfLongestMatch(size_t iParent) const {
    for (size_t iChild = i; iChild < j; ++iChild, ++iParent) {

        assert(iParent < input.size());

        if (input[iChild] != input[iParent]) {
            return iChild - i;
        }
    }
    return j - i;
}

void Node::FindPath(size_t iPath) {
    if (iPath < input.size()) {
        assert(iPath <= j);

        char firstChar(input[iPath]);
        if (children[firstChar] == nullptr) {
            Node *child = new Node(this, input, iPath);
            child->nodeId = ++nextLeafId;
            allLeaves.push_back(child);
            return;
        }
        Node *child = children[firstChar];
        child->Match(iPath);
    }
}

// trying to meet 4 cases of the suffix link
void Node::Match(size_t iParent) {
    size_t matchLength = lengthOfLongestMatch(iParent);

    if (matchLength < length()) {
        size_t parentSplitAt = iParent + matchLength;
        assert(parentSplitAt < input.size());

        size_t splitAt = i + matchLength;
        assert(splitAt < j);

        Node *head = new Node(parent, input, i, splitAt);
        head->children[input[splitAt]] = this;
        parent = head;
        i = splitAt;

        head->nodeId = --nextInternalId;

        Node *leaf = new Node(head, input, parentSplitAt);

        leaf->nodeId = ++nextLeafId;
        allLeaves.push_back(leaf);

        // Get the start of the edge spanning from head (u) to its parent
        // (u').

        size_t iBeta = head->parent->i;

        // Cases II.{A,B} SL(u) is unknown (a.k.a. u->suffixLink ==
        // nullptr) and u' is [not] the root:

        Node *u = head;
        assert(u->suffixLink == nullptr);
        Node *uPrime = head->parent;
        if (uPrime->parent != nullptr) {

            // Case II.A

            assert(uPrime->suffixLink);
            Node *vPrime = uPrime->suffixLink;
            vPrime->NodeHops(u, iBeta + 1, j);
        } else {

            // Case II.B

            assert(uPrime->suffixLink);
            Node *vPrime = uPrime->suffixLink;
            vPrime->NodeHops(u, iBeta, j);
        }

        return;
    }

    // The lengths match, so we don't have to split an edge.

    FindPath(i + matchLength);
}

void Node::NodeHops(Node *linkfrom, size_t iBetaPrime, size_t jBetaPrime) {
    if (iBetaPrime == jBetaPrime) {
        linkfrom->suffixLink = this;
        return;
    }

    FindPath(iBetaPrime);
}


void Node::Display() const {
    size_t depth = Depth();
    static string const indentation
            ("                                                                                ");
//    cout << indentation.substr(0, 4 * depth)
//         << "[" << (parent ? input[i] : '^')
//         << "] " << ToString()
//         << endl;
    for (auto const &c: children) {
        c.second->Display();
    }
}

//constructing the  suffix tree
SuffixTree::SuffixTree(string const &_input, string const &_alphabet) :
        input(_input + "$"),
        alphabet(_alphabet),
        root(new Node(nullptr, input)) {
//    cout << "SuffixTree::SuffixTree(input=" << _input << ", alphabet=" << alphabet << endl;
//    cout << "SuffixTree::SuffixTree(): initial:" << endl;
//    Display();

    for (size_t i = 0; i < input.size(); ++i) {
        root->FindPath(i);
//
//        cout << endl
//             << "SuffixTree::SuffixTree(): after insertion #" << i
//             << ", '" << input.substr(i)
//             << "'" << endl;
//        Display();
    }
}

void SuffixTree::Display() const {
    root->Display();
}
void SuffixTree::p2_process_children(){
    root->p2_process();
}


