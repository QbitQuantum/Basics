/*-------------------------------------------------------------------*/	
bool DPMatchingMultiStart (	int *C, double &T_best,		// output
							double *A, double thre,		// input
							int	M, int N,				// A is MxN matrix
							int	n_start,
							int n_search)
{
	double *A2	= new double[M*2*N];
	bool bSucc	= false;
	memcpy(A2,A,M*N*sizeof(double));
	memcpy(A2+M*N,A,M*N*sizeof(double));

	int		*CC	= new int[M*N];
	double	TT;
	int		id_best;

	id_best		= -1;
	T_best		= 4000*N;
	n_start	= MIN(N,n_start);

	// try different start points
	int	id_start, iS, iS1, iS2, dS;
	for(iS=0;iS<n_start;++iS)
	{
		id_start	= ROUND(N*iS/(double)n_start);
		bSucc		= DPMatchingFixStartPoint(CC+id_start*M, TT, A2+id_start*M, thre, M, N);
		if(TT<T_best) {
			T_best 	= TT;
			id_best	= id_start;
		}

		for(dS=1;dS<n_search;++dS)	
		{
			// forward
			iS1	= id_start+dS;
			if(iS1>N)	iS1-=N;
			bSucc = DPMatchingFixStartPoint(CC+iS1*M, TT, A2+iS1*M, thre, M, N);
			if(TT<T_best) {
				T_best 	= TT;
				id_best	= iS1;
			}
		
			// backward
			iS2	= id_start-dS;
			if(iS2<0)	iS2+=N;
			bSucc	= DPMatchingFixStartPoint(CC+iS2*M, TT, A2+iS2*M, thre, M, N);
			if(TT<T_best) {
				T_best 	= TT;
				id_best	= iS2;
			}
		}
	}

	// adjust indices 
	if(id_best<0)	printf("\n\tId_best=%d !!!!!!!\n",id_best);

	memcpy(C,CC+id_best*M,M*sizeof(int));				
	for(int ii=0;ii<M;++ii)
	{
		if(C[ii]<N)	{		// not occluded
			C[ii] += id_best;
			if(C[ii]>=N)	C[ii] -= N;
		}
	}

	delete	[]A2;
	delete	[]CC;
	return true;
}