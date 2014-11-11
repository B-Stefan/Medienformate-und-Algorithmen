
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "LZWClass.h"
#include "Entropie.h"
#include "BitStream.h"

using namespace std;

void executeFile(string fileName, bool debug) {
    fstream file(fileName, ios::binary | ios::in);
    std::vector<unsigned char> vec;

    std::size_t found = fileName.find(".ppm");
    bool isBmp = found != std::string::npos;
    if (!file.eof() && !file.fail()) {
        file.seekg(0, std::ios_base::end);
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios_base::beg);


        if (isBmp) {
            unsigned char c;
            while (file.read((char *) &c, 1)) {
                vec.push_back(c);
            }

        } else {
            vec.resize(fileSize);
            file.read((char *) &vec[0], fileSize);
        }


        file.close();


    }

    /*
    for(char c : vec){
        cout << (unsigned int)c << ",";
    }
*/



    cout << endl << endl << endl;
    cout << "========Datei: " << fileName << "=======" << endl;


    if (!isBmp) {
        Entropie entr(&vec);
        cout << "Entropie für die Datei: \t "<< entr.getEntropie() << "  Bits / Zeichen" << endl;
        cout << "Otimale länge der Datei :\t " << entr.getBestFileSize()  << " Bytes"<<endl;
        cout << endl << endl;
    }

    cout << "====LZW===" << endl;
    LZWClass lzw;
    vector<unsigned int> outInts = lzw.encode(&vec);

    cout << "Original-Länge: \t" << vec.size() << " Zeichen (" << vec.size() << " Bytes)" << endl;

    if (debug) {
        int i = 0;
        for (int val : vec) {
            cout << "\t" << i << ". Original: " << (char) val << "(" << val << ")" << endl;
            i++;
        }
    }

    cout << "Encodieren-Länge: \t" << outInts.size() << " Zeichen (" << (double) outInts.size() * (double) 10 / (double) 8 << " Bytes)" << endl;
    if (debug) {
        int i = 0;
        for (int val : outInts) {
            cout << "\t" << i << ". Encode: " << (char) val << "(" << val << ")" << endl;
            i++;
        }

    }

    vector<char> outChar = lzw.decode(&outInts);


    cout << "Decodeieren-Länge: \t" << outChar.size() << " Zeichen" << endl;

    int i = 0;
    for (char val : vec) {


        if (i < outChar.size()) {
            if(debug){
                char decodeErg = outChar.at(i);
                cout << "\t" << i << ". " << "Decode:" << decodeErg << "(" << (unsigned int) decodeErg << ")=Original:" << val <<endl;
                if (decodeErg != val) {
                    cout << "\t\tFEHLER!!!";
                }
            }
        } else{
            cout << "\t" << i << ". Fehler: " << " wurde nicht in der ausgabe der LZW decodierung gefunden es fehlte: " << (unsigned int)val << "(" << val << ")" << endl;
        }

        i++;
    }






    double compression = 1-(double)outInts.size()/(double)vec.size();

    cout << "Compression: \t\t" << compression*100<< "%" << endl;

    BitStream b;
    vector<bool> binaryBool= b.getBinary(&outInts);


    cout << endl << endl;
    cout << "====Bitstream-Speicherung==== " << endl;
    if(debug){
        cout << endl <<"Binärer String: \t";
        for (bool b: binaryBool){
            cout <<b;
        }
        cout <<endl;
    }


    //Binär Datei speichern
    string fileNameBinary = fileName+".bin";
    cout << "Binäre save: \t" << outInts.size() << " Zeichen"<< endl;
    cout << "Binäre Datei save: \t" << fileNameBinary << endl;

    b.saveBinaryFile(&outInts, fileNameBinary);

    cout << "Binäre Datei load: \t" << fileNameBinary << endl;
    vector<unsigned int> binaryResult = b.readBinaryFile(fileNameBinary);

    cout << "Binäre load: \t" << binaryResult.size() << " Zeichen"<< endl;

    i = 0;
    for (int val: binaryResult){
        if(i<outInts.size()){
            int decodeErg = outInts.at(i);

            if(val!=decodeErg){
                cout << "\t" << i <<". Fehler Erwartet: " << decodeErg << " Bekommen: " << val << endl;
            }else if (debug){
                cout << "\t" << i << ". BinarDecode: " << decodeErg << " Original: " << val << endl;
            }
            i++;
        }

    }




}

/**
* Main funktion
*/
int main(int argc, char *argv[]) {


    executeFile("Text_Short_LZWLW78.txt", true);
    executeFile("Test_Long_Lorem.txt", false);
    executeFile("Test_lena.ppm", false);

    return 0;
}