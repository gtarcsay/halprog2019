#include <vector>
#include <cmath>
#include <algorithm>
#include <functional>



auto add = [](auto const& x, auto const& y){ return x + y; };
auto sub = [](auto const& x, auto const& y){ return x - y; };
auto mult = [](auto const& x, auto const& y){return x*y};


// 2×2-es nagy mátrixok osztálya
//N*N = vektor mérete -> class kell legyen a matrix2, mert ez egy megszorítás
//class 3féle láthatóságot von maga után
template<typename T>
class Matrix2{

private:
  std::vector<T>data;	// -> ezeket inicializálni kell minden konstruktorban
	int N;				//  N = sqrt(data.size()) -> ez rossz, ha a felhasználó pl. 7-et ír be
	int M;				// helyette: data, N private-ba megy, utána a public: konstruktorok
						// felhasználó mondja meg a mátrix lineáris méretét, utána kezdjük a konstruálást, aztán
						//megnézzük, hogy ehhez megfelelő számú elemet adott-e meg a default konstruktorban -> 
						//konstruktor vár egy méretet és egy lambdát
						//copy, move már lehet default
						//kell-e hozzáférés a private tagookhoz?
public:	
	//műveleteknél csak a mátrixszorzás más a vektorokéhoz képest
	// - allokálunk egy új mátrixot az eredményhez (N^2)
	// - egy darab sort allokálunk, végig szorozzuk az első sort, és kicseréljük (N)

	//Subscript operator for reading and writing:
	T&       operator()( int i, int j )       { return data[N*i+j]; };
	T const& operator()( int i, int j ) const { return data[N*i+j]; };

	//Function call operator for reading and writing:
	T&       operator[]( int i )       { return data[i]; }
	T const& operator[]( int i ) const { return data[i]; }



    //Default, Copy and Move constructors implemented by the compiler:
	Matrix2() = default;
	Matrix2( Matrix2 const& ) = default;
	Matrix2( Matrix2 && ) = default;
	
	//Copy and Move assignment operators implemented by the compiler:
	Matrix2<T>& operator=(Matrix2 const&) = default;
	Matrix2<T>& operator=(Matrix2 &&) = default;
  

	//Construct 0 matrix from size
	Matrix2(int row, int column)
	{
		if(row < 0 || column < 0){std::cout << "Matrix size cannot be negative integer!\n"; std::exit(-1);}
		N = row;
		M = column;
		data.resize(N*M);
		for(int i = 0; i<N*M;i++)
		{			
				data[i] = 0;	
		}
	}

		//Construct matrix with a function
	template <typename F>
	Matrix2(int row, int column, F f)
	{
		if(row < 0 || column < 0){std::cout << "Matrix size cannot be negative integer!\n"; std::exit(-1);}
		N = row;
		M = column;
		data.resize(N*M);
		for(int i = 0; i<N*M;i++)
		{			
				data[i] = f(i);	
		}
	}

	//Construct from initializer list:
	Matrix2(int row, int column,  std::initializer_list<T> const& il ) 
	{
		if(row < 0 || column < 0){std::cout << "Matrix size cannot be negative integer!\n"; std::exit(-1);}
		if(row*column != il.size()){
			std::cout << "Matrix size and number of initalizer list's elements do not match!\n";
			std::exit(-1);
			}
		N = row;
		M = column;
		data = il;		
	}


    //number of elements
    int size()const
    {
        return static_cast<int>(data.size());
    }

	int row()const
	{
		return static_cast<int>(N);
	}

	int column()const
	{
		return static_cast<int>(N);
	}

	auto begin()
	{
		return data.begin();
	}

	auto cbegin() const
	{
		return data.cbegin();
	}

	auto end()
	{
		return data.end();
	}

	auto cend() const
	{
		return data.cend();
	}

	auto get_data() const
	{
		return data;
	}

	auto get_N() const
	{
		return N;
	}

	auto set_N(int n) 
	{
		N = n;
	}

	auto get_M() const
	{
		return M;
	}

	auto set_M(int m) 
	{
		M = m;
	}

