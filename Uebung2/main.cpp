#include <iostream>
#include <Foundation/Foundation.h>
#include "Transform.h"
#include "math.h"
#include "array"
#define _USE_MATH_DEFINES

#include "Test.h"

using namespace std;




int main() {
    cout << "Hello, World!" << endl;

    long double alpha = M_PI/2;
    int tx = 3;
    int ty = 4;
    Transform t(alpha,tx,ty);


    double dX = 3;
    double dY = 4;
    /**
    * Apply
    */
    std::array< double, 2 > applyErg = t.Apply(&dX,&dY);

    cout << "Neue Werte für apply" << endl;
    cout <<  "X:\t" << applyErg[0] << endl;
    cout <<  "Y:\t" << applyErg[1]  << endl;

    /**
    * ApplyInverse
    */
    std::array< double, 2 > applyInverseErg = t.ApplyInverse(&dX,&dY);

    cout << "Neue Werte für applyInverse" << endl;
    cout <<  "X:\t" << applyInverseErg[0] << endl;
    cout <<  "Y:\t" << applyInverseErg[1]  << endl;



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

    /*double inverseTranslateVars[][2][3] = {
            {
                    {M_PI/2,3,4},//translate inverse to (x,y)
                    {} //expected result from Matlab
            },

    };*/

    Test test1 =  Test(translateVars,&t);


    test1.run();

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