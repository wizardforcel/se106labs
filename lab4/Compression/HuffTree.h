#ifndef HUFFTREE_H
#define HUFFTREE_H

#include <vector>
#include <iostream>
#include "FreqInfo.h"
using std::vector;
using std::istream;

class HuffTree
{
private:
  struct Node
  {
    char data;
    Node *left;
    Node *right;

    Node(char d = 0, Node *l = 0, Node *r = 0);
  };

  Node *root;

  void DeleteTree(Node *n);

  HuffTree(const HuffTree &ht);
  HuffTree& operator= (const HuffTree &ht);

public:

  HuffTree(const vector<char> &vc);
  ~HuffTree();

  bool GetNum1(char chr, int &num) const;
  bool GetChrByNum1(int num, char &chr) const;
  int GetLen() const;
};

#endif //HUFFTREE_H