	auto resize(int n)
	{
		data.resize(n);
	}

	auto insert1(std::vector<T> val)
	{
		data.insert(data.end(), val.begin(), val.end());
	}

	auto insert2(std::vector<T> val, T i, T column1)
	{
		data.insert(data.begin()+column1*i, val.begin(), val.end());
	}

	auto erase(T i, T column1)
	{
	
		data.erase(data.begin()+column1*i, data.begin()+column1*(i+1));
	}

	
	//template <typename T>
	//auto push_back(std::vector<T>const& temp)
	//{
		//data.push_back(std::move(temp));
	//}

	auto operator+=( Matrix2<T> const& m)
    {
		for(int i=0; i < data.size(); i++)
        data[i] += m[i];
        
        return *this;
    };

		auto operator-=( Matrix2<T> const& m)
    {
		for(int i=0; i < data.size(); i++)
        data[i] -= m[i];
        
        return *this;
    };

		auto operator*=( T lambda)
    {
		for(int i=0; i < data.size(); i++)
        data[i] *= lambda;
        
        return *this;
    };

		auto operator/=( T lambda)
    {
		for(int i=0; i < data.size(); i++)
        data[i] /= lambda;
        
        return *this;
    };

    
};


// + operators

// LL values
template<typename T>
Matrix2<T> operator+( Matrix2<T> const& m1, Matrix2<T> const& m2 )
{
	if(m1.size() <= 0 || m2.size() <= 0){std::cout<<"Matrices must be initialized for the + operation!\n"; std::exit(-1);}
	if(m1.size()!=m2.size()){std::cout << "Size of matrices do not match! \n"; std::exit(-1);}
	Matrix2<T> result(m1.get_N(), m1.get_M()); 
	std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), result.begin(), add);
	return result;
}

// RL values
template<typename T>
Matrix2<T>&& operator+(Matrix2<T>&& m1, Matrix2<T> const& m2 )
{
	std::transform(m1.cbegin(), m1.cend(), m2.cbegin(),m1.begin(),  add);
	return std::move(m1);
}

// LR values
template<typename T>
Matrix2<T>&& operator+( Matrix2<T> const& m1, Matrix2<T>&& m2 )
{
	std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), m2.begin(),  add);
	return std::move(m2);
}

//RR values
template<typename T>
Matrix2<T>&& operator+( Matrix2<T>&& m1, Matrix2<T>&& m2 )
{
	std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), m2.begin(),  add);
	return std::move(m2);
}

// - operators
// LL values
template<typename T>
Matrix2<T> operator-( Matrix2<T> const& m1, Matrix2<T> const& m2 )
{
	if(m1.size() <= 0 || m2.size() <= 0){std::cout<<"Matrices must be initialized for the + operation!\n"; std::exit(-1);}
	if(m1.size()!=m2.size()){std::cout << "Size of matrices do not match! \n"; std::exit(-1);}
	Matrix2<T> result(m1.get_N(), m1.get_M()); 
	std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), result.begin(), sub);
	return result;
}

// RL values
template<typename T>
Matrix2<T>&& operator-(Matrix2<T>&& m1, Matrix2<T> const& m2 )
{
	std::transform(m1.cbegin(), m1.cend(), m2.cbegin(),m1.begin(),  sub);
	return std::move(m1);
}

// LR values
template<typename T>
Matrix2<T>&& operator-( Matrix2<T> const& m1, Matrix2<T>&& m2 )
{
	std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), m2.begin(),  sub);
	return std::move(m2);
}

//RR values
template<typename T>
Matrix2<T>&& operator-( Matrix2<T>&& m1, Matrix2<T>&& m2 )
{
	std::transform(m1.cbegin(), m1.cend(), m2.cbegin(), m2.begin(),  sub);
	return std::move(m2);
}

//multiplying by scalar

template<typename T>
auto operator*( Matrix2<T> const& m, const T lambda)
{
	Matrix2<T> result(m.get_N(), m.get_M()); 
	std::transform(m.cbegin(), m.cend(), result.begin(),
               std::bind1st(std::multiplies<T>(), lambda));
	return result;
};

