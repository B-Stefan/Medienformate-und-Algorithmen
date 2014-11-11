#include "vector"
#include "string"
using namespace std;

class BitStream{


private:

public:
    BitStream();
    void saveBinaryFile(vector<unsigned int>* vec,string fileName);
    vector<int> readBinaryFile(string fileName);
    vector<bool> getBinary(vector<unsigned int>* vec);
    vector<int> getVector(string* bitset);
    ~BitStream();
};