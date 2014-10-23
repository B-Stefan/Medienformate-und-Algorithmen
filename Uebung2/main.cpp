#include <iostream>
#include "Transform.h"
#include "math.h"
#include "array"
#define _USE_MATH_DEFINES


using namespace std;




int main() {
    cout << "Hello, World!" << endl;

    long double alpha = M_PI/2;
    double tx = 3;
    double ty = 4;
    Transform t(alpha,tx,ty);

    double translateVars[4][2][2] = {
            {
                    {4,7},//translate to (x,y)
                    {-4,8},//expected result from Matlab for apply

            },
            {
                    {3,4},//translate to (x,y)
                    {-1,7},//expected result from Matlab for apply

            },
            {
                    {0.5,1.5},//translate to (x,y)
                    {1.5,4.5},//expected result from Matlab for apply

            },
            {
                    {5.0/6.0,1.0/3.0},//translate to (x,y)
                    {3.0+1.0/(-3.0),5.0+1.0/(-6.0)},//expected result from Matlab for apply

            }

    };

    cout.precision(100); // Nachkommerstellen setzten
    int l = sizeof(translateVars)/sizeof(translateVars[0]); //size of 3d array
    while (l!= 0){
        l--;
        std::array<double ,2> ergApply = t.Apply(&translateVars[l][0][0], &translateVars[l][0][1]);
        std::array<double ,2> ergApplyInverse = t.ApplyInverse(&translateVars[l][1][0], &translateVars[l][1][1]);


        /**
        * Apply Inverse Test
        */
        if (ergApply[0] !=  translateVars[l][1][0] || ergApply[1] !=   translateVars[l][1][1]
                ){

            float ausgangswertX = (float) translateVars[l][1][0];
            float ausgangswertY = (float) translateVars[l][1][1];

            float ergX = (float) ergApply[0];
            float ergY = (float) ergApply[1];

            cout << l << ". Fehler Apply: \t\t\t";
            cout << "expeceted: (" <<   ausgangswertX << "," <<  ausgangswertY <<") \t" ;
            cout << "actual:(" << ergX << "," <<  ergY <<")" << endl;
        }
        else
            cout << l <<". Apply OK" << endl;


        /**
        * Apply Inverse
        */
        /**
        * Apply Inverse Test
        */
        if (ergApplyInverse[0] !=  translateVars[l][0][0] || ergApplyInverse[1] !=   translateVars[l][0][1]
                ){
            std::cout.unsetf ( std::ios::floatfield );
            cout.precision(15);
            float ergX = (float) ergApplyInverse[0];
            float ergY = (float) ergApplyInverse[1];

            float ausgangswertX = (float) translateVars[l][0][0];
            float ausgangswertY = (float) translateVars[l][0][1];

            cout << l << ". Fehler Apply-Inverse: \t ";
            cout << "expeceted: (" <<  ausgangswertX << "," <<   ausgangswertY <<") \t" ;
            cout << "actual:(" << ergX << "," <<  ergY <<")" << endl;
        }
        else
            cout << l <<". Apply OK" << endl;


    }

    /***
    *  Test Fall 1
    >> a = pi/2;
    >> R = [cos(a), -sin(a);  sin(a),cos(a),];
    >> p = [3;4];
    >> t = [3;4];
    >> R*p+t
    */

    return 0;




}