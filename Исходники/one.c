int nth_digit (int n, int i) {
    int m = n;
    int j = log10l(n);
    while (j>i) {
        m /= 10;
        j--;
    }
    return m % 10;
}