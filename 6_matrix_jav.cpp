#include <iostream>
#include <sstream>
#include "6_matrix.h"
#include "6_vector2.h"

int main(int, char**) {


auto err = [](auto str){ std::cout << "matrix.h error in: " << str << "\n"; std::exit(-1); };

auto testm = [](auto m1, auto mref, auto str){

    if(m1.size() != mref.size()){std::cout << str; std::exit(-1);}
    //if(m1.row() != mref.row()){std::cout << str; std::exit(-1);}  
    for(int i =0; i<m1.size()-1; i++)
    {
    if(std::abs(m1[i]-mref[i]) > 1e-14 ){
        std::cout << str;
        std::exit(-1);   
        }
    }  
       };

//test construction from initlist
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
std::vector<double> mref = {3.0, 17.0, 5.0, 19.0};
testm(m1, mref, "Error in matrix.h: constructor(int,int, init_list)\n");
}

//test construction 0 matrix
{
Matrix2<double> m1(2);
std::vector<double> mref = {0.0, 0.0, 0.0, 0.0};
testm(m1, mref, "Error in matrix.h: constructor(int)\n");
}


//test construction from arbitrary function
{
Matrix2<double> m1(2,[](int i){ return 5*i+i*i; });
std::vector<double> mref = {0.0, 6.0, 14.0, 24.0};
testm(m1, mref, "Error in matrix.h: constructor(int,int, f)\n");
}

//test << and >> for matrix
{
Matrix2<double> m_in(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m_out(2);
Matrix2<double> mref(2,{3.0, 17.0, 5.0, 19.0});
std::stringstream ss;
ss << m_in;
ss >> m_out;

testm(m_out, mref, "Error in matrix.h: out << operator\n");
}

//test << and >> for vectors
{
    Vector2d<double> v_in{5.0, 7.5};
    Vector2d<double> v_out;
    std::stringstream ss;
    ss << v_in;
    ss >> v_out;
    if(abs(v_in.x - v_out.x) > 1e-14 || abs(v_in.y - v_out.y) > 1e-14 )
    {std::cout<<"Error in 6_vector2.h: iostream.\n";}
}

//test dim() functions
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
if (m1.dim() != 2){std::cout <<"Error in matrix.h: dim()\n"; std::exit(-1); }
}


//test += operator
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
m1 += m2;
Matrix2<double> mref(2,{5.0, 30.0, 16.0, 26.0});
testm(m1, mref, "Error in matrix.h: += operation\n");
}

//test -= operator
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
m1 -= m2;
Matrix2<double> mref(2,{1.0, 4.0, -6.0, 11.0});
testm(m1, mref, "Error in matrix.h: -= operation\n");
}

//test *= operator
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
double lambda = 3.2;
m1 *= lambda;
Matrix2<double> mref(2,{9.6, 54.4, 16.0, 60.8});
testm(m1, mref, "Error in matrix.h: *= operation\n");

}

//test /= operator
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
double lambda = 2.0;
m1 /= lambda;
Matrix2<double> mref(2,{1.5, 8.5 , 2.5, 9.5});
testm(m1, mref, "Error in matrix.h: /= operation\n");

}



//test + operators

// LL
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = m1 + m2;
Matrix2<double> mref(2,{5.0, 30.0, 16.0, 26.0});
testm(m3, mref, "Error in matrix.h: + operation (LL-values)\n");
}

//RL
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = std::move(m1) + m2;
Matrix2<double> mref(2,{5.0, 30.0, 16.0, 26.0});
testm(m3, mref, "Error in matrix.h: + operation (RL-values)\n");
}

//LR
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = m1 + std::move(m2);
Matrix2<double> mref(2,{5.0, 30.0, 16.0, 26.0});
testm(m3, mref, "Error in matrix.h: + operation (LR-values)\n");
}

//RR
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = std::move(m1) + std::move(m2);
Matrix2<double> mref(2,{5.0, 30.0, 16.0, 26.0});
testm(m3, mref, "Error in matrix.h: + operation (RR-values)\n");
}


