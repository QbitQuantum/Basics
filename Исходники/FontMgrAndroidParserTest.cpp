template <int N, typename T> static double test_parse_fixed_r(skiatest::Reporter* reporter,
                                                              double low, double high, double inc)
{
    double SK_FixedMax_double = nextafter(1 << (sizeof(T) * CHAR_BIT - N - 1), 0.0);
    double SK_FixedEpsilon_double = (1.0 / (1 << N));
    double maxError = 0;
    char buffer[64];
    for (double f = low; f < high; f += inc) {
        SkString s;
        // 'sprintf' formatting as expected depends on the current locale being "C".
        // We currently expect tests and tools to run in the "C" locale.
        sprintf(buffer, "%.20f", f);
        T fix;
        bool b = parse_fixed<N>(buffer, &fix);
        if (b) {
            double f2 = fix * SK_FixedEpsilon_double;
            double error = fabs(f - f2);
            REPORTER_ASSERT(reporter,  error <= SK_FixedEpsilon_double);
            maxError = SkTMax(maxError, error);
        } else {
            REPORTER_ASSERT(reporter, f < -SK_FixedMax_double || SK_FixedMax_double < f);
        }
    }

    //SkDebugf("maxError: %.20f\n", maxError);
    return maxError;
}