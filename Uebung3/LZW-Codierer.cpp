#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>
#include <cmath>
#include <sstream>
#include <string>

using namespace std;

const int LENGTH_OF_MUSTER_ARRAY = 1024;

/**
* Start Index für die Muster
*/
const int START_INDEX_OF_MUSTER_ARRAY = 256;


/**
* Array mit den Mustern
*/
std::string muster[LENGTH_OF_MUSTER_ARRAY] = {};



/**
* Sucht ab dem startIndex das Muster für den angegebenen searchString
* gibt -1 zurück wenn kein Muster gefunden wurde
*/
int findMuster(std::string*searchString)
{
    for (int i = START_INDEX_OF_MUSTER_ARRAY; i <= (sizeof(muster)/sizeof(*muster)); i++){
        if(muster[i] == (*searchString)){
            return i;
        }
    }
    return -1;
}

/**
* Main funktion
*/
int main(int argc, char *argv[]) {
    fstream file("Test.txt");
    char currentChar;
    std::vector<char> vec;

    if (!file.eof() && !file.fail()) {
        file.seekg(0, std::ios_base::end);
        std::streampos fileSize = file.tellg();
        vec.resize(fileSize);
        file.seekg(0, std::ios_base::beg);
        file.read(&vec[0], fileSize);

    }


    std::ostringstream  result;
    int lengthOfText = vec.size();
    int indexOfLastMuster = START_INDEX_OF_MUSTER_ARRAY;

    for (int i = 0; i <= lengthOfText; i++) {
        std:string searchString = string(1,vec.at(i));
        int n = i;
        int musterInt = -1;
        int lastMuster = -1;
        do {
            n++;
            if (n == lengthOfText){
                musterInt = -1;
            }
            lastMuster = musterInt;
            musterInt = findMuster(&searchString);
            searchString = searchString + string(1,vec.at(n));
        }while (musterInt > 0);


        if (indexOfLastMuster == LENGTH_OF_MUSTER_ARRAY ){
            indexOfLastMuster = START_INDEX_OF_MUSTER_ARRAY;
        }
        muster[indexOfLastMuster+1] = searchString;
        indexOfLastMuster++;


        if(lastMuster > 0 ){
            result << lastMuster;
        }
        else{
            result << string(1,vec.at(i));
        }
    }


    cout << result.str();
}