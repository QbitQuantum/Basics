void sgemm( int m, int n, int d, float *A, float *C )
{
	#pragma omp parallel
	{
		__m128 vect, ATmatrix, ATvect1, ATvect2, ATvect3, ATvect4, ATvect5, ATvect6, ATvect7, Cmatrix, vect2, vect3, vect4, ATvect3j, AT3j, ATvect2j, AT2j, ATvect1j, AT1j, ATjmatrix, ATj;
		#pragma omp for
		for( int j = 0; j < n/2 * 2; j+=2 ) {
			for( int k = 0; k < m/4 * 4; k+=4 ) {
				ATmatrix =  _mm_load1_ps(A + (j * (n + 1) + (k) * (n)));
				float AT = A[j*(n+1)+k*(n)];
				ATjmatrix =  _mm_load1_ps(A + ((j+1) * (n + 1) + (k) * (n)));
				float ATj = A[(j+1)*(n+1)+k*(n)];

				ATvect1 =  _mm_load1_ps(A + (j * (n + 1) + (k+1) * (n)));
				float AT1 = A[j*(n+1)+(k+1)*(n)];
				ATvect1j =  _mm_load1_ps(A + ((j + 1) * (n + 1) + (k + 1) * (n)));
				float AT1j = A[(j + 1)*(n+1)+(k + 1)*(n)];

				ATvect2 =  _mm_load1_ps(A + (j * (n + 1) + (k+2) * (n)));
				float AT2 = A[j*(n+1)+(k+2)*(n)];
				ATvect2j =  _mm_load1_ps(A + ((j + 1) * (n + 1) + (k + 2) * (n)));
				float AT2j = A[(j + 1)*(n+1)+(k + 2)*(n)];

				ATvect3 =  _mm_load1_ps(A + (j * (n + 1) + (k+3) * (n)));
				float AT3 = A[j*(n+1)+(k+3)*(n)];
				ATvect3j =  _mm_load1_ps(A + ((j + 1) * (n + 1) + (k + 3) * (n)));
				float AT3j = A[(j + 1)*(n+1)+(k + 3)*(n)];

				for( int i = 0; i < n/8 * 8; i+= 8 ) {
					float *temp = C + i + j * n;
					float *tempj = C + i + (j + 1) * n;
					float *tmp = A + i + (k)*(n);
					float *tmp1 = A + i + (k + 1)*(n);
					float *tmp2 = A + i + (k + 2)*(n);
					float *tmp3 = A + i + (k + 3)*(n);

					//i = 0
					Cmatrix = _mm_loadu_ps(temp);
				    vect = _mm_mul_ps(_mm_loadu_ps(tmp), ATmatrix);
				    vect2 = _mm_mul_ps(_mm_loadu_ps(tmp1), ATvect1);
				    vect3 = _mm_mul_ps(_mm_loadu_ps(tmp2), ATvect2);
				    vect4 = _mm_mul_ps(_mm_loadu_ps(tmp3), ATvect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    Cmatrix = _mm_add_ps(Cmatrix, vect2);
				    Cmatrix = _mm_add_ps(Cmatrix, vect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect4);
				    _mm_storeu_ps(temp, Cmatrix);
				    //j + 1
				    Cmatrix = _mm_loadu_ps(tempj);
				    vect = _mm_mul_ps(_mm_loadu_ps(tmp), ATjmatrix);
				    vect2 = _mm_mul_ps(_mm_loadu_ps(tmp1), ATvect1j);
				    vect3 = _mm_mul_ps(_mm_loadu_ps(tmp2), ATvect2j);
				    vect4 = _mm_mul_ps(_mm_loadu_ps(tmp3), ATvect3j);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    Cmatrix = _mm_add_ps(Cmatrix, vect2);
				    Cmatrix = _mm_add_ps(Cmatrix, vect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect4);
				    _mm_storeu_ps(tempj, Cmatrix);

				    // i = 1

				    Cmatrix = _mm_loadu_ps((temp) + 4);
				    vect = _mm_mul_ps(_mm_loadu_ps((tmp) + 4), ATmatrix);
				    vect2 = _mm_mul_ps(_mm_loadu_ps((tmp1) + 4), ATvect1);
				    vect3 = _mm_mul_ps(_mm_loadu_ps((tmp2) + 4), ATvect2);
				    vect4 = _mm_mul_ps(_mm_loadu_ps((tmp3) + 4), ATvect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    Cmatrix = _mm_add_ps(Cmatrix, vect2);
				    Cmatrix = _mm_add_ps(Cmatrix, vect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect4);
				    _mm_storeu_ps((temp) + 4, Cmatrix);
				    // j + 1
				    Cmatrix = _mm_loadu_ps(tempj + 4);
				    vect = _mm_mul_ps(_mm_loadu_ps(tmp + 4), ATjmatrix);
				    vect2 = _mm_mul_ps(_mm_loadu_ps(tmp1 + 4), ATvect1j);
				    vect3 = _mm_mul_ps(_mm_loadu_ps(tmp2 + 4), ATvect2j);
				    vect4 = _mm_mul_ps(_mm_loadu_ps(tmp3 + 4), ATvect3j);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    Cmatrix = _mm_add_ps(Cmatrix, vect2);
				    Cmatrix = _mm_add_ps(Cmatrix, vect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect4);
				    _mm_storeu_ps(tempj + 4, Cmatrix);

				}
				for (int i = n/8 * 8; i < n; i += 1) {
					C[i+j*n] += A[i+k*(n)] * AT + A[i+(k+1)*(n)] * AT1 + A[i+(k+2)*(n)] * AT2 + A[i+(k+3)*(n)] * AT3;
					C[i+(j + 1)*n] += A[i+k*(n)] * ATj + A[i+(k+1)*(n)] * AT1j + A[i+(k+2)*(n)] * AT2j + A[i+(k+3)*(n)] * AT3j;
				}
			}
			for (int k = m/4 * 4; k < m; k += 1) {
				ATmatrix =  _mm_load1_ps(A + (j * (n + 1) + (k) * (n)));
				float AT = A[j*(n+1)+k*(n)];

				ATjmatrix =  _mm_load1_ps(A + ((j + 1) * (n + 1) + (k) * (n)));
				float ATj = A[(j + 1)*(n+1)+k*(n)];
				for( int i = 0; i < n/12 * 12; i+= 12 ) {
					float *temp = C + i + j * n;
					float *t2 = A + i + (k)*(n);
					float *tempj = C + i + (j+1) * n;

					//i = 0
					Cmatrix = _mm_loadu_ps(temp);
				    vect = _mm_mul_ps(_mm_loadu_ps(t2), ATmatrix);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    _mm_storeu_ps(temp, Cmatrix);
				    //j + 1
				    Cmatrix = _mm_loadu_ps(tempj);
				    vect = _mm_mul_ps(_mm_loadu_ps(t2), ATjmatrix);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    _mm_storeu_ps(tempj, Cmatrix);

				    //i = 1
				    Cmatrix = _mm_loadu_ps((temp) + 4);
				    vect = _mm_mul_ps(_mm_loadu_ps((t2) + 4), ATmatrix);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    _mm_storeu_ps((temp) + 4, Cmatrix);
				    //j + 1
				    Cmatrix = _mm_loadu_ps((tempj) + 4);
				    vect = _mm_mul_ps(_mm_loadu_ps((t2) + 4), ATjmatrix);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    _mm_storeu_ps((tempj) + 4, Cmatrix);

				    //i = 2
				    Cmatrix = _mm_loadu_ps((temp) + 8);
				    vect = _mm_mul_ps(_mm_loadu_ps((t2) + 8), ATmatrix);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    _mm_storeu_ps((temp) + 8, Cmatrix);
				    //j + 1
				    Cmatrix = _mm_loadu_ps((tempj) + 8);
				    vect = _mm_mul_ps(_mm_loadu_ps((t2) + 8), ATjmatrix);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    _mm_storeu_ps((tempj) + 8, Cmatrix);
				}
				for (int i = n/12 * 12; i < n; i += 1) {
					C[i+j*n] += A[i+k*(n)] * AT;
					C[i+(j+1)*n] += A[i+k*(n)] * ATj;
				}
			}
		}
	}
	#pragma omp parallel
	{
		__m128 vect, ATmatrix, ATvect1, ATvect2, ATvect3, ATvect4, ATvect5, ATvect6, ATvect7, Cmatrix, vect2, vect3, vect4, ATvect3j, AT3j, ATvect2j, AT2j, ATvect1j, AT1j, ATjmatrix, ATj;
		#pragma omp for
		for (int j = n/2 * 2; j < n; j ++) {
			for( int k = 0; k < m/4 * 4; k+=4 ) {
				ATmatrix =  _mm_load1_ps(A + (j * (n + 1) + (k) * (n)));
				float AT = A[j*(n+1)+k*(n)];

				ATvect1 =  _mm_load1_ps(A + (j * (n + 1) + (k+1) * (n)));
				float AT1 = A[j*(n+1)+(k+1)*(n)];

				ATvect2 =  _mm_load1_ps(A + (j * (n + 1) + (k+2) * (n)));
				float AT2 = A[j*(n+1)+(k+2)*(n)];

				ATvect3 =  _mm_load1_ps(A + (j * (n + 1) + (k+3) * (n)));
				float AT3 = A[j*(n+1)+(k+3)*(n)];
				for( int i = 0; i < n/8 * 8; i+= 8 ) {
					float *temp = C + i + j * n;
					float *tmp = A + i + (k)*(n);
					float *tmp1 = A + i + (k + 1)*(n);
					float *tmp2 = A + i + (k + 2)*(n);
					float *tmp3 = A + i + (k + 3)*(n);
					//i = 0
					Cmatrix = _mm_loadu_ps(temp);
				    vect = _mm_mul_ps(_mm_loadu_ps(tmp), ATmatrix);
				    vect2 = _mm_mul_ps(_mm_loadu_ps(tmp1), ATvect1);
				    vect3 = _mm_mul_ps(_mm_loadu_ps(tmp2), ATvect2);
				    vect4 = _mm_mul_ps(_mm_loadu_ps(tmp3), ATvect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    Cmatrix = _mm_add_ps(Cmatrix, vect2);
				    Cmatrix = _mm_add_ps(Cmatrix, vect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect4);
				    _mm_storeu_ps(temp, Cmatrix);

				    //i = 1
				    Cmatrix = _mm_loadu_ps((temp) + 4);
				    vect = _mm_mul_ps(_mm_loadu_ps((tmp) + 4), ATmatrix);
				    vect2 = _mm_mul_ps(_mm_loadu_ps((tmp1) + 4), ATvect1);
				    vect3 = _mm_mul_ps(_mm_loadu_ps((tmp2) + 4), ATvect2);
				    vect4 = _mm_mul_ps(_mm_loadu_ps((tmp3) + 4), ATvect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    Cmatrix = _mm_add_ps(Cmatrix, vect2);
				    Cmatrix = _mm_add_ps(Cmatrix, vect3);
				    Cmatrix = _mm_add_ps(Cmatrix, vect4);
				    _mm_storeu_ps((temp) + 4, Cmatrix);
				    
				}
				for (int i = n/8 * 8; i < n; i += 1) {
					C[i+j*n] += A[i+k*(n)] * AT + A[i+(k+1)*(n)] * AT1 + A[i+(k+2)*(n)] * AT2 + A[i+(k+3)*(n)] * AT3;
				}
			}
			for (int k = m/4 * 4; k < m; k += 1) {
				ATmatrix =  _mm_load1_ps(A + (j * (n + 1) + (k) * (n)));
				float AT = A[j*(n+1)+k*(n)];
				for( int i = 0; i < n/8 * 8; i+= 8 ) {

					float *temp = C + i + j * n;
					float *tempj = C + i + (j + 1) * n;
					//i = 0
					Cmatrix = _mm_loadu_ps(temp);
				    vect = _mm_mul_ps(_mm_loadu_ps(A + i + (k)*(n)), ATmatrix);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    _mm_storeu_ps(temp, Cmatrix);

				    //i = 1
				    Cmatrix = _mm_loadu_ps((temp) + 4);
				    vect = _mm_mul_ps(_mm_loadu_ps((A + i + (k)*(n)) + 4), ATmatrix);
				    Cmatrix = _mm_add_ps(Cmatrix, vect);
				    _mm_storeu_ps((temp) + 4, Cmatrix);
				}
				for (int i = n/8 * 8; i < n; i += 1) {
					C[i+j*n] += A[i+k*(n)] * AT;
				}
			}
		}
	}
}