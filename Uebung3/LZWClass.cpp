
#include "string"
#include "LZWClass.h"
#include "iostream"
#include "map"
using  namespace std;
/**
* Konstruktor
*/
LZWClass::LZWClass() {
    this->setDefaults();

};
/**
* Dekonstruktor
*/


LZWClass::~LZWClass() {

}

/*Static*/
/**
Methdoen
*/
/*Private*/

void LZWClass::setDefaults() {
    this->indexOfNewMuster = LZWClass::START_INDEX_OF_MUSTER;
}
bool LZWClass::decodeMuster(int searchID, string* outputString) {

    for (std::map<string,int>::iterator it=this->muster.begin(); it!=this->muster.end(); ++it){
        if (it->second  == searchID){
            *outputString = it->first;
            return true;
        }
    }
    return false;
}

bool LZWClass::encodeMuster(string searchString, int* outputMusterId) {

    if(this->muster.count(searchString)){
        *outputMusterId = this->muster[searchString];
        return true;
    }
    return false;
}


void LZWClass::insertMuster(string newMusterString) {
    string tempString;
    if(this->indexOfNewMuster == LZWClass::MAX_INDEX_OF_MUSTER){
        this->indexOfNewMuster = this->START_INDEX_OF_MUSTER;
    }
    //Wenn für die muster ID schon ein Key exisitert dann diesen raus löschen, nur wnen überlauf
    string key;
    if(this->decodeMuster(this->indexOfNewMuster, &key)){
        this->muster.erase(key);
    }
    this->muster[newMusterString] = this->indexOfNewMuster++;

}



/*Public*/
vector<char> LZWClass::decode(vector<int> *vec) {
    this->setDefaults();
    vector<char> output;
    int i = 0;

    string newMuster;
    for(int val : *vec){
        if(val <= LZWClass::LAST_ASCI_CODE){
            //Wenn normales ASCI Zeichen
            char asciZeichen = (char)val;
            newMuster = string(1,asciZeichen);
            output.push_back(asciZeichen);
        }
        else {
            //Wenn muster
            bool isMusterFound = this->decodeMuster(val, &newMuster);
            if (!isMusterFound){
                cout << "ERROR: Muster für ID" << val << " wurde nicht gefunden. Dies sollte nicht vorkommen" << endl;
            }
            for(char val : newMuster){
                output.push_back(val);
            }
        }

        if((*vec).size()-1 == i){
            break;
        }
        //Neues Muster hinzufügen
        int nextInt = (*vec).at(i+1);
        if (nextInt <= LZWClass::LAST_ASCI_CODE){
            char nextChar = (char) nextInt;
            newMuster = newMuster+ string(1,nextChar);
        }else {
            string nextIntMusterString;
            this->decodeMuster(nextInt,&nextIntMusterString);
            newMuster = newMuster + nextIntMusterString[0];
        }
        //cout << "NeuesMuster: " << newMuster  << "(" << this->indexOfNewMuster << ")"<< endl;
        this->insertMuster(newMuster);
        i++;
    }
    return output;
}


vector<int> LZWClass::encode(vector<char> *vec) {
    this->setDefaults();
    int lengthOfText = (*vec).size();
    vector<int> output;
    for (int i = 0; i < (lengthOfText-1); ) {

        char currentChar = (*vec).at(i);
        //Muster Suchen
        bool isMusterFound = false;
        string currentMuster = string(1,currentChar);
        do{
            if (i == (lengthOfText-1)){
                break;
            }
            char nextChar = (*vec).at(i+1);
            currentMuster = currentMuster + string(1,nextChar);

            i++;

            int lastFoundMusterId;
            isMusterFound = this->encodeMuster(currentMuster, &lastFoundMusterId);
            if(!isMusterFound){
                //kein Muster mehr gefunden
                this->insertMuster(currentMuster);

                string lastFoundMuster = currentMuster.substr(0,currentMuster.size()-1);
                //Zuletzt gefundendes Muster
                if(lastFoundMuster.size()==1){
                    //Wenn es kein Muster war sondern nur das Zeichen
                    char charToSaveInVector = lastFoundMuster[0];
                    output.push_back(charToSaveInVector);
                }
                else {
                    //Wenn es ein Muster war
                    output.push_back(lastFoundMusterId);
                }
            }

        }while(isMusterFound);

    }
    return output;

}