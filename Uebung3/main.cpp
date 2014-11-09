#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <map>
#include "LZWClass.h"
#include "Entropie.h"

using namespace std;

/**
* Main funktion
*/
int main(int argc, char *argv[]) {

    fstream file("Test_LZW_Vorlesung.txt");
    std::vector<char> vec;

    if (!file.eof() && !file.fail()) {
        file.seekg(0, std::ios_base::end);
        std::streampos fileSize = file.tellg();
        vec.resize(fileSize);
        file.seekg(0, std::ios_base::beg);
        file.read(&vec[0], fileSize);

    }


    Entropie entr(&vec);
    double entrophieOfText = entr.getEntropie();
    cout << " Entropie für den Text: "<<entrophieOfText << endl;
    cout << "Otimale länge des Textes in Byte: " << entr.getBestFileSize() <<endl;
    LZWClass lzw;
    vector<int> out = lzw.encode(&vec);


    cout << "Encodieren des Textes"<<endl;
    for(int val : out){
        cout <<"encode: " << val << endl;
    }

    vector<char> outChar = lzw.decode(&out);


    cout << "Decodeieren des Textes" << endl;
    int i = 0;
    for(char val : outChar){
        char org = vec.at(i);
        cout << "decode:" << val  << " original:" << org;
        if (org != val){
            cout << "FEHLER!!!";
        }
        cout << endl;
        i++;
    }
    return 0;

}