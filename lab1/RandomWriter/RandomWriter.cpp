/*
 * File: RandomWriter.cpp
 * ----------------------
 * [TODO: fill in your name and student ID]
 * Name: 姓名
 * Student ID: 5120379000
 * This file is the starter project for the random writer problem.
 * [TODO: extend the documentation]
 */

#include <fstream>
#include <iostream>
#include <string>
#include "console.h"
#include "map.h"
#include "random.h"
#include "strlib.h"
#include "vector.h"
#include "filelib.h"
using namespace std;

string SIP_GetMost(const Map<string, int> &v)
{
  if(v.size() == 0) return "";

  typedef Map<string, int> tp;
  tp::iterator pos = v.begin();
  int fqbase = v.get(*pos);
  
  for(tp::iterator it = v.begin(); it != v.end(); ++it)
  {
    int fq = v.get(*it);
    if(fq > fqbase)
    {
      fqbase = fq;
      pos = it;
    }
  }
  
  return *pos;
}


int main() {
    

  ifstream ifs;
  do
  {
    cout << "Please enter filenames containing source text:";
    string fname;
    cin >> fname;
    cin.sync();
    ifs.open(fname.c_str());
  }
  while(!ifs);

  int order = 0;
  do
  {
    cout << "What order of analysis? (a number from 1 to 10):";
    cin >> order;
    cin.sync();
  }
  while(!cin || !(order >= 1 && order <= 10));

  cout << "Analyzing ... please wait.\n";

  string cur, last;
  Map<string, Vector<char> > later;
  Map<string, int> freq;

  char ch;
  while(ifs.get(ch))
  {
    if(cur.size() == order) cur = cur.substr(1);
    cur += ch;
    
    if(cur.size() == order)
    {
      int f = freq.get(cur);
      freq.put(cur, f + 1);
    }

    if(last != "")
    {
      Vector<char> vf = later.get(last);
      vf.push_back(ch);
      later.put(last, vf); //update later
    }

    if(cur.size() == order) last = cur;

  }

  ifs.close();

  string opt = SIP_GetMost(freq);

  while(opt.size() < 2000)
  {
    string seed = opt.substr(opt.size() - order, order);
    //cout << "seed: " << seed << endl;

    Vector<char> vf = later.get(seed);
    if(vf.isEmpty()) opt += (char)randomInteger('a', 'z');
    else opt += vf[randomInteger(0, vf.size() - 1)];
  }

  cout << opt;
  return 0;
}
