#include <iostream>
#include <cmath>

using namespace std;

bool converge(int counter, double x, double x_prev)
{

    if (counter > 50){return true;}
    if (abs(x-x_prev) < 1e-12){return true;}
    return false;
}

template <typename T, typename F1, typename F2>

T Newton(F1 f, F2 fd, T x0)
{
    double x1 = x0;
    int counter = 0;
    bool stop = false;

    while (stop != true){
       counter ++;
       double x_prev = x1;
       x1 = x1-f(x1)/fd(x1);
       stop = converge(counter, x1, x_prev);
       cout << "Result of iteration No. " << counter << ": " << x_prev << "     " << stop << endl;

}
    return x_prev;
}




int main(){
    cout.precision(16);
    Newton([](double x) {return x*x-612;}, [](double x) {return 2*x;}, 10);
    return 0;

}
