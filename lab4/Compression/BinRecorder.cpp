#include "BinRecorder.h"
#include <stdexcept>
using namespace std;

BinRecorder::BinRecorder()
  : data(0), len(0) {}


//后进后出 先进先出
//前置存储取数据方便 后置存数据方便
//这里用的是前置
void BinRecorder::push(bool b)
{
  if(full()) throw logic_error("buffer full!");

  data |= (char)b << (7 - len);
  len++;
}

bool BinRecorder::pop()
{
  if(empty()) throw logic_error("buffer empty!");

  bool b = (data >> 7) & 1;
  data <<= 1;
  len--;
  return b;
}

bool BinRecorder::full() const
{ return len == 8; }

bool BinRecorder::empty() const
{ return len == 0; }

unsigned char BinRecorder::ToUChar() const
{ return data; }

void BinRecorder::FromUChar(unsigned char uc)
{
  data = uc;
  len = 8;
}

void BinRecorder::clear()
{
  data = 0;
  len = 0;
}


