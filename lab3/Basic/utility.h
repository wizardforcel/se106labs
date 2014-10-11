#ifndef UTILITY_H
#define UTILITY_H

#include <string>
using namespace std;

int skipblank(const string &str, int index);

bool parseint(const string &str, int &index, int &res);

bool parseletter(const string &str, int &index, string &res);

bool parsevar(const string &str, int &index, string &res);

string stolower(const string &str);

bool isint(const string &str);

#endif //UTILITY_H
