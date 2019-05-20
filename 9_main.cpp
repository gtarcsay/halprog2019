#include <iostream>
#include <fstream>
#include "6_matrix.h"

auto fill = [](int i){return i;};

int main(int, char**) {

    int max_thread = 5;
    int size = 500; 
    Matrix2<double> m1(size,fill);
    Matrix2<double> m2(size,fill);
    Matrix2<double> m3(size);
    auto time1 = std::chrono::high_resolution_clock::now();
    Matrix2<double> mref = m1*m2;
    auto time2 = std::chrono::high_resolution_clock::now();
    std::cout << std::chrono::duration_cast<std::chrono::milliseconds>(time2-time1).count() << std::endl;
    std::vector<double> time(max_thread);
    for(int t = 1; t<max_thread + 1; t++)
    {
        std::cout << "Run on " << t << " threads" << std::endl;
        auto time1 = std::chrono::high_resolution_clock::now();
        m3 =  parallel_mul(m1,m2,t); 
        auto time2 = std::chrono::high_resolution_clock::now();
        time[t-1] = static_cast<double>(std::chrono::duration_cast<std::chrono::milliseconds>(time2-time1).count());
    }
std::ofstream myfile;
  myfile.open ("time500.txt");
  for(int i=0;i < time.size(); i++){
    myfile << i+1  << "\t" << time[i] << std::endl;
  }  
  myfile.close();

    
}
