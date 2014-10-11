#include "utility.h"
#include <ctype.h>

#define isvarname(a) (isalnum(a) || (a) == '_')

int skipblank(const string &str, int index)
{
  int len = str.size();
  while(index != len && str[index] == ' ')
    index++;
  return index;
}

bool parseint(const string &str, int &index, int &res)
{
  if(!isdigit(str[index])) return false;
  int end = index;
  int len = str.size();
  while(isdigit(str[end]) && end != len)
    end++;
  string tmp = str.substr(index, end - index);
  res = stoi(tmp);
  index = end;
  return true;
}

bool parseletter(const string &str, int &index, string &res)
{
  if(!isalpha(str[index])) return false;
  int end = index;
  int len = str.size();
  while(isalpha(str[end]) && end != len)
    end++;
  res = str.substr(index, end - index);
  index = end;
  return true;
}

bool parsevar(const string &str, int &index, string &res)
{
  if(!isalpha(str[index])) return false;
  int end = index;
  int len = str.size();
  while(isvarname(str[end]) && end != len)
    end++;
  res = str.substr(index, end - index);
  index = end;
  return true;
}

string stolower(const string &str)
{
  string res = str;
  int len = res.size();
  for(int i = 0; i < len; i++)
  {
    if(isupper(res[i]))
      res[i] = tolower(res[i]);
  }
  return res;
}

bool isint(const string &str)
{
  int index = skipblank(str, 0);
  if(!(isdigit(str[index]) || str[index] == '-'))
    return false;
  
  index++;
  int len = str.size();
  for( ; index < len && str[index] != ' '; index++)
  {
    if(!isdigit(str[index])) return false;
  }
  index = skipblank(str, index);
  if(index != len) return false;
  else return true;

}
