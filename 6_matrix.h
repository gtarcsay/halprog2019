#include <vector>
#include <cmath>
#include <algorithm>

auto add = [](auto const& x, auto const& y){ return x + y; };
auto sub = [](auto const& x, auto const& y){ return x - y; };

// 2×2-es nagy mátrixok osztálya
//N*N = vektor mérete -> class kell legyen a matrix2, mert ez egy megszorítás
//class 3féle láthatóságot von maga után
template<typename T>
class Matrix2{

private:
  std::vector<T>data;	// -> ezeket inicializálni kell minden konstruktorban
	int N;				//  N = sqrt(data.size()) -> ez rossz, ha a felhasználó pl. 7-et ír be
						// helyette: data, N private-ba megy, utána a public: konstruktorok
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
	Matrix2(int dim)
	{
		if(dim < 0 ){std::cout << "Matrix size cannot be negative integer!\n"; std::exit(-1);}
		int Nsq = dim*dim;
		N = dim;
		data.resize(Nsq);
		for(int i = 0; i<Nsq;i++)
		{			
				data[i] = 0;	
		}
	}

		//Construct matrix with a function
	template <typename F>
	Matrix2(int dim, F f)
	{
		if(dim < 0 ){std::cout << "Matrix size cannot be negative integer!\n"; std::exit(-1);}
		N = dim;
		int Nsq = dim*dim;
		data.resize(Nsq);
		for(int i = 0; i<Nsq;i++)
		{			
				data[i] = f(i);	
		}
	}

	//Construct from initializer list:
	Matrix2(int dim, std::initializer_list<T> const& il ) 
	{
		if(dim < 0 ){std::cout << "Matrix size cannot be negative integer!\n"; std::exit(-1);}
		if(dim*dim != il.size()){
			std::cout << "Matrix size and number of initalizer list's elements do not match!\n";
			std::exit(-1);
			}
		N = dim;
		data = il;		
	}


    //number of elements
    int size()const
    {
        return static_cast<int>(data.size());
    }

	int dim()const
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

	
	  auto set_size(int size)
    {	
				if(data.size() != 0){return *this;}
        data.resize(size);
				return *this;
    }

	auto operator+=( Matrix2<T> const& m)
    {
		std::transform(data.cbegin(), data.cend(), m.cbegin(),data.begin(),  add);        
        return *this;
    };

		auto operator-=( Matrix2<T> const& m)
    {
		std::transform(data.cbegin(), data.cend(), m.cbegin(),data.begin(),  sub);

        
        return *this;
    };

		auto operator*=( T lambda)
    {
		std::transform(data.cbegin(), data.cend(), data.begin(),
               [lambda](auto const& c){return c*lambda;});
        
        return *this;
    };

		auto operator/=( T lambda)
    {
		std::transform(data.cbegin(), data.cend(), data.begin(),
               [lambda](auto const& c){return c/lambda;});
        
        return *this;
    };

    
};

template<typename T>
std::ostream& operator<<(std::ostream& o, Matrix2<T>const& m)
	{
		int dim = m.dim();
	//	if(m.size < 0){std::cout <<"Matrix is not defined!" <<std::endl; std::exit(-1);}
		for(int i =0; i<dim; i++ )
		{
			for(int j =0; j<dim;j++)
			{
				o << m(i,j) << " ";
			}
			o << "\n";
			
			
		}
		return o;
	}

template<typename T>
std::istream& operator>>(std::istream& i, Matrix2<T>& m)
{
	T value;
	std::vector<T> temp;
	const auto state = i.rdstate();
	const auto pos = i.tellg();
	while(i >> value)
	{
		temp.push_back(value);
		if(i.fail() == 1 )
			{
				i.seekg(pos);
				i.setstate(state);
				return i;
			}
	}
	auto dim = std::sqrt(temp.size());
	// is the dimension an integer? If yes -> matrix is quadratic
	if(abs(ceil(dim) - floor(dim)) > 1e-14)
	{
		i.seekg(pos);
		i.setstate(state);
		return i;
	}
	for(int k=0; k < static_cast<int>(dim*dim) ;k++ )
	{
			m[k] = temp[k];
	}
		
		return i;
	}
	
	


// + operators

// LL values
template<typename T>
Matrix2<T> operator+( Matrix2<T> const& m1, Matrix2<T> const& m2 )
{
	if(m1.size() < 0 || m2.size() < 0){std::cout<<"Matrix size cannot be negative integer!\n"; std::exit(-1);}
	if(m1.size()!=m2.size()){std::cout << "Size of matrices do not match! \n"; std::exit(-1);}
	Matrix2<T> result(m1.dim()); 
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
	if(m1.size() < 0 || m2.size() < 0){std::cout<<"Matrix size cannot be negative integer!\n"; std::exit(-1);}
	if(m1.size()!=m2.size()){std::cout << "Size of matrices do not match! \n"; std::exit(-1);}
	Matrix2<T> result(m1.dim()); 
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
	Matrix2<T> result(m.dim()); 
	std::transform(m.cbegin(), m.cend(), result.begin(),
               [lambda](auto const& c){return c*lambda;});
	return result;
}

