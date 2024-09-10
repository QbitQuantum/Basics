/*
 ?? 把n分解成所有素数的乘积，然后求ln(primt)，并用数组保存起来，可能会更快 ??
 */
long double ln_n(int n) {
    int lg_max = lg(n);
    long double ex = powl(2.0, lg_max);
    long double x = n / ex;
    
    return lg_max * M_LN2 + lnx(x, K);
}