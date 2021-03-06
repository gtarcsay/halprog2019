#include <iostream>
#include<cmath>
#include<math.h>

using namespace std;

// Newton iteráció gyök meghatározására
double sqrt_newton(double num, double x0)
{
    if(num < 0)
    {
        cout << "No real solution!" << endl;
    }

    // x_i = x_(i-1) - f(x0)/f'(x0) - x inicializiálása
    double  fx, fderivx, xcheck;
    double x1 = x0 - (x0*x0-num)/(2*x0);
    int converge = 1;        // stop, ha konvergál
    int counter = 0;         // számláló


    while (converge != 0){
        counter ++;
        xcheck = x1;
        fx = x1*x1-num;
        fderivx = 2*x1;
        x1 = x1 - fx/fderivx;
        cout << "Result of iteration number " << counter << ": " << x1 << "and xcheck: " << xcheck << endl;
        if (abs(xcheck-x1) < 0.00001)
            {
                converge = 0;
                cout << "Sqare roots of " << num << ": +/-" << x1 << endl;
            }
     //   if (counter > 1000) {
       //     break;
       // }
    }
    return converge;
}

//Newton-Coates integrálás f(x) = x^2*sin(x)-re trapéz-szabályra
double integrate(int n, double x0, double x1)       //n : felosztási pont, x0 és x1: határok
{


double h, fx_sum, fx0, fx1, x, Integral;
h = (x1-x0)/n;        //integrálás lépéshossza
fx_sum =0;
fx0 = x0*x0*sin(x0)/2;         //  f(x = x0) járuléka
fx1 = x1*x1*sin(x1)/2;         // f(x = x1) járuléka
x = x0;
Integral;            // végső értéknek


for(int m = 1;m < n-1; m++)
{
    x =  m*h + x0;          //update x
    fx_sum += x*x*sin(x);
}

Integral = (fx_sum+fx0+fx1)*h ;

return Integral;

}



int main(){
    cout.precision(16);

    for(int i =1; i < 501; i++){                //loop: # of steps  1000től 1000*500ig
    cout << "Result: " << integrate(1000*i,-4,9) << " Steps of iteration: " << 1000*i <<  endl;
    }
//megjegyzés: wolphramalpha szerint a megoldás 76.301, ezt az értéket még 500 000-es lépésszámnál sem éri el

    //1024 négyzetgyöke 10-es tippeléssel
    sqrt_newton(1024.,10.);
}
