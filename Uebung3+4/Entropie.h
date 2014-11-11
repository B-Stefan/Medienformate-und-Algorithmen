#include "vector"
using namespace std;

class Entropie{
const
    int LAST_ASCI_CODE = 255;

private:
    vector<unsigned char>* vec;

public:
    Entropie(vector<unsigned char> *vec);
    double getEntropie();
    double getBestFileSize();
    ~Entropie();
};