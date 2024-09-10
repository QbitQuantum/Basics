int main(void) {
    double  a1 = 1.0, b1 = -10.5, c1 = 32.0, d1 = -30.0;
    double  a2 = 1.0, b2 = -4.5, c2 = 17.0, d2 = -30.0;
    double  x[3];
    int     solutions;

    SolveCubic(a1, b1, c1, d1, &solutions, x);

    /* should get 3 solutions: 2, 6 & 2.5   */

    SolveCubic(a2, b2, c2, d2, &solutions, x);

    /* should get 1 solution: 2.5           */

    return 0;
}