#include <iostream>
#include <cmath>

using namespace std;

bool converge(int counter, double x)
{
    double target = 24.738633753705963298928;
    if (counter > 50){return true;}
    if (abs(x-target) < 1e-14){return true;}
    return false;
}

template <typename T, typename F1, typename F2>

T Newton(F1 f, F2 fd, T x0)
{
    double x1 = x0-f(x0)/fd(x0);
    int counter = 0;
    bool stop = false;

    while (stop != true){
       counter ++;
       x1 = x1-f(x1)/fd(x1);
       stop = converge(counter, x1);
       cout << "Result of iteration No. " << counter << ": " << x1 << "     " << stop << endl;
}
    return x1;
}




int main(){
    cout.precision(16);
    Newton([](double x) {return x*x-612;}, [](double x) {return 2*x;}, 10);
    return 0;

}
