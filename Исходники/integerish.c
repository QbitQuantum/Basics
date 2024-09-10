static inline int_check_t is_unconvertible_double(const double x, const double tol) {
    if (!ISNAN(x)) {
        if (x <= INT_MIN || x > INT_MAX)
            return INT_RANGE;
        if (fabs(x - nearbyint(x)) >= tol)
            return INT_TOL;
    }
    return INT_OK;
}