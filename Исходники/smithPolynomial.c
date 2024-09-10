// initializes Q to identity
void initializeQ(float Q[][M][maxDegree+1]) {
	int i, j;
	for(i = 0; i < M; ++i) {
		for(j = 0; j < M; ++j) {
			setZero(Q[i][j]);
			if (i == j) {
				Q[i][j][0] = 1;
			}
		}
	}
}