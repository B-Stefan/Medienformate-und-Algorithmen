#include <vector>
#include <fstream>
#include "BitStream.h"
#include "iostream"

using  namespace std;
/**
* Konstruktor
*/
BitStream::BitStream() {

};
/**
* Dekonstruktor
*/


BitStream::~BitStream() {

}


/**
* Methoden public
*/

void BitStream::saveBinaryFile(vector<int> *vec, string fileName) {
    ofstream binaryFile;
    string binaryString = this->getBinary(vec);

    //String into char Array
    char *binaryCharArray=new char[binaryString.size()+1];
    binaryCharArray[binaryString.size()]=0;
    memcpy(binaryCharArray,binaryString.c_str(),binaryString.size());

    //Save file
    binaryFile.open(fileName, ios::out|ios::binary);
    binaryFile.write(binaryCharArray, binaryString.size());
    binaryFile.close();
    delete binaryCharArray;
}

vector<int> BitStream::readBinaryFile(string fileName) {
    fstream file(fileName,  ios::in|ios::binary);

    //File einlsen
    if (!file.eof() && !file.fail()) {
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        std::string buffer(size, ' ');
        file.seekg(0);
        file.read(&buffer[0], size);
        return this->getVector(&buffer);
    }
    else {
        cout << "Fehler beim einlesen der Datei " << fileName << endl;
    }
    vector<int> output;
    return output;

}

string BitStream::getBinary(vector<int> *vec) {
    string output = "";
    for (int val: *vec){
        output += bitset<10>(val).to_string();
    }
    return output;
}

vector<int> BitStream::getVector(string *str) {
    vector<int> output;
    for(int i = 0; i<(*str).size();i+=10){
        string bytes = (*str).substr(i,10);
        bitset<10> currentBitset(bytes);
        int result = (int)currentBitset.to_ulong();
        output.push_back(result);
    }
    return output;
}