template<typename T>
Matrix2<T>&& operator*( Matrix2<T>&& m, const T lambda)
{
	std::transform(m.cbegin(), m.cend(), m.begin(),
               [lambda](auto const& c){return c*lambda;});
	return std::move(m);
}

template<typename T>
auto operator*(const T lambda, Matrix2<T> const& m)
{
	Matrix2<T> result(m.dim());
	std::transform(m.cbegin(), m.cend(), result.begin(),
               [lambda](auto const& c){return c*lambda;});
	return result;
}

template<typename T>
Matrix2<T>&& operator*(const T lambda, Matrix2<T>&& m)
{
	//std::transform(m.cbegin(), m.cend(), result.begin(),
             //  std::bind1st(std::multiplies<T>(), lambda));
	std::transform(m.cbegin(), m.cend(), m.begin(),
              [lambda](auto const& c){return lambda*c;});

	return std::move(m);
}

// / operator
template<typename T>
auto operator/( Matrix2<T> const& m, const T lambda)
{
	Matrix2<T> result(m.dim()); 
	std::transform(m.cbegin(), m.cend(), result.begin(),
               [lambda](auto const& c){return c/lambda;});
	return result;
};

template<typename T>
Matrix2<T>&& operator/( Matrix2<T>&& m, const T lambda)
{
	std::transform(m.cbegin(), m.cend(), m.begin(),
               [lambda](auto const& c){return c/lambda;});
	return std::move(m);
}

//matrix multiplication

template<typename T>
auto operator*( Matrix2<T> const& m1, Matrix2<T> const& m2)
{
	int i, j,k;
	int size_n1 = m1.dim();	//result matrix: N×N
	int size_n2 = m2.dim();
	if(size_n1 != size_n2){std::cout<< "Matrix sizes do not match! \n"; std::exit(-1);}
	Matrix2<T> result(size_n1);
	T sum = 0.0;
	for(i = 0; i < size_n1; ++i)
	{	
		for(j = 0; j < size_n1; ++j)
		{
			sum = 0.0;
			for(k=0; k<size_n1; ++k)
			{
				sum += m1(i,k) * m2(k,j);
			}
			result(i,j) = sum;
			
		}
		
	}
	return result;
    
}

// RL multiplication
template<typename T>
auto operator*(Matrix2<T>&& m1, Matrix2<T> const& m2)
{
	int i, j,k, m;
	int size_n1 = m1.dim();	//result matrix: N1×M2
	int size_n2 = m2.dim();
	if(size_n1 != size_n2){std::cout<< "Matrix sizes do not match! \n"; std::exit(-1);}
	std::vector<T> temp;
	temp.resize(size_n1);
	T sum = 0.0;

	for(i = 0; i < size_n1; ++i)
	{	
		for(j = 0; j < size_n2; ++j)
		{
			
			sum = 0.0;
			for(k=0; k<size_n1; ++k)
			{
				sum += m1(i,k) * m2(k,j);
			}
			temp[j] = sum;
		}
		for(m = 0;m< size_n1; ++m)
		{
			m1(i,m) = temp[m];
		}
		
		
		}

		
	
	return std::move(m1);
}

//LR multiplication
template<typename T>
Matrix2<T>&& operator*(Matrix2<T> const& m1, Matrix2<T>&& m2)
{
	int i, j,k, m;
	int size_n1 = m1.dim();	//result matrix: N1×M2
	int size_n2 = m2.dim();
	if(size_n1 != size_n2 ){std::cout<< "Matrix sizes do not match! \n"; std::exit(-1);}
	std::vector<T> temp(size_n1);
	T sum = 0.0;

	for(i = 0; i < size_n1; ++i)
	{	
		
		for(j = 0; j < size_n1; ++j)
		{
			sum = 0.0;
			for(k=0; k<size_n1; ++k)
			{
				sum += m1(j,k) * m2(k,i);
			}
			temp[j] = sum;
		}
		for(m=0;m<size_n1;++m){
			m2(m,i) = temp[m];
		}
		
	}
	return std::move(m2);
    
}

//RR multiplication	
template<typename T>
Matrix2<T>&& operator*(Matrix2<T>&& m1, Matrix2<T>&& m2)
{
	int i, j,k, m;
	int size_n1 = m1.dim();	//result matrix: N1×M2
	int size_n2 = m2.dim();
	if(size_n1 != size_n2 ){std::cout<< "Matrix sizes do not match! \n"; std::exit(-1);}
	std::vector<T> temp(size_n1);
  T sum = 0.0;

	for(i = 0; i < size_n1; ++i)
	{	
		
		for(j = 0; j < size_n1; ++j)
		{
			sum = 0.0;
			for(k=0; k<size_n1; ++k)
			{
				sum += m1(i,k) * m2(k,j);
			}
			temp[j] = sum;
		}
		for(m=0;m<size_n1;++m){
			m1(i,m) = temp[m];
		}
		
	}
	return std::move(m1);
    
}
