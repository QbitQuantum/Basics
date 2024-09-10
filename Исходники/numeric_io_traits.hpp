inline int floating_point_decimals(T t)
{
    BOOST_STATIC_ASSERT(boost::is_float<T>::value);
#if defined LMI_MSVCRT
    // COMPILER !! This C runtime not only writes infinity as "1.#INF"
    // instead of "inf" but also "respects" the precision specifier
    // when doing so, truncating it to "1." if this function were to
    // return zero.
    if(is_infinite(t))
        {
        return 4;
        }
#endif // defined LMI_MSVCRT
    // Avoid taking the logarithm of zero or infinity.
    if(0 == t || is_infinite(t))
        {
        return 0;
        }
// TODO ?? As this is written on 2005-11-03, cygwin lacks fabsl().
// It would be far better to write replacements for this and other
// such functions in one unit-tested module, and use them here as
// well as in 'round_to.hpp'.
#if !defined __CYGWIN__
    long double z = std::numeric_limits<T>::epsilon() * fabsl(t);
    return std::max(0, static_cast<int>(-log10l(z)));
#else  // defined __CYGWIN__
    long double z = std::numeric_limits<T>::epsilon() * t;
    if(t < 0.0)
        {
        z = -z;
        }
    return std::max(0, static_cast<int>(-log10(z)));
#endif // defined __CYGWIN__
}