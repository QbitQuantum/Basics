void initializeA(float A[][M][maxDegree+1], float Acopy[][M][maxDegree+1]) {
	int i, n, m;
	for(n = 0; n < N; ++n) {
		for(m = 0; m < M; ++m) {
			setZero(A[n][m]);
			setZero(Acopy[n][m]);
		}
	}

	// A[0][0][0] = 1;
	// A[0][0][1] = 0;
	// A[0][0][2] = 1;
	// A[0][1][0] = 0;
	// A[0][1][1] = -4;
	// A[0][1][2] = 3;
	// A[1][0][0] = 0;
	// A[1][0][1] = 8;
	// A[1][0][2] = 0;
	// A[1][1][0] = 0;
	// A[1][1][1] = 0;
	// A[1][1][2] = -1;

	float temp;
	float negative;
	// printf("Initialize the matrix \"A\".\n");
	for(n = 0; n < N; ++n) {
		for(m = 0; m < M; ++m) {
			for(i = 0; i <= maxEntry; ++i) {
				// printf("Enter the coefficient of x^%d in A[%d][%d]: ", i, n, m);
				// scanf("%f", &temp);

				//after this, negative will be either +1 or -1
				negative = (float) (rand()%2);
				negative = negative - 0.5;
				negative *= 2;

				temp = (float) (rand()%10);
				temp *= negative;

				A[n][m][i] = temp;
				Acopy[n][m][i] = temp;
			}
		}
	}
	
}