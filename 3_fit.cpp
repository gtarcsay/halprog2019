#include <iostream>
#include <cmath>
#include <vector>
#include <array>
#include <algorithm>
#include <numeric>

using namespace std;

// Az input hibalehet�s�gei:
// * Az adatpontok n�vel�s�vel pontatlanabb eredm�nyt kapunk.
// * Min�l nagyobb az adat sz�r�sa, ann�l rosszabb eredm�nyt kapunk. �gy vettem �szre, hogy erre a metsz�spont �rt�ke nagyon �rz�keny.
// * Nem egyenl� x - y �rt�kek mellett szint�n elromlik a fit.

std::array<double, 3> fit(vector<double> const& x, vector<double> const& y, std::array<double, 3> & params){

    if(x.size() != y.size()){
        cout << "Az adatpontok szama nem egyezik meg!" << endl;
        return params;
        }

    // �tlagok kisz�mol�sa
    double mean_x = accumulate(x.begin(), x.end(), 0)/x.size();
    double mean_y = accumulate(y.begin(), y.end(), 0)/y.size();


    //�rt�kek eltol�sa az �tlag �rt�k�vel (x' �s y')
    auto fx = [mean_x](double a){return a-mean_x;};
    auto fy = [mean_y](double a){return a-mean_y;};

    // 2 vektor defini�l�sa, mivel x �s y const
    vector<double> x_shift;
    vector<double> y_shift;

    x_shift.resize(static_cast<int>(x.size()));
    y_shift.resize(static_cast<int>(y.size()));

    transform(x.begin(), x.end(), x_shift.begin(), fx );
    transform(y.begin(), y.end(), y_shift.begin(), fy);

    //ekkor a szumm�z�s egy skal�rszorz�snak felel meg: x'*y' �s x'*x'
    double numerator = inner_product(x_shift.begin(), x_shift.end(), y_shift.begin(),0);
    double denom = inner_product(x_shift.begin(), x_shift.end(), x_shift.begin(),0);

    //az egyenes param�terei
    double m = numerator/denom;
    double b = mean_y - mean_x*m;


    //r2
    double y2 = inner_product(y_shift.begin(), y_shift.end(), y_shift.begin(),0); //y' * y'
    double r = numerator/(sqrt(denom*y2));  // r = x'*y' / sqrt(x'2 * y'2)


    params = {m,b, r*r};

    return params;

}



int main(){

    array<double,3> params;
    vector<double> const x = {1,2,3,4,5,6,7,8,9,10};
    vector<double> const y = {-2,3,5,7,12,15,18,21,23,25};
    //vector<double> const x = {1,2,3,4};
    //vector<double> const y = {1,2,3,4};
    fit(x, y, params);

    cout << "Meredekseg: m = " << params[0] << endl << "Metszespont: b = " << params[1] << endl << "r^2 = " << params[2] << endl;

    return 0;

}
