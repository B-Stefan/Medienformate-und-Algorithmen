#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>

using namespace std;

int main(int argc, char * argv[]) {
    fstream file("Text.txt");
    char currentChar;
    std::vector<char> vec;

    if (!file.eof() && !file.fail()) {
        file.seekg(0, std::ios_base::end);
        std::streampos fileSize = file.tellg();
        vec.resize(fileSize);
        file.seekg(0, std::ios_base::beg);
        file.read(&vec[0], fileSize);
    }


    double zeichen[256] = {};
    unsigned long lengthOfText = vec.size();
    for (int i : vec){
        zeichen[i] = zeichen[i]+1;
    }
    // get character from file and store in array c[]

    double h = 0;
    for (double val : zeichen){
        if(val != 0 ){
             double pa = val/lengthOfText;
             double xa = log2(1.0/pa);
             h = h + xa * pa;
             cout << "Debug: Val:" << val << " - xa: " << xa  << endl;
        }
    }

    cout<< "Entropie für den Text: " << h << endl;

    return 0;
}