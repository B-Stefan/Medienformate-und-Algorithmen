
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
    for(unsigned int val : *vec){
        if(val <= LZWClass::LAST_ASCI_CODE){
            //Wenn normales ASCI Zeichen

            newMuster.clear();
            newMuster.push_back(val);
            output.push_back((char)val);
        }
        else {
            //Wenn muster
            bool isMusterFound = this->decodeMuster(val, &newMuster);
            if (!isMusterFound){
                cout << "ERROR: Muster für ID" << val << " wurde nicht gefunden. Dies sollte nicht vorkommen" << endl;
            }
            for(unsigned int valOfMuster : newMuster){
                output.push_back((char)valOfMuster);
            }
        }

        //Wenn man am letzten Zeichen des Vectors angekommen ist. Schleife verlassen
        if((*vec).size()-1 == i){
            break;
        }


        //Neues Muster hinzufügen
        unsigned int nextInt = (*vec).at(i+1);
        if (nextInt <= LZWClass::LAST_ASCI_CODE){
            //Wenn normales ASCI Zeichen im nextInt
            newMuster.push_back(nextInt);
        }else {
            vector<unsigned int> nextIntMuster;
            this->decodeMuster(nextInt,&nextIntMuster);
            newMuster.push_back(nextIntMuster.at(0));
        }

        this->insertMuster(newMuster);
        i++;
    }
    return output;
}


vector<unsigned int> LZWClass::encode(vector<unsigned char> *vec) {
    this->setDefaults();
    unsigned long lengthOfText = (*vec).size();
    vector<unsigned int> output;

    //Für jedes zeichen im Text
    for (unsigned long i = 0; i < (lengthOfText); ) {

        int currentChar = (*vec).at(i);
        //Muster Suchen
        bool isMusterFound = false;
        vector<unsigned int> currentMuster;
        currentMuster.push_back(currentChar);


        // Suche das Muster ausgehend vom aktuellen Zeichen
        do{


            if (i!=lengthOfText-1) {
                //Wenn es noch ein nächstes Zeichen gibt
                int nextChar = (*vec).at(i + 1);
                currentMuster.push_back(nextChar);
            }

            //Erhöhen von i
            i++;

            int lastFoundMusterId;
            isMusterFound = this->encodeMuster(currentMuster, &lastFoundMusterId);

            if(!isMusterFound || i == lengthOfText){
                //Kein Muster mehr gefunden
                this->insertMuster(currentMuster);

                //Wenn kein Muster mehr gefunden wurde das zuletzt gefunden muster in lastFoundMuster kopieren
                vector<unsigned int> lastFoundMuster;
                copy ( currentMuster.begin(), currentMuster.end() - (currentMuster.size() > 1 ? 2:1) , std::back_inserter(lastFoundMuster) );


                //Zuletzt gefundendes Muster
                if(lastFoundMuster.size()==0){
                    //Wenn es kein Muster war sondern nur das Zeichen
                    unsigned int charToSaveInVector = currentMuster.at(0);
                    output.push_back(charToSaveInVector);
                }
                else {
                    //Wenn es ein Muster war
                    output.push_back((unsigned int)lastFoundMusterId);
                    lastFoundMusterId = 0;
                }
            }
            if (i == lengthOfText){
                break;
            }

        }while(isMusterFound);

    }
    return output;

}