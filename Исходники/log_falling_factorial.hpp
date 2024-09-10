inline typename boost::math::tools::promote_args<T1, T2>::type
log_falling_factorial(const T1 x, const T2 n) {
    if (is_nan(x) || is_nan(n))
        return std::numeric_limits<double>::quiet_NaN();
    static const char* fun = "log_falling_factorial";
    check_positive(fun, "first argument", x);
    return lgamma(x + 1) - lgamma(x - n + 1);
}