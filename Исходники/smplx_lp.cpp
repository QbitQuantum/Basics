void SimplexLP::GetPenaltyEstimates( Real_T &MinM, Real_T &MaxM )
{
	//--------------------------------------------------------------------------
	//	Estimate the minimum penalty.
	//
	MaxM = -INFINITY;	// "Guarantees" that the problem will not be unbounded.
	MinM = +INFINITY;	// Guarantees that the problem will be unbounded.

	Ptr<Real_T> a;
	Ptr<Int_T> row;
	Int_T j, len, nn = GetStructN();

	for( j = 0; j < nn; j++ )
	{
		Real_T x = 0.0;

		for( GetColumn( j, a, row, len ); len; --len, ++a, ++row )
			if( ! ( LambdaVT[ *row ] & VT_FX ) )
				x += Lambda[ *row ] * *a;

		if( IsNonZero( x ) )
		{
			x = GetC( j ) / x;

			if( MaxM < x ) MaxM = x;
			if( MinM > x ) MinM = x;
		}
	}
}