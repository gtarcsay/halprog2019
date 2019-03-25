#include <iostream>
#include <cmath>
#include "vector2.h"

int main(int, char**) {

    Vector2d<double> v1{1.0, 3.0}, v2{5.0, 7.0};
    double lambda = 3.0;
    double phi = 3.14/2;
    bool error = false;
    
    //test
    // +=
    v1 += v2;
    Vector2d<double> vres_add{1.0+5.0, 3.0+7.0};
    if(abs(v1.x - vres_add.x) > 1e-10 || abs(v1.y - vres_add.y) > 1e-10 ){
        error = true;
        std::cout << "+= operator is failed!\n";
    }

    // -=
    v1 -= v2;
    Vector2d<double> vres_subdiv{1.0, 3.0};
    if(abs(v1.x - vres_subdiv.x) > 1e-10 || abs(v1.y - vres_subdiv.y) > 1e-10 ){
        error = true;
        std::cout << "-= operator is failed!\n";
    }

    // *=
    v1 *= lambda;
    Vector2d<double> vres_mul{1.0*3.0, 3.0*3.0};

     if(abs(v1.x - vres_mul.x) > 1e-10 || abs(v1.y - vres_mul.y) > 1e-10 ){
        error = true;
        std::cout << "*= operator is failed!\n";
        std::cout << v1.x << "\t" << v1.y << std::endl;
    }

    // /=
    v1 /= lambda;
    if(abs(v1.x - vres_subdiv.x) > 1e-10 || abs(v1.y - vres_subdiv.y) > 1e-10 ){
        error = true;
        std::cout << "/= operator is failed!\n";
    }

    Vector2d<double> v3{11.0, 13.0}, v4{17.0, 19.0};

    //add
    Vector2d<double> v5 = v3+v4;
    Vector2d<double> vres_func1{11.0+17.0, 13.0 + 19.0};

    if(abs(v5.x - vres_func1.x) > 1e-10 || abs(v5.y - vres_func1.y) > 1e-10 ){
        error = true;
        std::cout << "Addition is failed!\n";
    }
    
    //sub
    Vector2d<double> v6 = v3-v4;
    Vector2d<double> vres_func2{11.0-17.0, 13.0 - 19.0};

    if(abs(v6.x - vres_func2.x) > 1e-10 || abs(v6.y - vres_func2.y) > 1e-10 ){
    error = true;
    std::cout << "Subtraction is failed!\n";
    }

    //functions
    //scalar product
    double dot_res = v1.x*v2.x+v1.y+v2.y;
    if (abs(dot(v1,v2) - dot_res) > 1e-10){
        error = true;
        std::cout << "Dot is failed!\n";
    }
    
    //length
    double L2_res = v1.x*v1.x+v1.y*v1.y; 

     if (abs(sqlength(v1) - L2_res) > 1e-10){
        error = true;
        std::cout << "Sqlength is failed!\n";
    }

    if (abs(length(v1) - std::sqrt(L2_res)) > 1e-10){
        error = true;
        std::cout << "Length is failed!\n";
    }

    //normalization
    double L_2 = length(v2);
    Vector2d<double> vres_norm{5.0/L_2, 7.0/L_2};
    Vector2d<double> Nv2 = normalize(v2);

    if(abs(Nv2.x - vres_norm.x) > 1e-10 || abs(Nv2.y - vres_norm.y) > 1e-10){
        error = true;
        std::cout << "Normalize is failed!\n";

    }
    //rotation
    Vector2d<double> vres_rot{v2.x*std::cos(phi) - v2.y*std::sin(phi), v2.x*std::sin(phi) + v2.y*std::cos(phi)};
    Vector2d<double> Rv2 = rotate(v2, phi);

    if(abs(Rv2.x - vres_rot.x) > 1e-10 || abs(Rv2.y - vres_rot.y) > 1e-10){
        error = true;
        std::cout << "Rotation is failed!\n";
    }


if(error == false)
{
    std::cout << "Test cases were successful!\n";
}




}
