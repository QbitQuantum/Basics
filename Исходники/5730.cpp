#include <cmath>
#include <cstdio>
#include <cstring>
#include <algorithm>
typedef long long LL;
const int maxn = 100001, maxm = 131072, mod = 313;
const long double pi = acos(-1.0);
struct complex
{
    long double r, i;
    complex() {}
    complex(long double x, long double y) : r(x), i(y) {}
    friend complex operator + (const complex &a, const complex &b) { return complex(a.r + b.r, a.i + b.i); }
    friend complex operator - (const complex &a, const complex &b) { return complex(a.r - b.r, a.i - b.i); }
    friend complex operator * (const complex &a, const complex &b) { return complex(a.r * b.r - a.i * b.i, a.r * b.i + a.i * b.r); }
} x[maxm], y[maxm];
void FFT(complex a[], int n, int flag)
{
    for(int i = 1, j = n >> 1, k; i < n - 1; ++i)
    {
        if(i < j)
            std::swap(a[i], a[j]);
        for(k = n >> 1; j >= k; k >>= 1)
            j -= k;
        if(j < k)
            j += k;
    }
    for(int i = 1; i < n; i <<= 1)
    {
        complex wn(cos(pi / i), flag * sin(pi / i));
        for(int j = 0; j < n; j += i << 1)