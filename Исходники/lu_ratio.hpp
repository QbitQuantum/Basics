int LuRatio(SizeVector &ip, SizeVector &jp, ADvector &LU, AD<Base> &ratio) //
{
	typedef ADvector FloatVector;                                       //
	typedef AD<Base>       Float;                                       //

	// check numeric type specifications
	CheckNumericType<Float>();

	// check simple vector class specifications
	CheckSimpleVector<Float, FloatVector>();
	CheckSimpleVector<size_t, SizeVector>();

	size_t  i, j;          // some temporary indices
	const Float zero( 0 ); // the value zero as a Float object
	size_t  imax;          // row index of maximum element
	size_t  jmax;          // column indx of maximum element
	Float    emax;         // maximum absolute value
	size_t  p;             // count pivots
	int     sign;          // sign of the permutation
	Float   etmp;          // temporary element
	Float   pivot;         // pivot element

	// -------------------------------------------------------
	size_t n = size_t(ip.size());
	CPPAD_ASSERT_KNOWN(
		size_t(jp.size()) == n,
		"Error in LuFactor: jp must have size equal to n"
	);
	CPPAD_ASSERT_KNOWN(
		size_t(LU.size()) == n * n,
		"Error in LuFactor: LU must have size equal to n * m"
	);
	// -------------------------------------------------------

	// initialize row and column order in matrix not yet pivoted
	for(i = 0; i < n; i++)
	{	ip[i] = i;
		jp[i] = i;
	}
	// initialize the sign of the permutation
	sign = 1;
	// initialize the ratio                                             //
	ratio = Float(1);                                                   //
	// ---------------------------------------------------------

	// Reduce the matrix P to L * U using n pivots
	for(p = 0; p < n; p++)
	{	// determine row and column corresponding to element of
		// maximum absolute value in remaining part of P
		imax = jmax = n;
		emax = zero;
		for(i = p; i < n; i++)
		{	for(j = p; j < n; j++)
			{	CPPAD_ASSERT_UNKNOWN(
					(ip[i] < n) & (jp[j] < n)
				);
				etmp = LU[ ip[i] * n + jp[j] ];

				// check if maximum absolute value so far
				if( AbsGeq (etmp, emax) )
				{	imax = i;
					jmax = j;
					emax = etmp;
				}
			}
		}
		for(i = p; i < n; i++)                                       //
		{	for(j = p; j < n; j++)                               //
			{	etmp  = abs(LU[ ip[i] * n + jp[j] ] / emax); //
				ratio =                                      //
				CondExpGt(etmp, ratio, etmp, ratio);         //
			}                                                    //
		}                                                            //
		CPPAD_ASSERT_KNOWN(
			(imax < n) & (jmax < n) ,
			"AbsGeq must return true when second argument is zero"
		);
		if( imax != p )
		{	// switch rows so max absolute element is in row p
			i        = ip[p];
			ip[p]    = ip[imax];
			ip[imax] = i;
			sign     = -sign;
		}
		if( jmax != p )
		{	// switch columns so max absolute element is in column p
			j        = jp[p];
			jp[p]    = jp[jmax];
			jp[jmax] = j;
			sign     = -sign;
		}
		// pivot using the max absolute element
		pivot   = LU[ ip[p] * n + jp[p] ];

		// check for determinant equal to zero
		if( pivot == zero )
		{	// abort the mission
			return   0;
		}

		// Reduce U by the elementary transformations that maps
		// LU( ip[p], jp[p] ) to one.  Only need transform elements
		// above the diagonal in U and LU( ip[p] , jp[p] ) is
		// corresponding value below diagonal in L.
		for(j = p+1; j < n; j++)
			LU[ ip[p] * n + jp[j] ] /= pivot;

		// Reduce U by the elementary transformations that maps
		// LU( ip[i], jp[p] ) to zero. Only need transform elements
		// above the diagonal in U and LU( ip[i], jp[p] ) is
		// corresponding value below diagonal in L.
		for(i = p+1; i < n; i++ )
		{	etmp = LU[ ip[i] * n + jp[p] ];
			for(j = p+1; j < n; j++)
			{	LU[ ip[i] * n + jp[j] ] -=
					etmp * LU[ ip[p] * n + jp[j] ];
			}
		}
	}
	return sign;
}