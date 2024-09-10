/*Fills the matrix with the matching pattern then used to compute the LCS*/
void fillMatrixWithValues(int** mat, int **p,char* stringA,char* stringB, int lenA, int lenB){
	int i, j, s, t;

	for(i = 1; i <= lenA; i++) {
		for(j = 1; j <= lenB; j++) {
			//eq. 7
			t = (0 - p[getC(stringA[i - 1])][j]) < 0 ? 1 : 0;
			s = (0 - (mat[i - 1][j]-t*mat[i - 1][p[getC(stringA[i - 1])][j]-1])) < 0 ? 1 : 0;
			if(stringA[i-1]==stringB[j-1])
				cost(i);
			mat[i][j] = mat[i - 1][j] + t*(s ^ 1);
			//
		}
	}
}