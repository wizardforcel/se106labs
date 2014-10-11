#ifndef EXPRPARSER_H
#define EXPRPARSER_H

#include <string>
#include <map>
using namespace std;

class exprparser
{
public:

  exprparser(map<string, int> *vt = 0):
             vartable(vt) {}

  void setvt(map<string, int> *vt) {vartable = vt;}

  //check tail
  int parse(const string &str, int &index, bool chktail = false);

  


private:

  map<string, int> *vartable;

  //deal with add, sub
  int parse_expr(const string &str, int &index);
  //deal with mul, div
  int parse_sub(const string &str, int &index);
  //deal with int, varname, (...)
  int parse_token(const string &str, int &index);

};
#endif //EXPRPARSER_H
