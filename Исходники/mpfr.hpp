inline long lround(__gmp_expr<T,U> const& x, const Policy& pol)
{
   return lround(static_cast<mpfr_class>(x), pol);
}