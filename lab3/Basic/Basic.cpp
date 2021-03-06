#include <iostream>
#include <string>
#include <map>
#include <exception>
#include <stdexcept>
#include <algorithm>
using namespace std;

#include "utility.h"
#include "exprparser.h"

//Globals

map<string, int> VarTable;
map<int, string> CodeTable;
exprparser Parser(&VarTable);

//Functions dclr

bool builtin_cmd(const string &cmd);
void listall();
void do_run();
void do_work();
int parseline(const string &str);

void do_print(const string &cmd, int index);
void do_let(const string &cmd, int index);
void do_input(const string &cmd, int index);
int do_if(const string &cmd, int index);

//Function impl

int do_if(const string &cmd, int index)
{
  //expr1
  index = skipblank(cmd, index);
  int num1 = Parser.parse(cmd, index);

  //op, expr2
  index = skipblank(cmd, index);
  char op = cmd[index];
  bool jmp;
  if(op == '<')
  {
    index = skipblank(cmd, index + 1);
    int num2 = Parser.parse(cmd, index);
    jmp = (num1 < num2);
  }
  else if(op == '>')
  {
    index = skipblank(cmd, index + 1);
    int num2 = Parser.parse(cmd, index);
    jmp = (num1 > num2);
  }
  else if(op == '=')
  {
    index = skipblank(cmd, index + 1);
    int num2 = Parser.parse(cmd, index);
    jmp = (num1 == num2);
  }
  else throw logic_error("STATAX ERROR");

  //then
  index = skipblank(cmd, index);
  string ltr;
  if(!parseletter(cmd, index, ltr))
    throw logic_error("STATAX ERROR");
  ltr = stolower(ltr);
  if(ltr != "then")
    throw logic_error("STATAX ERROR");

  //line num
  index = skipblank(cmd, index);
  int line;
  if(!parseint(cmd, index, line))
    throw logic_error("STATAX ERROR");
  if(jmp) return line;
  else return -1;

}

void do_print(const string &cmd, int index)
{
  index = skipblank(cmd, index);
  int res = Parser.parse(cmd, index, true);
  cout << res << endl;
}

void do_input(const string &cmd, int index)
{
  index = skipblank(cmd, index);
  string var;
  if(!parsevar(cmd, index, var))
    throw logic_error("STATAX ERROR");
  var = stolower(var);
  
  /*int value;
  cin >> value;
  cin.get();
  if(!cin) throw logic_error("INVALID NUMBER");*/

  string sval;
  bool valid;
  do {
  cout << " ? ";
  getline(cin, sval);
  valid = isint(sval);
  if(!valid)
    cout << "INVALID NUMBER" << endl;
  }
  while(!valid);
  int value = stoi(sval);

  VarTable[var] = value;
}

void do_let(const string &cmd, int index)
{
  //var
  index = skipblank(cmd, index);
  string var;
  if(!parsevar(cmd, index, var))
    throw logic_error("STATAX ERROR");
  var = stolower(var);
  //=
  index = skipblank(cmd, index);
  if(cmd[index] != '=')
    throw logic_error("STATAX ERROR");
  //expr
  index = skipblank(cmd, index + 1);
  int res = Parser.parse(cmd, index, true);
  VarTable[var] = res;
}


// >=0: goto -1: cont -2: end
int parseline(const string &str)
{
  int index = 0;
  string ltr;
  if(!parseletter(str, index, ltr))
    throw logic_error("STATAX ERROR");
  ltr = stolower(ltr);
  
  if(ltr == "rem")
    return -1;
  else if(ltr == "input")
  {
    do_input(str, index);
    return -1;
  }
  else if(ltr == "end")
    return -2;
  else if(ltr == "goto")
  {
    int line;
    index = skipblank(str, index);
    if(!parseint(str, index, line))
      throw logic_error("STATAX ERROR");
    return line;
  }
  else if(ltr == "print")
  {
    do_print(str, index);
    return -1;
  }
  else if(ltr == "let")
  {
    do_let(str, index);
    return -1;
  }
  else if(ltr == "if")
  {
    return do_if(str, index);
  }
  else throw logic_error("STATAX ERROR");
  
}

void do_run()
{
  //sort(CodeTable.begin(), CodeTable.end());
  for(auto it = CodeTable.begin(); it != CodeTable.end(); )
  {
    int res = parseline(it->second);
    if(res >= 0) 
    {
      it = CodeTable.find(res);
      if(it == CodeTable.end())
        throw logic_error("LINE NUMBER ERROR");
    }
    else if(res == -2) break;
    else //res == -1
      ++it;
  }
}

void listall()
{
  //sort(CodeTable.begin(), CodeTable.end());
  for(const auto &e : CodeTable)
    cout << e.first << ' ' << e.second << endl;
}

bool builtin_cmd(const string &cmd)
{
  string ltr;
  int index = skipblank(cmd, 0);
  if(!parseletter(cmd, index, ltr))
    return false;
  ltr = stolower(ltr);

  if(ltr == "quit")
    exit(0);
  else if(ltr == "help")
  {
    cout << "张子辰 5110369009" << endl;
    return true;
  }
  else if(ltr == "clear")
  {
    CodeTable.clear();
    VarTable.clear();
    return true;
  }
  else if(ltr == "list")
  {
    listall();
    return true;
  }
  else if(ltr == "run")  
  {
    do_run();
    return true;
  }
  else return false;
}

void do_work()
{
  try {

  //cout << "Please input command:\n";
  string cmd;
  getline(cin, cmd);
  if(cmd == "") return; //ignore empty line

  //parse built-in
  if(builtin_cmd(cmd)) return;
  
  //parse line number
  int index = skipblank(cmd, 0);
  int line = 0;
  if(parseint(cmd, index, line))
  {
    index = skipblank(cmd, index);
    string state = cmd.substr(index);
    if(state == "") //remove it
    {
      auto it = CodeTable.find(line);
      if(it != CodeTable.end())
        CodeTable.erase(it);
    }
    else //add it
      CodeTable[line] = state;
    return;
  }

  //parse let, print, input
  string ltr;
  if(!parseletter(cmd, index, ltr))
    throw logic_error("STATAX ERROR");
  ltr = stolower(ltr);
  //index = skipblank(cmd, index);
  if(ltr == "print")
    do_print(cmd, index);
  else if(ltr == "input")
    do_input(cmd, index);
  else if(ltr == "let")
    do_let(cmd, index);
  else throw logic_error("STATAX ERROR");

  }
  catch(exception &ex)
  { cout << ex.what() << endl; }

}

int main()
{
  while(true)
    do_work();
  return 0;
}
