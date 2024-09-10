int simd_chol(double *A, int n){

    register  int i;
    register  int j;
    register  int k;
    register  int local_size = n;
    register __m256d v1, v2, v3, v4, mul1, mul2, sum;

    for (j = 0; j < local_size; j++) {
        for (i = j; i < local_size; i++) {
            register double Aij = A[IDX(i, j, local_size)];
            if (j > 8)
                for (k = 0; k < j;) {
                    if (k < j - 8){

                        v1 = _mm256_loadu_pd(A+IDX(i, k, local_size));
                        v2 = _mm256_loadu_pd(A+IDX(j, k, local_size));
                        mul1 = _mm256_mul_pd(v1, v2);

                        v3 = _mm256_loadu_pd(A+IDX(i, k + 4, local_size));
                        v4 = _mm256_loadu_pd(A+IDX(j, k + 4, local_size));

                        mul2 = _mm256_mul_pd(v3, v4);

                        sum = _mm256_add_pd(mul1, mul2);
                        Aij -= (sum[3] + sum[2] + sum[1] + sum[0]);

                        k = k + 8;
                    } else {
                        Aij -= A[IDX(i, k, local_size)] * A[IDX(j, k, local_size)];
                        k++;
                    }
                }
                // i <= 8
            else for (k = 0; k < j; ++k)
                    Aij -= A[IDX(i, k, local_size)] * A[IDX(j, k, local_size)];
            A[IDX(i, j, local_size)] = Aij;
        }

        if (A[IDX(j, j, local_size)] < 0.0) {
            return (1);
        }

        A[IDX(j, j, local_size)] = sqrt(A[IDX(j, j, local_size)]);
        register double Ajj = A[IDX(j, j, n)];
        for (i = j + 1; i < local_size;){

            if (i < local_size - 8){
                A[IDX(i, j, local_size)] /= Ajj;
                A[IDX(i + 1, j, local_size)] /= Ajj;
                A[IDX(i + 2, j, local_size)] /= Ajj;
                A[IDX(i + 3, j, local_size)] /= Ajj;
                A[IDX(i + 4, j, local_size)] /= Ajj;
                A[IDX(i + 5, j, local_size)] /= Ajj;
                A[IDX(i + 6, j, local_size)] /= Ajj;
                A[IDX(i + 7, j, local_size)] /= Ajj;
                i += 8;
            } else {
                A[IDX(i, j, local_size)] /= Ajj;
                i++;
            }
        }
    }

    return (0);
}