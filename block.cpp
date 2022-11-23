#include <string>
class block
{
  private:
  
  unsigned long pHash; // Previous blocks hash
  unsigned long bHash; // This blocks hash
  std::string data; // Data in block
  
  unsigned long calculateHash()
  {
    std::string sHash = data.append(std::to_string(pHash));
    return std::hash<std::string>()(sHash);
  }
  
  public:
  
  block(int prevHash, std::string newData)
  {
    data = newData;
    pHash = prevHash;
    bHash = calculateHash();
  }
};
