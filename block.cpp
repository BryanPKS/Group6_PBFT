#include "block.h"
unsigned long block::calculateHash() //calculates hash using data from current block 
  {
    std::string temp = data;
    return std::hash<std::string>()(temp.append(std::to_string(pHash)));
  }

  block::block(int prevHash, std::string newData) //updates block variables
  {
    data = newData;
    pHash = prevHash;
    bHash = calculateHash();
  }
