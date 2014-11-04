#include "map"
#include <vector>

using namespace std;
class LZWClass {
const
    int LAST_ASCI_CODE = 255;
    int START_INDEX_OF_MUSTER = LAST_ASCI_CODE +1 ;
    int MAX_INDEX_OF_MUSTER = 1024;
private:
    map<string,int> muster;
    int indexOfNewMuster;
    bool encodeMuster(string searchString,  int* outputMusterId);
    void insertMuster(string newMusterString);
    bool decodeMuster(int searchID, string *outputString);
    void setDefaults();

public:
    LZWClass();
    vector<char> decode(vector<int> *vec);
    vector<int> encode(vector<char> *vec);
    ~LZWClass();

};