template<typename T>
auto operator*( Matrix2<T>&& m, const T lambda)
{
	std::transform(m.cbegin(), m.cend(), m.begin(),
               std::bind1st(std::multiplies<T>(), lambda));
	return m;
};

template<typename T>
auto operator*(const T lambda, Matrix2<T> const& m)
{
	Matrix2<T> result(m.get_N(), m.get_M());
	std::transform(m.cbegin(), m.cend(), result.begin(),
               std::bind1st(std::multiplies<T>(), lambda));
	return result;
};

template<typename T>
auto operator*(const T lambda, Matrix2<T>&& m)
{
	std::transform(m.cbegin(), m.cend(), m.begin(),
               std::bind1st(std::multiplies<T>(), lambda));
	return m;
};

// / operator
template<typename T>
auto operator/( Matrix2<T> const& m, const T lambda)
{
	Matrix2<T> result(m.get_N(), m.get_M()); 
	std::transform(m.cbegin(), m.cend(), result.begin(),
               std::bind1st(std::multiplies<T>(), 1/lambda));
	return result;
};

template<typename T>
auto operator/( Matrix2<T>&& m, const T lambda)
{
	std::transform(m.cbegin(), m.cend(), m.begin(),
               std::bind1st(std::multiplies<T>(), 1/lambda));
	return m;
};

//matrix multiplication

template<typename T>
auto mul( Matrix2<T> const& m1, Matrix2<T> const& m2)
{
	int i, j,k;
	int row1 = m1.get_N();	//result matrix: N1×M2
	int column1 = m1.get_M();
	int row2 = m2.get_N();
	int column2 = m2.get_M();
	if(column1 != row2 || column2 != row1){std::cout<< "Matrix sizes do not match! \n"; std::exit(-1);}
	Matrix2<T> result;

	for(i = 0; i < row1; ++i)
	{	
		std::vector<T> temp;
		temp.resize(column2);
		for(j = 0; j < column2; ++j)
		{
			for(k=0; k<column1; ++k)
			{
				temp[j] += m1(i,k) * m2(k,j);
			}
		}
		result.insert1(temp);
		//result.get_data().insert(result.end(), temp.begin(), temp.end());
		
	}
	return result;
    
};

// RL multiplication
template<typename T>
auto mul(Matrix2<T>&& m1, Matrix2<T> const& m2)
{
	int i, j,k;
	int row1 = m1.get_N();	//result matrix: N1×M2
	int column1 = m1.get_M();
	int row2 = m2.get_N();
	int column2 = m2.get_M();

	if(column1 != row2 || column2 != row1){std::cout<< "Matrix sizes do not match! \n"; std::exit(-1);}


	for(i = 0; i < row1; ++i)
	{	
		std::vector<T> temp;
		temp.resize(column2);
		for(j = 0; j < column2; ++j)
		{
			for(k=0; k<column1; ++k)
			{
				temp[j] += m1(i,k) * m2(k,j);
			}
		}
		m1.erase(i, column1);
		m1.insert2(temp, i, column1);
		
	}
	return std::move(m1);
};

//RR multiplication	
template<typename T>
auto mul(Matrix2<T>&& m1, Matrix2<T>&& m2)
{
	int i, j,k;
	int row1 = m1.get_N();	//result matrix: N1×M2
	int column1 = m1.get_M();
	int row2 = m2.get_N();
	int column2 = m2.get_M();

	if(column1 != row2 || column2 != row1){std::cout<< "Matrix sizes do not match! \n"; std::exit(-1);}


	for(i = 0; i < row1; ++i)
	{	
		std::vector<T> temp;
		temp.resize(column2);
		for(j = 0; j < column2; ++j)
		{
			for(k=0; k<column1; ++k)
			{
				temp[j] += m1(i,k) * m2(k,j);
			}
		}
		m1.erase(i, column1);
		m1.insert2(temp, i, column1);
		
	}
	return std::move(m1);
    
};