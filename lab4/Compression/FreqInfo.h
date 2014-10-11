#ifndef FREQINFO_H
#define FREQINFO_H

struct FreqInfo
{
  char chr;
  unsigned int freq;

  FreqInfo() : chr(0), freq(0) {}
  FreqInfo(char c, unsigned int f) : chr(c), freq(f) {}

};


static bool operator< (const FreqInfo &freq1, const FreqInfo &freq2)
{ return freq1.freq < freq2.freq; }

static bool operator<= (const FreqInfo &freq1, const FreqInfo &freq2)
{ return freq1.freq <= freq2.freq; }

static bool operator> (const FreqInfo &freq1, const FreqInfo &freq2)
{ return freq1.freq > freq2.freq; }

static bool operator>= (const FreqInfo &freq1, const FreqInfo &freq2)
{ return freq1.freq >= freq2.freq; }

static bool operator== (const FreqInfo &freq1, const FreqInfo &freq2)
{ return freq1.freq == freq2.freq; }

static bool operator!= (const FreqInfo &freq1, const FreqInfo &freq2)
{ return freq1.freq != freq2.freq; }

#endif //FREQINFO_H
