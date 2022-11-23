#ifndef __blockChain_H
#define __blockChain_H

#include <vector>

class blockChain
{
private:
  std::vector<block> chain;
  block createGenesisBlock() { return block(0, "Genesis"); }
  
public:
  blockChain() { chain.push_back(createGenesisBlock()); }
  void addBlock(int prevHash, std::string data) { chain.push_back(block(prevHash, data)); }
  block getLatestBlock() { return chain[chain.size() - 1]; }

};

#endif
