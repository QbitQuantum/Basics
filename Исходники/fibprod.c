ull* productFib(ull prod) {

        ull *out = malloc(3 * sizeof(ull*));
        ull isfib = 1;
        long double golden = 1.6180339887498948482;
        long double srfive = 2.2360679774997896964;
        long double p = (long double)prod;
        long double n, m, r, t;

        n = roundl(sqrtl(p / golden));
        m = p / n;
        r = fmodl(p, n);

        if (r > 0) {
                isfib = 0;
                t = floorl(logl(n * srfive) / logl(golden)) + 1;
                n = roundl(powl(golden, t) / srfive);
                m = roundl(powl(golden, t + 1) / srfive);
        }

        out[0] = (ull)n;
        out[1] = (ull)m;
        out[2] = isfib;
        return out;
}