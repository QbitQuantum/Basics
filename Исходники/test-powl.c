static int
do_test (void)
{
    int result = 0;

#ifndef NO_LONG_DOUBLE
# if LDBL_MANT_DIG == 64
    {
        long double x = 1e-20;
        union ieee854_long_double u;
        u.ieee.mantissa0 = 1;
        u.ieee.mantissa1 = 1;
        u.ieee.exponent = 0;
        u.ieee.negative = 0;
        (void) powl (0.2, u.d);
        x = powl (x, 1.5);
        if (fabsl (x - 1e-30) > 1e-10)
        {
            printf ("powl (1e-20, 1.5): wrong result: %Lg\n", x);
            result = 1;
        }
    }
# endif
#endif

    return result;
}