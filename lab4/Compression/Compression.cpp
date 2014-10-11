#include <iostream>
#include <string>
#include <fstream>
#include <cstdlib>
#include <map>
#include <vector>
#include <stdexcept>
#include <algorithm>
#include <stdarg.h>
#include "FreqInfo.h"
#include "HuffTree.h"
#include "BinRecorder.h"
using namespace std;

//#define _DEBUG

using uchar = unsigned char;
using uint = unsigned int;

//function declearation
string FReadAllText(const char *fname);
void Writebit(fstream &fs, BinRecorder &rec, bool bit);
bool Readbit(fstream &fs, BinRecorder &rec);
void compress(const string &inputFilename, const string &outputFilename);
void decompress(const string &inputFilename, const string &outputFilename);

string FReadAllText(const string &fname)
{
  ifstream ifs(fname, ios::in | ios::binary);
  if(!ifs) throw logic_error("file open error");
  ifs.seekg(0, ios::end);
  int fsize = ifs.tellg();
  ifs.seekg(0, ios::beg);
  string str(fsize, ' ');
  ifs.read((char *)str.c_str(), fsize);
  ifs.close();
  return str;
}

void Writebit(ofstream &ofs, BinRecorder &rec, bool bit)
{
  if(rec.full()) 
  {
    uchar data = rec.ToUChar();
    ofs.write((char *)&data, sizeof(data));
    rec.clear();
  }
  rec.push(bit);
}

bool Readbit(ifstream &ifs, BinRecorder &rec)
{
  if(rec.empty())
  {
    uchar data;
    ifs.read((char *)&data, sizeof(data));
    if(ifs.eof()) logic_error("input file format error :3");
    rec.FromUChar(data);
  }
  return rec.pop();
}

void compress(const string &inputFilename, const string &outputFilename) 
{  
  ofstream ofs(outputFilename, ios::out | ios::trunc | ios::binary);
  if(!ofs) throw logic_error("open output file error!");

#ifdef _DEBUG
  string log_fname = inputFilename + ".log";
  ofstream logfs(log_fname, ios::out | ios::trunc);
#endif

  string filestr = FReadAllText(inputFilename);
  int fsize = filestr.size();
  if(fsize == 0) //empty file
  {
    ofs.close();
    return;
  }
  
  map<char, uint> freqtable;
  for(int i = 0; i < fsize; i++)
  {
    char tmp = filestr[i];
    uint f = freqtable[tmp];
    freqtable[tmp] = f + 1;
  }
  
  vector<FreqInfo> vfreq;
  for(const auto &e : freqtable)
  {
    FreqInfo fi(e.first, e.second);
    vfreq.push_back(fi);
  }
  sort(vfreq.rbegin(), vfreq.rend());

  vector<char> vc;
  for(const auto &e : vfreq)
    vc.push_back(e.chr);

  int hdrsize = vc.size();
  ofs.write((char *)&hdrsize, sizeof(hdrsize));
  for(const auto &e : vc)
    ofs.put(e);
  ofs.write((char *)&fsize, sizeof(fsize));

  HuffTree ht(vc);
  BinRecorder br;
  for(int i = 0; i < fsize; i++)
  {
    char tmp = filestr[i];
    int num;
    if(!ht.GetNum1(tmp, num))
      throw logic_error("encoding error!");
    for(int i = 0; i < num; i++)
      Writebit(ofs, br, 1);
    Writebit(ofs, br, 0);
#ifdef _DEBUG
    logfs << (uint)(uchar)tmp << ' ' << num << endl;
#endif
  }
  if(!br.empty()) ofs << br.ToUChar(); 

  ofs.close(); 
#ifdef _DEBUG 
  logfs.close();
#endif
};

void decompress(const string &inputFilename, const string &outputFilename) 
{
  ifstream ifs(inputFilename, ios::in | ios::binary);
  if(!ifs) throw logic_error("open input file error!");
  ofstream ofs(outputFilename, ios::out | ios::trunc | ios::binary);
  if(!ofs)
  {
    ifs.close();
    throw logic_error("open output file error!");
  }

#ifdef _DEBUG
  string log_fname = inputFilename + ".log";
  ofstream logfs(log_fname, ios::out | ios::trunc);
#endif

  int hdrsize;
  ifs.read((char *)&hdrsize, sizeof(hdrsize));
  if(ifs.eof()) return; //empty file

  vector<char> vc;
  for(int i = 0; i < hdrsize; i++)
  {
    int chr = ifs.get();
    if(ifs.eof()) throw logic_error("input file format error! :1");
    vc.push_back(chr);
  }

  int binsize;
  ifs.read((char *)&binsize, sizeof(binsize));
  if(ifs.eof()) throw logic_error("input file format error! :2");
  HuffTree ht(vc);
  BinRecorder br;
  for(int i = 0; i < binsize; i++)
  {
    int num = 0;
    while(true)
    {
      bool b = Readbit(ifs, br);
      if(b == 0) break;
      num++;
    }
    char chr;
    if(!ht.GetChrByNum1(num, chr))
      throw logic_error("char not found!");
    ofs.put(chr);
#ifdef _DEBUG
    logfs << (uint)(uchar)chr << ' ' << num << endl;
#endif
  }

  ifs.close();
  ofs.close();
#ifdef _DEBUG
  logfs.close();
#endif
}

void useage(string prog) {
  cerr << "Useage: " << endl
      << "    " << prog << "[-d] input_file output_file" << endl;
  exit(2);
}

int main(int argc, char* argv[]) {
  int i;
  string inputFilename, outputFilename;
  bool isDecompress = false;
  for (i = 1; i < argc; i++) {
    if (argv[i] == string("-d")) isDecompress = true;
    else if (inputFilename == "") inputFilename = argv[i];
    else if (outputFilename == "") outputFilename = argv[i];
    else useage(argv[0]);
  }
  if (outputFilename == "") useage(argv[0]);
  try
  {
    if (isDecompress) decompress(inputFilename, outputFilename);
    else compress(inputFilename, outputFilename);
  }
  catch(exception &ex)
  { cout << ex.what() << endl; }
  return 0;
}
