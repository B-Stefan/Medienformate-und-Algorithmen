#include "array"
#include "Transform.h"

class Test {
/**
* Private part
*/
private:
    /*
    @example
        {
            {alpha,x,y} // Ausgangswert
            {alpha,x,y} // Erwartertert Wert (Matlab) s
        },...
     */
    double  testVars [2][2][2];
    Transform *transform;
/**
* Public part
*/
public:
    Test(double [2][2][2], Transform *);

    ~Test();

    void run();


};

