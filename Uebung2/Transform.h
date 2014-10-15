/**
* Übung 2
* Aufgabenblatt: https://www.aulis.hs-bremen.de/goto.php?target=file_480441_download&client_id=hsbremen
*
*/
#include "array"

class Transform {
private:
    double tx;
    double ty;
    long double alpha;
public:
    Transform(long double alpha, double tx, double ty);

    ~Transform();

    std::array< double, 2 > &  Apply(double *x, double *y);

    std::array< double, 2 > &  ApplyInverse(double *x, double *y);
};