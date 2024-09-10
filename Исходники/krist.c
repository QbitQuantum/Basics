void deth(int nr, TYPE *h) {
    const int hmax = 20;
    const int kmax = 30;
    const int lmax = 15;
    int i;
    for (i = 0; i < nr; i++) {
        h[DIM2_H * i + 0] = rintf(2 * hmax * (TYPE) random() / (TYPE) RAND_MAX - hmax);
        h[DIM2_H * i + 1] = rintf(2 * kmax * (TYPE) random() / (TYPE) RAND_MAX - kmax);
        h[DIM2_H * i + 2] = rintf(2 * lmax * (TYPE) random() / (TYPE) RAND_MAX - lmax);
    }
}