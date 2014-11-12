#include <vector>
#include <math.h>
#include "Entropie.h"
#include "iostream"

using  namespace std;
/**
* Konstruktor
*/
Entropie::Entropie(vector<unsigned char>* vec) {
    this->vec = vec;

};
/**
* Dekonstruktor
*/


Entropie::~Entropie() {

}


/**
* Methoden public
*/

/**
* Gibt die optimale länge in byte zurück
*/
double Entropie::getBestFileSize() {

    double lengthOfText = (*this->vec).size();
    return this->getEntropie()* lengthOfText/8;
}

double Entropie::getEntropie() {
    double zeichen[256] = {};
    unsigned long lengthOfText = (*this->vec).size();
    // Zähler für jedes ASCI Zeichen, sodass pro Zeichen die Anzahl des vorkommens im Text hinterlegt wird.
    for (int i : (*this->vec)) {
        zeichen[i] = zeichen[i] + 1;
    }


    //Berechnen der Entropie nach Formel in der VL
    double h = 0;
    for (double val : zeichen) {
        if (val != 0) {
            double pa = val / lengthOfText;
            double xa = log2(1.0 / pa);
            h = h + xa * pa;
            //cout << "Debug: Val:" << val << " - xa: " << xa << endl;
        }
    }

    return h;
}
