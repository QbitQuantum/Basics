void prefetch_Ablock(const double* A, int col, int row, int m, int n, int k, int bm, int bn, int bk){
	double* A_prefetch = (double*)A + (col * m + row);
	for(int i = 0; i < bk; i++){
		double* A_prefetch_m = A_prefetch;
		for(int j = 0; j < (bm + CACHE_LINE - 1) / CACHE_LINE; j++){
			_mm_prefetch(A_prefetch_m, L2);
			A_prefetch_m += CACHE_LINE;
		}
		A_prefetch += m;
	}
}