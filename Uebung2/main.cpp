#include <iostream>
#include "Transform.h"
#include "math.h"
#include "array"
#define _USE_MATH_DEFINES


using namespace std;




int main() {
    cout << "Hello, World!" << endl;

    long double alpha = M_PI/2;
    int tx = 3;
    int ty = 4;
    Transform t(alpha,tx,ty);


    double dX = 3;
    double dY = 4;

    double translateVars[2][2][2] = {
            {
                    {3,4},//translate to (x,y)
                    {7,6},//expected result from Matlab for apply

            },
            {
                    {3,4},//translate to (x,y)
                    {7,6},//expected result from Matlab for apply

            }

    };

    int l = sizeof(translateVars);
    while (l!= 0){
        l--;
        std::array<double ,2> ergApply = t.Apply(&translateVars[l][0][0], &translateVars[l][0][1]);
        std::array<double ,2> ergApplyInverse = t.ApplyInverse(&translateVars[l][1][0], &translateVars[l][1][1]);


        /**
        * Apply Inverse Test
        */
        cout << "apply" << endl;
        if (ergApply[0] !=  translateVars[l][1][1] || ergApply[1] !=   translateVars[l][1][2]
                ){
            cout << l << ". Fehler Apply: \t ";
            cout << "expeceted: (" <<  translateVars[l][1][1] << "," <<  translateVars[l][1][2] <<") \t" ;
            cout << "actual:(" << ergApply[0] << "," << ergApply[1] <<")" << endl;
        }
        else
            cout << l <<". OK";

        cout << "applyInverse" << endl;
    }

    /***
    *  Test Fall 1
    >> a = pi/2;
    >> R = [cos(a), -sin(a);  sin(a),cos(a),];
    >> R = [cos(a), -sin(a);  sin(a),cos(a),];
    >> p = [3;4];
    >> t = [3;4];
    >> R*p+t
    */

    return 0;




}