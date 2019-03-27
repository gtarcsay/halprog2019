template <typename T>

struct Vector2d
{
    T x, y;

        auto operator+=( Vector2d<T> const& v)
    {
        x += v.x;
        y += v.y;
        return *this;
    };

    auto operator-=( Vector2d<T> const& v)
    {
        x -= v.x;
        y -= v.y;
        return *this;
    };

    auto operator*=( T lambda)
    {
        x *= lambda;
        y *= lambda;
        return *this;
    };

    auto operator/=( T lambda)
    {
        if(lambda != static_cast<T>(0))
        {
            x /= lambda;
            y /= lambda;
        }
        else {std::cout << "0-val osztas nem lehetseges!\n";}
        return *this;
    };

};


template<typename T>
auto operator+( Vector2d<T> const& a, Vector2d<T> const& b)
{
    return Vector2d<T>{ a.x+ b.x, a.y+ b.y};
};

template<typename T>
auto operator-( Vector2d<T> const& a, Vector2d<T> const& b)
{
    return Vector2d<T>{ a.x - b.x, a.y - b.y};
};

template<typename T>
auto operator*( Vector2d<T> const& a, const T lambda)
{
    return Vector2d<T>{ a.x*lambda, a.y*lambda};
};

template<typename T>
auto operator*(const T lambda, Vector2d<T> const& a)
{
    return Vector2d<T>{ a.x*lambda, a.y*lambda};
};

template<typename T>
auto operator/( Vector2d<T> const& a, const T lambda)
{
    if(lambda != static_cast<T>(0)) {
        return Vector2d<T>{ a.x/lambda, a.y/lambda};
        }
    else {
        std::cout << "0-val osztas nem lehetseges!\n"; 
        return a;
        }
    
};


template<typename T>
auto dot( Vector2d<T> const& a, Vector2d<T> const& b)
{
    return a.x*b.x+a.y*b.y;
    
};

template<typename T>
auto sqlength(Vector2d<T> const& a)
{
    return a.x*a.x+a.y*a.y;
};

template<typename T>
auto length(Vector2d<T> const& a)
{
    return std::sqrt(a.x*a.x+a.y*a.y);
};

template<typename T>
auto normalize(Vector2d<T> const& a)
{
    T L = length(a);
    return Vector2d<T>{a.x/L, a.y/L};
};

template<typename T>
auto rotate(Vector2d<T> const& a, const T phi)
{   
    T cphi = std::cos(phi);
    T sphi = std::sin(phi);
    return Vector2d<T>{a.x*cphi - a.y*sphi, a.x*sphi + a.y*cphi};
};


template<typename T>
std::ostream& operator<<( std::ostream& o, Vector2d<T> const& v)
{
    o << "(" << v.x << "," << v.y <<")\n";
    return o;
}

template<typename T>
std::istream& operator>>( std::istream& i, Vector2d<T> & v)
{
    i >> v.x;
    i >> v.y;
    return i;
}
