#include "Test.h"
#include "array"
#include <iostream>


using namespace std;
Test::Test(double  testVars[2][2][2], Transform* transform){
    int l = sizeof(this->testVars);
    while (l!= 0){
        l--;
        array<double ,2> ergApply = this->transform->Apply(&this->testVars[l][0][0], &this->testVars[l][0][1]);
        array<double ,2> ergApplyInverse = this->transform->ApplyInverse(&this->testVars[l][1][0], &this->testVars[l][1][1]);

        double * expectedVars[] = testVars[l][1];

        /**
        * Apply Inverse Test
        */
        cout << "apply" << endl;
        if (ergApply[0] != expectedVars[1] || ergApply[1] !=  expectedVars[2]
                ){
            cout << l << ". Fehler Apply: \t ";
            cout << "expeceted: (" << expectedVars[1] << "," << expectedVars[2] <<") \t" ;
            cout << "actual:(" << ergApply[0] << "," << ergApply[1] <<")" << endl;
        }
        else
            cout << l <<". OK";

        cout << "applyInverse" << endl;
    }
}
void Test::run() {
    cout << "apply" << endl;
    int l = sizeof(this->testVars);
    while (l!= 0){
        l--;
        array<double ,2> ergApply = this->transform->Apply(&this->testVars[l][0][0], &this->testVars[l][0][1]);
        array<double ,2> ergApplyInverse = this->transform->ApplyInverse(&this->testVars[l][1][0], &this->testVars[l][1][1]);

        double expectedVars[2] = this->testVars[l][1];

        /**
        * Apply Inverse Test
        */
        if (ergApply[0] != expectedVars[1] || ergApply[1] !=  expectedVars[2]
                ){
            cout << l << ". Fehler Apply: \t ";
            cout << "expeceted: (" << expectedVars[1] << "," << expectedVars[2] <<") \t" ;
            cout << "actual:(" << ergApply[0] << "," << ergApply[1] <<")" << endl;
        }
        else
            cout << l <<". OK";

    }
}
void Test::runApplyInverse() {
    cout << "applyInverse" << endl;
}
Test::~Test(){

};