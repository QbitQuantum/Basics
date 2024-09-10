int main()
{
    slong iter;
    flint_rand_t state;

    flint_printf("d_log_upper_bound....");
    fflush(stdout);

    flint_randinit(state);

    for (iter = 0; iter < 100000 * arb_test_multiplier(); iter++)
    {
        mpfr_t t;
        double x, y, z;

        mpfr_init2(t, 53);

        x = d_randtest2(state);
        x = ldexp(x, 100 - n_randint(state, 200));

        switch (n_randint(state, 10))
        {
            case 0:
                x = 1.0 + x;
                break;
            case 1:
                x = 1.0 - x;
                break;
            case 2:
                x = D_INF;
                break;
            case 3:
                x = 0.0;
                break;
            case 4:
                x = D_NAN;
                break;
            default:
                break;
        }

        y = mag_d_log_upper_bound(x);

        mpfr_set_d(t, x, MPFR_RNDD);
        mpfr_log(t, t, MPFR_RNDU);
        z = mpfr_get_d(t, MPFR_RNDD);

        if (y < z || fabs(y-z) > 0.000001 * fabs(z))
        {
            flint_printf("FAIL\n");
            flint_printf("x = %.20g\n", x);
            flint_printf("y = %.20g\n", y);
            flint_printf("z = %.20g\n", z);
            flint_abort();
        }

        mpfr_clear(t);
    }

    flint_randclear(state);
    flint_cleanup();
    flint_printf("PASS\n");
    return EXIT_SUCCESS;
}