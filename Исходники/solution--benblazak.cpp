int gcd(int a, int b) {
    a = abs(a);
    b = abs(b);

    if (a == 0 || b == 0)
        return a+b;

    if (a > b)
        return gcd(a-b, b);

    return gcd(a, b-a);
}