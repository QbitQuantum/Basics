std::vector<T> legendre_p_zeros_imp(int n, const Policy& pol)
{
    using std::cos;
    using std::sin;
    using std::ceil;
    using std::sqrt;
    using boost::math::constants::pi;
    using boost::math::constants::half;
    using boost::math::tools::newton_raphson_iterate;

    BOOST_ASSERT(n >= 0);
    std::vector<T> zeros;
    if (n == 0)
    {
        // There are no zeros of P_0(x) = 1.
        return zeros;
    }
    int k;
    if (n & 1)
    {
        zeros.resize((n-1)/2 + 1, std::numeric_limits<T>::quiet_NaN());
        zeros[0] = 0;
        k = 1;
    }
    else
    {
        zeros.resize(n/2, std::numeric_limits<T>::quiet_NaN());
        k = 0;
    }
    T half_n = ceil(n*half<T>());

    while (k < (int)zeros.size())
    {
        // Bracket the root: Szego:
        // Gabriel Szego, Inequalities for the Zeros of Legendre Polynomials and Related Functions, Transactions of the American Mathematical Society, Vol. 39, No. 1 (1936)
        T theta_nk =  ((half_n - half<T>()*half<T>() - static_cast<T>(k))*pi<T>())/(static_cast<T>(n)+half<T>());
        T lower_bound = cos( (half_n - static_cast<T>(k))*pi<T>()/static_cast<T>(n + 1));
        T cos_nk = cos(theta_nk);
        T upper_bound = cos_nk;
        // First guess follows from:
        //  F. G. Tricomi, Sugli zeri dei polinomi sferici ed ultrasferici, Ann. Mat. Pura Appl., 31 (1950), pp. 93-97;
        T inv_n_sq = 1/static_cast<T>(n*n);
        T sin_nk = sin(theta_nk);
        T x_nk_guess = (1 - inv_n_sq/static_cast<T>(8) + inv_n_sq /static_cast<T>(8*n) - (inv_n_sq*inv_n_sq/384)*(39  - 28 / (sin_nk*sin_nk) ) )*cos_nk;

        boost::uintmax_t number_of_iterations = policies::get_max_root_iterations<Policy>();

        legendre_p_zero_func<T, Policy> f(n, pol);

        const T x_nk = newton_raphson_iterate(f, x_nk_guess,
                                              lower_bound, upper_bound,
                                              policies::digits<T, Policy>(),
                                              number_of_iterations);

        BOOST_ASSERT(lower_bound < x_nk);
        BOOST_ASSERT(upper_bound > x_nk);
        zeros[k] = x_nk;
        ++k;
    }
    return zeros;
}