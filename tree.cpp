#include"tree.h"
#include<iostream>
#include<vector>
#include<string>
#include<utility>
#include <sstream>

using namespace std;
int Node::nextLeafId = 0;
int Node::nextInternalId = 0;
vector<Node *> Node::allNodes;
vector<Node *> Node::allLeaves;

Node::Node(Node *_parent, std::string const &_input, size_t _i, size_t _j):
        parent(_parent),
        input(_input),
        i(_i),
        j(_j == 0 ? input.size() : _j),
        nodeId(0),
        suffixLink(parent ? nullptr : this)
{
    if (parent) {
        parent->children[input[i]] = this;
    }

    // cout << allNodes.size() << ": " << ToString() << endl;
    allNodes.push_back(this);
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
        if (input[iChild] != input[iParent]) {
            return iChild - i;
        }
    }
    return j;
}
Node* Node::NodeHops(size_t bPrime){
    Node* path = children[input[bPrime]];
    return Match(bPrime);
}
void Node::FindPath(size_t i) {
    char firstChar(input[i]);
    if (children[firstChar] == nullptr) {
        Node *child = new Node(this, input, i);
        child->nodeId = ++nextLeafId;
        allLeaves.push_back(child);

        if (parent -> parent) { // parent
            if (parent->suffixLink) {
                // Case I.A: SL(u) is known, u' is not root.
                //the new child's first letter index
                suffixLink->FindPath(child->i);

            } else {
                // Case II.A: SL(u) is unknown, u' is not root.
                //get the gradparent
                Node* UPrime = parent->parent;
                Node* VPrime =  UPrime-> suffixLink;
                Node* v = VPrime -> NodeHops(child -> i);
                parent-> suffixLink = v;
                v->FindPath(child->i);
            }
        } else {
            if (suffixLink) {

                // Case I.B: SL(u) is known, u' is root.
                //no parent  we already have the
                //i is the current
                suffixLink->FindPath(child -> i);
            } else {

                // Case II.B: SL(u) is unknown, u' is root.
                Node* UPrime = parent->parent;
                Node* VPrime =  UPrime-> suffixLink;
                Node* v = VPrime -> NodeHops(child -> i);
                parent-> suffixLink = v;
                v->FindPath(child->i);
            }
        }
        return;
    }
    Node *child = children[firstChar];
    child->Match(i);
}

Node* Node::Match(size_t iParent) {
    size_t matchLength = lengthOfLongestMatch(iParent);

    // cout << "Node::FindPath(iTh=" << iParen
    //      << " (\'" << input[i]
    //      << "\')): matches " << matchLength
    //      << " of Node " << ToString()
    //      << endl;

    if (matchLength < length()) {
        size_t parentSplitAt = iParent + matchLength;
        size_t splitAt = i + matchLength;
        Node *head = new Node(parent, input, i, splitAt);
        head->children[input[splitAt]] = this;
        parent = head;
        i = splitAt;

        head->nodeId = --nextInternalId;

        Node *leaf = new Node(head, input, parentSplitAt);

        leaf->nodeId = ++nextLeafId;
        allLeaves.push_back(leaf);
        return head;
    } else {
        FindPath(i + matchLength);
    }
    return this;
}

void Node::Display() const {
    size_t depth = Depth();
    static string const indentation
            ("                                                                                ");
    cout << indentation.substr(0, 4 * depth)
         << "[" << (parent ? input[i] : '^')
         << "] " << ToString()
         << endl;
    for (auto const &c: children) {
        c.second->Display();
    }
}

SuffixTree::SuffixTree(string const &_input, string const &_alphabet):
        input(_input + "$"),
        alphabet(_alphabet),
        root(new Node(nullptr, input))
{
    cout << "SuffixTree::SuffixTree(input=" << _input << ", alphabet=" << alphabet << endl;
    cout << "SuffixTree::SuffixTree(): initial:" << endl;
    Display();

    for (size_t i = 0; i < input.size(); ++i) {
        root->FindPath(i);

        cout << endl
             << "SuffixTree::SuffixTree(): after insertion #" << i
             << ", '" << input.substr(i)
             << "'" << endl;
        Display();
    }
}

void SuffixTree::Display() const {
    root->Display();
}