#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
#include <sstream>
#include <map>

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


    map<string, int> muster;

    int lengthOfText = vec.size();
    int indexOfNewMuster = 256;
    cout << "lenghtOfText" << lengthOfText << endl;

    std::vector<int> output;
    for (int i = 0; i < (lengthOfText-1); ) {

        char currentChar = vec.at(i);
        //Muster Suchen
        bool isMusterFound = false;
        string currentMuster = string(1,currentChar);
        do{
            if (i == (lengthOfText-1)){
                break;
            }
            char nextChar = vec.at(i+1);
            currentMuster = currentMuster + string(1,nextChar);

            i++;

            if(muster.count(currentMuster)){
                //Wenn muster gefunden wurde
                isMusterFound = true;
                int foundMusterId = muster[currentMuster];
            }else {
                //Hinzufügen des nicht gefundenen musters
                isMusterFound = false;
                muster[currentMuster] = indexOfNewMuster++;

            }

            if(!isMusterFound){
                //Nie ein Muster gefunden
                string lastFoundMuster = currentMuster.substr(0,currentMuster.size()-1);
                if(lastFoundMuster.size()==1){
                    cout << lastFoundMuster << endl;
                    char charToSaveInVector = lastFoundMuster[0];
                    output.push_back(charToSaveInVector);

                }
                else {
                    int lastFoundMusterId = muster[lastFoundMuster];
                    cout << lastFoundMuster << " (" << lastFoundMusterId << ")" << endl;
                    output.push_back(lastFoundMusterId);
                }
            }


        }while(isMusterFound);





    }

    cout << "Ende: " << output.size();
    return 0;

}