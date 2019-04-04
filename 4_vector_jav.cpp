#include <iostream>
#include "vector2.h"

int main(int, char**) {


    //lambda for testing vector
    auto testv = [](auto v1, auto vref, auto str){   
        if(abs(v1.x - vref.x) > 1e-10 || abs(v1.y - vref.y) > 1e-10 ){
        std::cout << str;
        std::exit(-1);   
        }
    };

    //test

    // +=
    {
    Vector2d<double> v1{1.0, 3.0}, v2{5.0, 7.0};
    v1 += v2;
    Vector2d<double> vref{6.0, 10.0};
    testv(v1, vref, "Error in vector2.h: += operator \n");
 
    } 

    // -=
    {
    Vector2d<double> v1{1.0, 3.0}, v2{5.0, 7.0};
    Vector2d<double> vref{-4.0, -4.0};
    v1 -= v2;
    testv(v1, vref, "Error in vector2.h: -= operator \n");
    }
    
    // *=
    {
    Vector2d<double> v1{1.0, 3.0};
    double lambda = 9.0;
    Vector2d<double> vref{9.0, 27.0};
    v1 *= lambda;
    testv(v1, vref, "Error in vector2.h: *= operator \n");
 
    }

    // /=
    {
    Vector2d<double> v1{1.0, 3.0};
    double lambda = 9.0;
    Vector2d<double> vref{1.0/9.0, 3.0/9.0};
    v1 /= lambda;
    testv(v1, vref, "Error in vector2.h: /= operator \n");

    }

    // + operator
    {
    Vector2d<double> v1{1.0, 3.0}, v2{5.0, 7.0};
    Vector2d<double> v3 = v1+v2;
    Vector2d<double> vref{6.0, 10.0};
    testv(v3, vref, "Error in vector2.h: + operator \n");
    }
    
    // - operator
    {
    Vector2d<double> v1{1.0, 3.0}, v2{5.0, 7.0};
    Vector2d<double> v3 = v1-v2;
    Vector2d<double> vref{-4.0, -4.0};
    testv(v3, vref, "Error in vector2.h: + operator \n");
    }

    // * operators
    {
    Vector2d<double> v1{1.0, 3.0};
    double lambda = 4.5;
    Vector2d<double> v2 = v1*lambda;
    Vector2d<double> v3 = lambda*v1;
    Vector2d<double> vref{4.5, 13.5};
    testv(v2, vref, "Error in vector2.h: * operator (right) \n");
    testv(v3, vref, "Error in vector2.h: * operator (left)  \n");
    }

    // / operator
    {
    Vector2d<double> v1{1.0, 3.0};
    double lambda = 2.0;
    Vector2d<double> v2 = v1/lambda;
    Vector2d<double> vref{0.5, 1.5};
    testv(v2, vref, "Error in vector2.h: / operator (right) \n");
    }

    //

    //functions
    //scalar product
    {
    Vector2d<double> v1{1.0, 3.0}, v2{5.0, 7.0};
    double ref = 5.0 + 21.0;
    if (abs(dot(v1,v2) - ref) > 1e-10){
        std::cout << "Error in vector2.h: dot() \n";
        std::exit(-1);
        }
    }
    
    //length
    {
    Vector2d<double> v1{1.0, 3.0};
    double ref =1.0 + 9.0 ; 
    if (abs(sqlength(v1) - ref) > 1e-10){
        std::cout << "Error in vector2.h: sqlength() \n";
        std::exit(-1);
        }

    }

    {
    Vector2d<double> v1{1.0, 3.0};
    double ref =std::sqrt(1.0 + 9.0) ; 
    if (abs(length(v1) - ref) > 1e-10){
        std::cout << "Error in vector2.h: length() \n";
        std::exit(-1);
        }
    }

    //normalization
    {
    Vector2d<double> v2{5.0, 7.0};
    double L = length(v2);
    Vector2d<double> vref ={5.0/L, 7.0/L};
    Vector2d<double> Nv2 = normalize(v2);
    testv(Nv2, vref, "Error in vector2.h: normalize() \n");    
    }

    //rotation
    {
    Vector2d<double> v2{5.0, 7.0};
    double phi = 1.0534;
    double cphi = std::cos(phi);
    double sphi = std::sin(phi);
    double x = v2.x*cphi - v2.y*sphi;
    double y = v2.x*sphi + v2.y*cphi;
    Vector2d<double> vref{x,y};
    Vector2d<double> Rv2 = rotate(v2, phi);
    testv(Rv2, vref, "Error in vector2.h: rotate() \n");

    }


    std::cout << "Tests were successful!\n";
    return 0;





}
