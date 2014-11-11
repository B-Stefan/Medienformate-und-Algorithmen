
#include "LZWClass.h"
#include "iostream"
#include <sstream>
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
bool LZWClass::decodeMuster(int searchID, vector<unsigned int>* output) {

    if(this->muster.count(searchID)){
        *output = this->muster[searchID];
        return true;
    }
    return false;
}

bool LZWClass::encodeMuster(vector<unsigned int> searchMuster, int* outputMusterId) {

    for (std::map<int,vector<unsigned int>>::iterator it=this->muster.begin(); it!=this->muster.end(); ++it){
        if (it->second  == searchMuster){
            *outputMusterId= it->first;
            return true;
        }
    }
    return false;
}


void LZWClass::insertMuster(vector<unsigned int> newMuster) {
    if(this->indexOfNewMuster == LZWClass::MAX_INDEX_OF_MUSTER){
        this->indexOfNewMuster = this->START_INDEX_OF_MUSTER;
    }
    //Wenn für die muster ID schon ein Key exisitert dann diesen raus löschen, nur wnen überlauf
    vector<unsigned int> key;
    if(this->muster.count(this->indexOfNewMuster)){
        this->muster.erase(this->indexOfNewMuster);
    }
    this->muster[this->indexOfNewMuster++] = newMuster;
}



/*Public*/
vector<char> LZWClass::decode(vector<unsigned int> *vec) {
    this->setDefaults();
    vector<char> output;
    int i = 0;

    vector<unsigned int> newMuster;
    for(int val : *vec){
        if(val <= LZWClass::LAST_ASCI_CODE){
            //Wenn normales ASCI Zeichen
            unsigned int asciZeichen = val;
            newMuster.clear();
            newMuster.push_back(asciZeichen);
            output.push_back(asciZeichen);
        }
        else {
            //Wenn muster
            bool isMusterFound = this->decodeMuster(val, &newMuster);
            if (!isMusterFound){
                //cout << "ERROR: Muster für ID" << val << " wurde nicht gefunden. Dies sollte nicht vorkommen" << endl;
            }
            for( int val : newMuster){
                output.push_back(val);
            }
        }

        if((*vec).size()-1 == i){
            break;
        }
        //Neues Muster hinzufügen
        int nextInt = (*vec).at(i+1);
        if (nextInt <= LZWClass::LAST_ASCI_CODE){
            //Wenn normales ASCI Zeichen im nextInt
            unsigned int nextChar =  nextInt;
            newMuster.push_back(nextChar);
        }else {
            vector<unsigned int> nextIntMuster;
            this->decodeMuster(nextInt,&nextIntMuster);
            newMuster.push_back(nextIntMuster.at(0));
        }
        ////cout << "NeuesMuster: " << newMuster  << "(" << this->indexOfNewMuster << ")"<< endl;
        this->insertMuster(newMuster);
        i++;
    }
    return output;
}


vector<unsigned int> LZWClass::encode(vector<unsigned char> *vec) {
    this->setDefaults();
    unsigned long lengthOfText = (*vec).size();
    vector<unsigned int> output;
    for (unsigned long i = 0; i < (lengthOfText); ) {

        int currentChar = (*vec).at(i);
        //Muster Suchen
        bool isMusterFound = false;
        vector<unsigned int> currentMuster;
        currentMuster.push_back(currentChar);
        //cout << currentChar << "("<<(char) currentChar << ")" << endl;
        do{

            if (i == lengthOfText){
                break;
            }
            else if (i!=lengthOfText-1) {
                //Wenn es noch ein nächstes Zeichen gibt
                int nextChar = (*vec).at(i + 1);
                currentMuster.push_back(nextChar);
            }


            i++;

            int lastFoundMusterId;
            isMusterFound = this->encodeMuster(currentMuster, &lastFoundMusterId);

            if(!isMusterFound){
                //Kein Muster mehr gefunden
                this->insertMuster(currentMuster);

                vector<unsigned int> lastFoundMuster;
                copy ( currentMuster.begin(), currentMuster.end() - (currentMuster.size() > 1 ? 2:1) , std::back_inserter(lastFoundMuster) );

                //cout << "LastFoundMuster";
                for(int iLastMuster: lastFoundMuster){
                    //cout << iLastMuster << endl;
                }
                //cout << endl;

                //Zuletzt gefundendes Muster
                if(lastFoundMuster.size()==0){
                    //Wenn es kein Muster war sondern nur das Zeichen
                    int charToSaveInVector = currentMuster.at(0);
                    //cout << "Normaler ASCI Code Ausgabe:" << (char)charToSaveInVector <<endl;
                    output.push_back(charToSaveInVector);
                }
                else {
                    //Wenn es ein Muster war
                    output.push_back(lastFoundMusterId);
                    //cout << "Muster gefunden und hinzugefügt Ausgabe: " << lastFoundMusterId <<endl;
                    lastFoundMusterId = 0;
                }
            }

        }while(isMusterFound);

    }
    return output;

}