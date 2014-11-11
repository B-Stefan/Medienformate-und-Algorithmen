
#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>

#include "LZWClass.h"
#include "Entropie.h"
#include "BitStream.h"

using namespace std;

void executeFile(string fileName, bool debug){
    fstream file(fileName,ios::binary|ios::in);
    std::vector<char> vec;

    if (!file.eof() && !file.fail()) {
        file.seekg(0, std::ios_base::end);
        std::streampos fileSize = file.tellg();
        file.seekg(0, std::ios_base::beg);


        std::size_t found=fileName.find(".ppm");
        if(found!=std::string::npos){
            char c;
            while( file.read(&c, 1) ){
                vec.push_back(c);
            }

        }else {
            vec.resize(fileSize);
            file.read(&vec[0], fileSize);
        }


        file.close();


    }
    for(char c : vec){
        cout << ( int)c << ",";
    }

    Entropie entr(&vec);

    cout << endl << endl <<endl;
    cout << "========Datei: "  << fileName <<"=======" << endl;
    cout << "Entropie für die Datei: \t "<< entr.getEntropie() << "  Bits / Zeichen" << endl;
    cout << "Otimale länge der Datei :\t " << entr.getBestFileSize()  << " Bytes"<<endl;
    cout << endl << endl;
    cout << "====LZW===" << endl;
    LZWClass lzw;
    vector<int> outInts = lzw.encode(&vec);

    cout << "Original-Länge: \t" << vec.size() <<" Zeichen (" << vec.size() << " Bytes)"<<endl;

    if(debug){
        int i = 0;
        for(int val : vec){
            cout<<"\t" << i  <<". Original: "<< (char)val  <<"(" << val <<")"<< endl ;
            i++;
        }
    }

    cout << "Encodieren-Länge: \t"<<outInts.size()<<" Zeichen ("<< (double)outInts.size()*(double)10/(double)8 << " Bytes)"  <<endl;
    if(debug){
        int i = 0;
        for(int val : outInts){
            cout<<"\t" << i  <<". Encode: "<< (char)val  <<"(" << val <<")"<< endl ;
            i++;
        }

    }

    vector<char> outChar = lzw.decode(&outInts);


    cout << "Decodeieren-Länge: \t" << outChar.size()<<" Zeichen" << endl;
    if(debug){
        int i = 0;
        for(char val : vec){
            cout<<"\t" << i << ". ";

            if(i < outChar.size()){
                char decodeErg = outChar.at(i);
                cout << "Decode:" << decodeErg << "("<< (int)decodeErg  << ")=Original:" << val;
                if (decodeErg != val ){
                    cout << "FEHLER!!!";
                }
            }else {
                cout << "Fehler: " << i << " wurde nicht in der ausgabe der LZW decodierung gefunden es fehlte: " << val << "(" << (char) val << ")";
            }

            cout << endl;
            i++;
        }
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
    vector<int> binaryResult = b.readBinaryFile(fileNameBinary);

    cout << "Binäre load: \t" << binaryResult.size() << " Zeichen"<< endl;

        int i = 0;
        for (int val: binaryResult){
            int decodeErg = outInts.at(i);

            if(val!=decodeErg){
                cout << "\t" << i <<". Fehler Erwartet: " << decodeErg << " Bekommen: " << val << endl;
            }else if (debug){
                cout << "\t" << i << ". BinarDecode: " << decodeErg << " Original: " << val << endl;
            }
            i++;
        }




}

/**
* Main funktion
*/
int main(int argc, char *argv[]) {


    executeFile("Text_Short_LZWLW78.txt", true);
    executeFile("Test_Long_Lorem.txt", false);
    //executeFile("lena.ppm", false);

    return 0;
}