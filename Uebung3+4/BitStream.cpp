#include <vector>
#include <fstream>
#include "BitStream.h"
#include "iostream"
#include "Sruct_bit.h"

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
    vector<bool> binaryBool= this->getBinary(vec);
    //Save file
    binaryFile.open(fileName, ios::out|ios::binary);

    char charArray [binaryBool.size()/8];
    int i= 0;
    for(int f = 0; f< (sizeof(charArray)); f++){
        Sruct_bit bit;
        bit = *(Sruct_bit*)(&charArray[f]);
        bit.b1 = binaryBool.at(i++);
        bit.b2 = binaryBool.at(i++);
        bit.b3 = binaryBool.at(i++);
        bit.b4 = binaryBool.at(i++);
        bit.b5 = binaryBool.at(i++);
        bit.b6 = binaryBool.at(i++);
        bit.b7 = binaryBool.at(i++);
        bit.b8 = binaryBool.at(i++);
        charArray[f]  = *(char*)(&bit);

    }

    binaryFile.write((char*)&charArray, i/8);
    binaryFile.close();


}

vector<int> BitStream::readBinaryFile(string fileName) {
    fstream file(fileName,  ios::in|ios::binary);

    //File einlsen
    if (!file.eof() && !file.fail()) {
        file.seekg(0, std::ios::end);
        size_t size = file.tellg();
        char memblock[size];
        file.seekg(0);
        file.read(memblock, size);
        file.close();
        string resultStr = "";
        for(char currentChar : memblock){
            Sruct_bit bit;
            bit = *(Sruct_bit*)(&currentChar);

            resultStr +=bit.b1? "1":"0";
            resultStr +=bit.b2? "1":"0";
            resultStr +=bit.b3? "1":"0";
            resultStr +=bit.b4? "1":"0";
            resultStr +=bit.b5? "1":"0";
            resultStr +=bit.b6? "1":"0";
            resultStr +=bit.b7? "1":"0";
            resultStr +=bit.b8? "1":"0";

        }
        return  this->getVector(&resultStr);

    }
    else {
        cout << "Fehler beim einlesen der Datei " << fileName << endl;
    }
    vector<int> output;
    return output;

}

vector<bool> BitStream::getBinary(vector<int> *vec) {
    vector<bool> output;
    for (int val: *vec){
        string valStr;
        valStr =  bitset<10>(val).to_string();
        for(char c : valStr){
            if(c=='1'){
                output.push_back(true);
            }else {
                output.push_back(false);
            }
        }
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
