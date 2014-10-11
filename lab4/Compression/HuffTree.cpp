#include "HuffTree.h"
#include <stdexcept>
#include <vector>
using namespace std;

HuffTree::Node::Node(char d, Node *l, Node *r)
  : data(d), left(l), right(r) {}


HuffTree::~HuffTree()
{
  DeleteTree(root);
}

HuffTree::HuffTree(const vector<char> &vc)
{
  if(vc.size() == 0) throw logic_error("number of ele too little");

  vector<Node *> vnode;
  for(const auto &e : vc)
  {
    Node *n = new Node(e, 0, 0);
    vnode.push_back(n);
  }

  while(vnode.size() >= 2)
  {
    Node *n1 = vnode[vnode.size() - 1];
    vnode.pop_back();
    Node *n2 = vnode[vnode.size() - 1];
    vnode.pop_back();
    Node *n = new Node(0, n2, n1);
    vnode.push_back(n);
  }

  root = vnode[0];
}

void HuffTree::DeleteTree(Node *n)
{
  if(n == 0) return;
  delete n->left;
  DeleteTree(n->right);
  delete n;
}


int HuffTree::GetLen() const
{
  Node *p = root;
  int len = 0;
  while(p->left != 0)
  {
    p = p->right;
    len++;
  }
  return len + 1;
 
}


bool HuffTree::GetNum1(char chr, int &num) const
{
  Node *p = root;
  int len = 0;

  while(p->left != 0)
  {
    if(p->left->data == chr)
    {
      num = len;
      return true;
    }
    p = p->right;
    len++;
  }
  if(p->data == chr)
  {
    num = len;
    return true;
  }
  else return false;
}


bool HuffTree::GetChrByNum1(int num, char &chr) const
{
  Node *p = root;
  int len = 0;
  while(p->left != 0)
  {
    if(len == num)
    {
      chr = p->left->data;
      return true;
    }
    p = p->right;
    len++;
  }
  if(len == num)
  {
    chr = p->data;
    return true;
  }
  else return false;
}










