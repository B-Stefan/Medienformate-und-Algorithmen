#include "map"
#include <vector>

using namespace std;
class LZWClass {
const
    int LAST_ASCI_CODE = 255;
    int START_INDEX_OF_MUSTER = LAST_ASCI_CODE +1 ;
    int MAX_INDEX_OF_MUSTER = 1023;
private:
    map<int,vector<int>> muster;
    int indexOfNewMuster;
    bool encodeMuster(vector<int> searchString,  int* outputMusterId);
    void insertMuster(vector<int> newMusterString);
    bool decodeMuster(int searchID, vector<int> *outputVector);
    void setDefaults();

public:
    LZWClass();
    vector<char> decode(vector<unsigned int> *vec);
    vector<unsigned int> encode(vector<unsigned char> *vec);
    ~LZWClass();

};