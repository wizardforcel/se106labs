#ifndef BINRECORDER_H
#define BINRECORDER_H

#include <iostream>
using std::istream;
using std::ostream;

class BinRecorder
{

private:
  unsigned char data;
  int len;

public:
  
  BinRecorder();

  bool empty() const;
  bool full() const;
  
  void push(bool b);
  bool pop();

  unsigned char ToUChar() const;
  void FromUChar(unsigned char uc);

  void clear();


};


#endif //BINRECORDER_H
