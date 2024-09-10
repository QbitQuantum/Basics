/**
 * Multiply Matrices A & B to the Matrix C.
 * the sizes of A,B and C are:
 * -----------------
 * A		M * K
 * B		K * N
 * C		M * N
 * -----------------
 * Matrix C should be allocated outside.
 * Matrix C will not be cleared in this function, thus you can add new result to the Matrix C.
 */
void highEfficentMatrixMultiply(float* C, float* A, float* B, int M, int K, int N)
{
	int i,j,k;
	float tmp[16] __attribute__((align(64)));
//#pragma omp parallel for private(j,k) num_threads(THREAD_NUM)
	for(i=0; i < M; i++)
	{
		/* Code Run on Xeon Phi */
		#ifdef __MIC__
		__m512 _A,_B,_C;
		for(k = 0; k < K; k++)
		{
			_A = _mm512_set_1to16_ps(A[i*K + k]);
			/*
			_mm512_packstorelo_ps((void*)&tmp,_A);
			_mm512_packstorehi_ps((char*)&tmp + 64,_A);
			for(int s = 0 ; s < 16; s++)
				fprintf(stderr,"%f ",tmp[s]);
			*/
			//for(j = 0; j < N/16; j += 16)
			for(j = 0; j+16 < N; j += 16)
			{
				//fprintf(stderr,"[i,k,j,A[i,k]]=[%d,%d,%d,%f]\n",i,k,j,A[i*K+k]);
				_B = _mm512_loadunpacklo_ps(_B,(void*)(&B[k*N + j]));
				_B = _mm512_loadunpackhi_ps(_B,(void*)(&B[k*N + j + 16]));
				_C = _mm512_loadunpacklo_ps(_C,(void*)(&C[i*N + j]));
				_C = _mm512_loadunpackhi_ps(_C,(void*)(&C[i*N + j + 16]));

				_mm512_packstorelo_ps((void*)&tmp,_C);
				_mm512_packstorehi_ps((char*)&tmp + 64,_C);
				
				/*
				fprintf(stderr,"_C=\n");
				for(int s = 0 ; s < 4; s++)
					fprintf(stderr,"%f ",tmp[s]);
				fprintf(stderr,"\n");
				*/
				

				_C = _mm512_add_ps(_C,_mm512_mul_ps(_A,_B));
				_mm512_packstorelo_ps((void*)(&C[i*N+j]),_C);
				_mm512_packstorehi_ps((void*)(&C[i*N+j+16]),_C);

				
				/*
				_mm512_packstorelo_ps((void*)&tmp,_C);
				_mm512_packstorehi_ps((char*)&tmp + 64,_C);
				
				for(int s = 0 ; s < 4; s++)
					fprintf(stderr,"%f ",tmp[s]);
				fprintf(stderr,"\n");
				*/
				
			}
			if (j+16 > N)
			{
				
//				fprintf(stderr,"[j=%d]\n",j);
				//We should deal with the tail in each row
				float temp = A[i*K + k];
				#pragma ivdep 
				for(; j < N; j++)
					C[i*N + j] += temp * B[k*N + j];
					
			}



		}	
		
		#else
		/* Code Run On Xeon */
		for(k = 0; k < K; k++)
		{
			float temp = A[i*K + k];
			#pragma ivdep
			for(j = 0; j < N; j++)
			{
				C[i*N + j] += temp * B[k*N + j];
			}
		}
	#endif
	}
}