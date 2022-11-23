#include "block.h"
unsigned long block::calculateHash()
  {
    std::string temp = data;
    return std::hash<std::string>()(temp.append(std::to_string(pHash)));
  }

  block::block(int prevHash, std::string newData)
  {
    data = newData;
    pHash = prevHash;
    bHash = calculateHash();
  }
