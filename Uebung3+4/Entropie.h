#include "vector"
using namespace std;

class Entropie{
const
    int LAST_ASCI_CODE = 255;

private:
    vector<char>* vec;

public:
    Entropie(vector<char> *vec);
    double getEntropie();
    double getBestFileSize();
    ~Entropie();
};