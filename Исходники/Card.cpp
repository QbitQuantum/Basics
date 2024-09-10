inline long long int newton(const long long int &n, const long long int &k)
{
    return factorial[n] * inverse(factorial[k] * factorial[n - k]) % MOD;
}