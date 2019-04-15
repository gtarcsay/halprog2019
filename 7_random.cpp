#include <iostream>
#include "matrix.h"
#include <random>
#include <chrono>
#include <fstream>
#include <array>
#include <numeric>

void printf(std::vector<double> time, std::vector<int> dim3){
std::ofstream myfile;
  myfile.open ("time.txt");
  for(int i=0;i < time.size(); i++){
    myfile << time[i] << "\t" << dim3[i] << std::endl;
  }  
  myfile.close();
}


int main(int, char**) {

    std::mt19937 gen(20);
    std::normal_distribution<double> distr(100,20);
    int min = 2;
    int max =  200;
    int m = 0;
    int size = (max-min)/2;
    std::vector<double> time(size);
    std::vector<int> N3(size);
    double temp;
    for(int n = min; n < max; n= n+2)
    {
        auto t0 = std::chrono::high_resolution_clock::now();
        Matrix2<double> m1(n,[&](int i){ return distr(gen);});
        Matrix2<double> m2(n,[&](int i){ return distr(gen);});
        auto t_start = std::chrono::high_resolution_clock::now();
        Matrix2<double> m3 = m1*m2;
        auto t_stop = std::chrono::high_resolution_clock::now();
        N3[m] = n*n*n;
        temp = std::chrono::duration_cast<std::chrono::microseconds>(t_stop-t_start).count();
        time[m] = temp;
        //std::cout << time[m] << " us\t" << N3[m] << std::endl;
        m++;
    }
std::cout << "Printing data into file...\n";   
printf(time, N3);
    
}
