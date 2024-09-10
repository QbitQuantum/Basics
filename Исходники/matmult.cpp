/*
Naive implementation of Matrix Matrix Multiplication

@param A input matrix
@param B input matrix
@param C output matrix
*/
inline
void	naive(const Matrix& A, const Matrix& B, Matrix& C){
	//preload dimensions for faster access
	int dimM = C.getDimM();
	int dimN = C.getDimN();
	int dimL = A.getDimN();
	
	for (int m = 0; m < dimM; m+=4){				///rows of c
		for (int n = 0; n < dimN; n+=4){			///cols of c	
			//do calculation of a 4x4 block
			//std::cout << m << "\t" << n << std::endl;
			__m256d*	pA = A.get(m, 0);
			__m256d*	pB = A.get(m+1, 0);
			__m256d*	pC = A.get(m+2, 0);
			__m256d*	pD = A.get(m+3, 0);
			__m256d*	pK = B.getT(0, n);
			__m256d*	pL = B.getT(0, n+1);
			__m256d*	pM = B.getT(0, n+2);
			__m256d*	pN = B.getT(0, n+3);
			//std::cout << pA << "\t" << pB << "\t" << pC << "\t" << pD << std::endl;
			__m256d		K = _mm256_setzero_pd();
			__m256d		L = _mm256_setzero_pd();
			__m256d		M = _mm256_setzero_pd();
			__m256d		N = _mm256_setzero_pd();
			__m256d		O = _mm256_setzero_pd();
			__m256d		P = _mm256_setzero_pd();
			__m256d		Q = _mm256_setzero_pd();
			__m256d		R = _mm256_setzero_pd();
			__m256d		S = _mm256_setzero_pd();
			__m256d		T = _mm256_setzero_pd();
			__m256d		U = _mm256_setzero_pd();
			__m256d		V = _mm256_setzero_pd();
			__m256d		W = _mm256_setzero_pd();
			__m256d		X = _mm256_setzero_pd();
			__m256d		Y = _mm256_setzero_pd();
			__m256d		Z = _mm256_setzero_pd();
			for (int l = 0; l < dimL; l+=4){
				//std::cout <<"mul" << std::endl;
				K = K + (*pA) * (*pK);
				L = L + (*pA) * (*pL);
				M = M + (*pA) * (*pM);
				N = N + (*pA) * (*pN);
				O = O + (*pB) * (*pK);
				P = P + (*pB) * (*pL);
				Q = Q + (*pB) * (*pM);
				R = R + (*pB) * (*pN);
				S = S + (*pC) * (*pK);
				T = T + (*pC) * (*pL);
				U = U + (*pC) * (*pM);
				V = V + (*pC) * (*pN);
				W = W + (*pD) * (*pK);
				X = X + (*pD) * (*pL);
				Y = Y + (*pD) * (*pM);
				Z = Z + (*pD) * (*pN);
				//std::cout << "inc" <<std::endl;
				pA++;
				pB++;
				pC++;
				pD++;
				pK++;
				pL++;
				pM++;
				pN++;
			}
			// {a[0]+a[1], b[0]+b[1], a[2]+a[3], b[2]+b[3]}
			__m256d sumab = _mm256_hadd_pd(K, L);
			// {c[0]+c[1], d[0]+d[1], c[2]+c[3], d[2]+d[3]}
			__m256d sumcd = _mm256_hadd_pd(M, N);

			// {a[0]+a[1], b[0]+b[1], c[2]+c[3], d[2]+d[3]}
			__m256d blend = _mm256_blend_pd(sumab, sumcd, 0b1100);
			// {a[2]+a[3], b[2]+b[3], c[0]+c[1], d[0]+d[1]}
			__m256d perm = _mm256_permute2f128_pd(sumab, sumcd, 0x21);

			__m256d sum =  _mm256_add_pd(perm, blend);

			C.set(m, n, sum);
			//C(m  , n)     = K[0] + K[1] + K[2] + K[3];
			//C(m  , n+1)   = L[0] + L[1] + L[2] + L[3];
			//C(m  , n+2)   = M[0] + M[1] + M[2] + M[3];
			//C(m  , n+3)   = N[0] + N[1] + N[2] + N[3];

			// {a[0]+a[1], b[0]+b[1], a[2]+a[3], b[2]+b[3]}
			sumab = _mm256_hadd_pd(O, P);
			// {c[0]+c[1], d[0]+d[1], c[2]+c[3], d[2]+d[3]}
			sumcd = _mm256_hadd_pd(Q, R);

			// {a[0]+a[1], b[0]+b[1], c[2]+c[3], d[2]+d[3]}
			blend = _mm256_blend_pd(sumab, sumcd, 0b1100);
			// {a[2]+a[3], b[2]+b[3], c[0]+c[1], d[0]+d[1]}
			perm = _mm256_permute2f128_pd(sumab, sumcd, 0x21);

			sum =  _mm256_add_pd(perm, blend);
			
			C.set(m+1, n, sum);
			//C(m+1, n  )   = O[0] + O[1] + O[2] + O[3];
			//C(m+1, n+1)   = P[0] + P[1] + P[2] + P[3];
			//C(m+1, n+2)   = Q[0] + Q[1] + Q[2] + Q[3];
			//C(m+1, n+3)   = R[0] + R[1] + R[2] + R[3];
			
			// {a[0]+a[1], b[0]+b[1], a[2]+a[3], b[2]+b[3]}
			sumab = _mm256_hadd_pd(S, T);
			// {c[0]+c[1], d[0]+d[1], c[2]+c[3], d[2]+d[3]}
			sumcd = _mm256_hadd_pd(U, V);

			// {a[0]+a[1], b[0]+b[1], c[2]+c[3], d[2]+d[3]}
			blend = _mm256_blend_pd(sumab, sumcd, 0b1100);
			// {a[2]+a[3], b[2]+b[3], c[0]+c[1], d[0]+d[1]}
			perm = _mm256_permute2f128_pd(sumab, sumcd, 0x21);

			sum =  _mm256_add_pd(perm, blend);
			
			C.set(m+2, n, sum);
			//C(m+2, n  )   = S[0] + S[1] + S[2] + S[3];
			//C(m+2, n+1)   = T[0] + T[1] + T[2] + T[3];
			//C(m+2, n+2)   = U[0] + U[1] + U[2] + U[3];
			//C(m+2, n+3)   = V[0] + V[1] + V[2] + V[3];
			
			// {a[0]+a[1], b[0]+b[1], a[2]+a[3], b[2]+b[3]}
			sumab = _mm256_hadd_pd(W, X);
			// {c[0]+c[1], d[0]+d[1], c[2]+c[3], d[2]+d[3]}
			sumcd = _mm256_hadd_pd(Y, Z);

			// {a[0]+a[1], b[0]+b[1], c[2]+c[3], d[2]+d[3]}
			blend = _mm256_blend_pd(sumab, sumcd, 0b1100);
			// {a[2]+a[3], b[2]+b[3], c[0]+c[1], d[0]+d[1]}
			perm = _mm256_permute2f128_pd(sumab, sumcd, 0x21);

			sum =  _mm256_add_pd(perm, blend);
			
			C.set(m+3, n, sum);
			
			//C(m+3, n  )   = W[0] + W[1] + W[2] + W[3];
			//C(m+3, n+1)   = X[0] + X[1] + X[2] + X[3];
			//C(m+3, n+2)   = Y[0] + Y[1] + Y[2] + Y[3];
			//C(m+3, n+3)   = Z[0] + Z[1] + Z[2] + Z[3];
		}
	}
}