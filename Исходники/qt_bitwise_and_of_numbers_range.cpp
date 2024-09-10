 int rangeBitwiseAnd(int m, int n) {
    /// return 0xffffffff<<(int)floor(log(n-m))&n; //bug:n-m可能为0
    return (0xffffffff << (int)ceil(log2(n-m+1))) & m & n;
    或
    return (n > m) ? (rangeBitwiseAnd(m/2, n/2) << 1) : m;
 }