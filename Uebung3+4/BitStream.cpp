#include <vector>
#include <fstream>
#include "BitStream.h"
#include "iostream"
#include "Sruct_bit.h"
#include "math.h"


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

void BitStream::saveBinaryFile(vector<unsigned int> *vec, string fileName) {
    ofstream binaryFile;
    vector<bool> binaryBool= this->getBinary(vec);
    //Save file
    binaryFile.open(fileName, ios::out|ios::binary);

    int byte = ceil((double)binaryBool.size()/(double)8);
    char charArray [byte];
    int i= 0;
    for(int f = 0; f< (sizeof(charArray)); f++){
        Sruct_bit bit;
        bit = *(Sruct_bit*)(&charArray[f]);

        /*
        * i < binaryBool.size() ? ist wegen dem letzten byte bzw. char das eventuell über die binaryBool.size hinaus ragt.
        * Dies tritt auf, wenn binaryBool.size() / 8 keinen graden Wert ergibt. Dann wird einfach aufgerundet, sodass alle Informationen gespeichert werden und die letzten bits unbenutzt gelassen werden.
        * */

        bit.b1 = i < binaryBool.size() ?  binaryBool.at(i++):false;
        bit.b2 = i < binaryBool.size() ?  binaryBool.at(i++):false;
        bit.b3 = i < binaryBool.size() ?  binaryBool.at(i++):false;
        bit.b4 = i < binaryBool.size() ?  binaryBool.at(i++):false;
        bit.b5 = i < binaryBool.size() ?  binaryBool.at(i++):false;
        bit.b6 = i < binaryBool.size() ?  binaryBool.at(i++):false;
        bit.b7 = i < binaryBool.size() ?  binaryBool.at(i++):false;
        bit.b8 = i < binaryBool.size() ?  binaryBool.at(i++):false;

        //Back cast
        charArray[f]  = *(char*)(&bit);

    }

    binaryFile.write((char*)&charArray, byte);
    binaryFile.close();


}

vector<unsigned int> BitStream::readBinaryFile(string fileName) {
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

            //Cast into sruct
            Sruct_bit bit;
            bit = *(Sruct_bit*)(&currentChar);

            //Schreiben in string
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
    vector<unsigned int> output;
    return output;

}

vector<bool> BitStream::getBinary(vector<unsigned int> *vec) {
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

vector<unsigned int> BitStream::getVector(string *str) {
    vector<unsigned int> output;
    for(int i = 0; i<(*str).size();i+=10){
        string bytes = (*str).substr(i,10);
        bitset<10> currentBitset(bytes);
        int result = (int)currentBitset.to_ulong();
        output.push_back(result);
    }
    return output;
}


#pragma clang diagnostic pop