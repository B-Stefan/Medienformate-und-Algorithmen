#include "Transform.h"
#include "math.h"
#include "iostream"
using  namespace std;
/**
* Konstruktor
*/
Transform::Transform(long double alpha, double tx, double ty) {
    this->alpha = alpha;
    this->tx = tx;
    this->ty = ty;

};

/**
* Dekonstruktor
*/

Transform::~Transform() {

}
array< double , 2> & Transform::Apply(double *x, double *y) {

    double R[] =    {   cos(this->alpha),-sin(this->alpha),
                        sin(this->alpha),cos(this->alpha)
                    };

    double newX = (R[0]**x + R[1]**y) + this->tx;
    double newY = (R[2]**x + R[3]**y) + this->ty;

    std::array<double , 2> erg{ {newX,newY} };
    return erg;
}

array< double , 2> & Transform::ApplyInverse(double *x, double *y) {

    double R[] =    {   cos(this->alpha),sin(this->alpha),
                        -sin(this->alpha),cos(this->alpha)
                    };
    int localX = (*x-this->tx);
    int localY = (*y-this->ty);

    double newX = (R[0]*localX + R[1]*localY);
    double newY = (R[2]*localX + R[3]*localY);

    std::array<double , 2> erg{ {newX,newY} };
    return erg;
}

