#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;

std::array<double, 3> fit(vector<double>& x, vector<double>& y){

    array<double,3> params = {};
    if(x.size() != y.size()){
        cout << "Az adatpontok szama nem egyezik meg!" << endl;

        return params;
        }

    // átlagok kiszámolása
    double mean_x = accumulate(x.begin(), x.end(), 0)/x.size();
    double mean_y = accumulate(y.begin(), y.end(), 0)/y.size();


    //értékek eltolása az átlag értékével (x' és y')
    auto fx = [mean_x](double a){return a-mean_x;};
    auto fy = [mean_y](double a){return a-mean_y;};

    // 2 vektor definiálása, mivel x és y const
    vector<double>& x_shift = x;
    vector<double>& y_shift = y;


    transform(x.begin(), x.end(), x_shift.begin(), fx );
    transform(y.begin(), y.end(), y_shift.begin(), fy);

    //ekkor a szummázás egy skalárszorzásnak felel meg: x'*y' és x'*x'
    double numerator = inner_product(x_shift.begin(), x_shift.end(), y_shift.begin(),0);
    double denom = inner_product(x_shift.begin(), x_shift.end(), x_shift.begin(),0);

    //az egyenes paraméterei
    double m = numerator/denom;
    double b = mean_y - mean_x*m;


    //r2
    double y2 = inner_product(y_shift.begin(), y_shift.end(), y_shift.begin(),0); //y' * y'
    double r = numerator/(sqrt(denom*y2));  // r = x'*y' / sqrt(x'2 * y'2)


    params = {m,b, r*r};

    return params;

}



int main(){


    vector<double> x = {1,2,3,4,5,6,7,8,9,10};
    vector<double> y = {-2,3,5,7,12,15,18,21,23,25};
    //vector<double> const x = {1,2,3,4};
    //vector<double> const y = {1,2,3,4};
    array<double,3> params = fit(x, y);
    cout << "Meredekseg = " << params[0] <<"\t Valodi meredekseg = 3.02424 +/- 0.1" << endl << "Metszespont= " << params[1] <<"\t Valodi metszespont = -3.9333 +/- 0.7" << endl << "r^2 = " << params[2] << endl;


    return 0;

}
