CppAD::ADFun<T>* AtanTestOneFunc(const std::vector<CppAD::AD<T> >& u) {
    using CppAD::atan;
    using namespace CppAD;

    assert(u.size() == 1);

    size_t s = 0;

    // some temporary values
    AD<T> x = cos(u[s]);
    AD<T> y = sin(u[s]);
    AD<T> z = y / x; // tan(s)

    // dependent variable vector and indices
    std::vector< AD<T> > Z(1);
    size_t a = 0;

    // dependent variable values
    Z[a] = atan(z); // atan( tan(s) )

    // create f: U -> Z and vectors used for derivative calculations
    return new ADFun<T > (u, Z);
}