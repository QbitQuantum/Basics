 __host__ __device__ double operator() (double a, double b) const {
     if (a == NEGATIVE_INFINITY) return b;
     if (b == NEGATIVE_INFINITY) return a;
     return a>b ? a+log1p(exp(b-a)) : b+log1p(exp(a-b));
 }