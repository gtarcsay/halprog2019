#include <iostream>
#include "matrix.h"
#include <random>
#include <chrono>
#include <fstream>
#include <array>
#include <numeric>
#include <algorithm>


int main(int, char**) {

    std::mt19937 gen(20);
    std::normal_distribution<double> distr(100,20);
    int min = 2;
    int max =  200;
    int m = 0;
    int size = (max-min)/2;
    int repeat = 50;
    std::vector<double> time(size);
    std::vector<int> N3(size);
    std::vector<double> temp(repeat);
    for(int n = min; n < max; n= n+2)
    {

        for(int l = 0; l < repeat; l++ )
          {
          Matrix2<double> m1(n,[&](int i){ return distr(gen);});
          Matrix2<double> m2(n,[&](int i){ return distr(gen);});
          auto t_start = std::chrono::high_resolution_clock::now();
          Matrix2<double> m3 = m1*m2;
          auto t_stop = std::chrono::high_resolution_clock::now();
          temp[l] = std::chrono::duration_cast<std::chrono::microseconds>(t_stop-t_start).count();
          }
        auto t_min = std::min_element(temp.begin(), temp.end());

        N3[m] = n*n*n;        
        time[m] = *t_min;
        m++;
    }

std::ofstream myfile;
  myfile.open ("time.txt");
  for(int i=0;i < time.size(); i++){
    myfile << N3[i] << "\t" << time[i] << std::endl;
  }  
  myfile.close();
    
}
