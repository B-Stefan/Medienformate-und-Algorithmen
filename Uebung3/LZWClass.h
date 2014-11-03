
#include <map>
#include <vector>

class LZWCLass {
private:
    map muster;
    int indexOfNewMuster;
    int encodeMuster(string searchTerm);
    string decodeMuster(int searchID);

public:
    LZWCLass ();
    void decode (vector<int> vec);
    void encode (vector<char> vec);
    ~LZWCLass();

};