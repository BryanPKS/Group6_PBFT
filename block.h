#ifndef __block_H
#define __block_H

#include <string>

class block
{
private:
  unsigned long pHash; // Previous blocks hash
  unsigned long bHash; // This blocks hash
  std::string data; // Data in block
  
  unsigned long calculateHash();
  
public:
  block(int prevHash, std::string newData);
  unsigned long getHash() { return bHash; }
  unsigned long getpHash() { return pHash; }
  std::string getData() { return data; }
};

#endif
