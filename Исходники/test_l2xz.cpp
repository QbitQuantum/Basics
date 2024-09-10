static inline
Scalar varying_data(const Scalar& x, const Scalar& L)
{
    using boost::math::constants::pi;
    using std::cos;
    const Scalar twopi_L = 2*pi<Scalar>()/L;
    return cos(twopi_L*(x + 2*cos(twopi_L*3*x)));
}