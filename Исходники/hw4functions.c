void sort( double * a, double * b, double * c ){
    if (*a < *b) swap(a, b);
    if (*b < *c) swap(b, c);
    if (*a < *b) swap(a, b);
    printf("%f, %f, %f\n", *a, *b, *c);
}