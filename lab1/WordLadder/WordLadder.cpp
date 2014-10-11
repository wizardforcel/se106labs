/*
 * File: WordLadder.cpp
 * --------------------
 * [TODO: fill in your name and student ID]
 * Name: 张子辰
 * Student ID: 5110369009
 * This file is the starter project for the word ladder problem.
 * [TODO: extend the documentation]
 */

//#include <fstream>

#include <iostream>
#include <string>
#include "console.h"
#include "lexicon.h"
#include "queue.h"
#include "simpio.h"
#include "vector.h"
#include "map.h"
using namespace std;

typedef Vector<string> Ladder;

bool isexist(const string &str, const Ladder &ldr)
{
  size_t sz = ldr.size();
  for(int i = 0; i < sz; i++)
  {
    if(str == ldr[i]) return true;
  }
  return false;
}

//whether them diff from one word
bool matchwords(const string &str1, const string &str2)
{
  size_t sz1 = str1.size(),
         sz2 = str2.size();
  if(sz1 != sz2) return false;
  int diff = 0;
  for(int i = 0; i < sz1; i++)
    if(str1[i] != str2[i]) diff++;
  return diff == 1;
}

void printldr(const Ladder &ldr)
{
  cout << "Found ladder: ";
  size_t sz = ldr.size();
  for(int i = 0; i < sz; i++)
    cout << ldr[i] << " ";
  cout << endl;
}

bool DoWork()
{
  cout << "Enter start word (RETURN to quit): ";
  string src;
  cin >> src;
  cin.sync();
  if(src == "RETURN") return false;

  cout << "Enter destination word: ";
  string dst;
  cin >> dst;
  cin.sync();
  if(src.size() != dst.size())
  {
    cout << "No ladder found." << endl;
    return true;
  }

  Queue<Ladder> que;
  Ladder ldr;
  ldr.push_back(src);
  que.enqueue(ldr);

  Lexicon lex("EnglishWords.dat");
  Ladder already;
  already.push_back(src);

  //fstream fs("log.txt", ios::out | ios::trunc);

  bool find = false;
  while(!que.isEmpty())
  {
    Ladder top = que.dequeue();
    string str = top[top.size() - 1];
    //fs << "str: " << str << endl;
    if(str == dst)
    {
      printldr(top);
      find = true;
      break;
    }
    else if(matchwords(str, dst))
    {
      top.push_back(dst);
      printldr(top);
      find = true;
      break;
    }

    for(Lexicon::iterator it = lex.begin(); it != lex.end(); ++it)
    {
      if(matchwords(*it, str) && !isexist(*it, already))
      {
        //fs << "*it: " << *it << endl;
        already.push_back(*it);
        Ladder tail = top;
        tail.push_back(*it);
        que.enqueue(tail);
      }
    }
  }
  if(!find) cout << "No ladder found." << endl;

  //fs.close();
  return true;
}

int main()
{
  while(DoWork());
  return 0;
}
