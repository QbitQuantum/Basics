// from Intel's sample intrin_double_sample.c
void multiply_SSE3(double xr, double xi, double yr, double yi,
    complex_num *z)
{
    __m128d num1, num2, num3;

    // Duplicates lower vector element into upper vector element.
    //   num1: [x.real, x.real]

    num1 = _mm_loaddup_pd(&xr);

    // Move y elements into a vector
    //   num2: [y.img, y.real]

    num2 = _mm_set_pd(yi, yr);

    // Multiplies vector elements
    //   num3: [(x.real*y.img), (x.real*y.real)]

    num3 = _mm_mul_pd(num2, num1);

    //   num1: [x.img, x.img]

    num1 = _mm_loaddup_pd(&xi);

    // Swaps the vector elements
    //   num2: [y.real, y.img]

    num2 = _mm_shuffle_pd(num2, num2, 1);

    //   num2: [(x.img*y.real), (x.img*y.img)]

    num2 = _mm_mul_pd(num2, num1);

    // Adds upper vector element while subtracting lower vector element
    //   num3: [((x.real *y.img)+(x.img*y.real)),
    //          ((x.real*y.real)-(x.img*y.img))]

    num3 = _mm_addsub_pd(num3, num2);

    // Stores the elements of num3 into z

    _mm_storeu_pd((double *)z, num3);

}