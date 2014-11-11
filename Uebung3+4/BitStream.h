#include "vector"
#include "string"
using namespace std;

class BitStream{


private:

public:
    BitStream();
    void saveBinaryFile(vector<int>* vec,string fileName);
    vector<int> readBinaryFile(string fileName);
    vector<bool> getBinary(vector<int>* vec);
    vector<int> getVector(string* bitset);
    ~BitStream();
};