//test - operators

// LL
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = m1-m2;
Matrix2<double> mref(2,{1.0, 4.0, -6.0, 11.0});
testm(m3, mref, "Error in matrix.h: - operation (LL-values)\n");
}

//RL
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = std::move(m1)-m2;
Matrix2<double> mref(2,{1.0, 4.0, -6.0, 11.0});
testm(m3, mref, "Error in matrix.h: - operation (RL-values)\n");
}

//LR
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = m1-std::move(m2);
Matrix2<double> mref(2,{1.0, 4.0, -6.0, 11.0});
testm(m3, mref, "Error in matrix.h: - operation (LR-values)\n");
}

//RR
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = std::move(m1)-std::move(m2);
Matrix2<double> mref(2,{1.0, 4.0, -6.0, 11.0});
testm(m3, mref, "Error in matrix.h: - operation (RR-values)\n");
}




//test matrix * scalar and scalar*matrix
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
double lambda = 3.2;
Matrix2<double> mres = m1*lambda;
Matrix2<double> mref(2,{9.6, 54.4, 16.0, 60.8});
testm(mres, mref, "Error in matrix.h: * operation (from right)\n");
}

//Rvalue reference
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
double lambda = 3.2;
Matrix2<double> mres = std::move(m1)*lambda;
Matrix2<double> mref(2,{9.6, 54.4, 16.0, 60.8});
testm(mres, mref, "Error in matrix.h: * operation (from right) with R value reference.\n");
}

//multiplying from left
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
double lambda = 3.2;
Matrix2<double> mres = lambda*m1;
Matrix2<double> mref(2,{9.6, 54.4, 16.0, 60.8});
testm(mres, mref, "Error in matrix.h: * operation (from left)\n");
}

//R value reference
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
double lambda = 3.2;
Matrix2<double> mres = lambda*std::move(m1);
Matrix2<double> mref(2,{9.6, 54.4, 16.0, 60.8});
testm(mres, mref, "Error in matrix.h: * operation (from left) with R value reference.\n");
}

//test matrix/scalar
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
double lambda = 2.0;
Matrix2<double> mres = m1/lambda;
Matrix2<double> mref(2,{1.5, 8.5 , 2.5, 9.5});
testm(mres, mref, "Error in matrix.h: / operation \n");
}

//R value reference
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
double lambda = 2.0;
Matrix2<double> mres = std::move(m1)/lambda;
Matrix2<double> mref(2,{1.5, 8.5 , 2.5, 9.5});
testm(mres, mref, "Error in matrix.h: / operation \n");
}

//matrix multiplication
//LL values
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = m1*m2;
Matrix2<double> mref(2,{193.0, 158.0, 219.0, 198.0});
testm(m3, mref, "Error in matrix.h: matrix multiplication, LL values.\n");
}

//LR values
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = m1*std::move(m2);
Matrix2<double> mref(2,{193.0, 158.0, 219.0, 198.0});
testm(m3, mref, "Error in matrix.h: matrix multiplication, LR values.\n");
}

//RL values
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = std::move(m1)*m2;
Matrix2<double> mref(2,{193.0, 158.0, 219.0, 198.0});
//std::cout << m3(0,0) << "\t" << m3(0,1) << "\n" << m3(1,0) << "\t" << m3(1,1)<< std::endl;
testm(m3, mref, "Error in matrix.h: matrix multiplication, RL values.\n");
}

//RR values
{
Matrix2<double> m1(2,{3.0, 17.0, 5.0, 19.0});
Matrix2<double> m2(2,{2.0, 13.0, 11.0, 7.0});
Matrix2<double> m3 = std::move(m1)*std::move(m2);
Matrix2<double> mref(2,{193.0, 158.0, 219.0, 198.0});
testm(m3, mref, "Error in matrix.h: matrix multiplication, RL values.\n");
}


std::cout<< "Test cases were successful!\n" << std::endl;
}