dng_matrix Invert (const dng_matrix &A)
	{
	
	if (A.Rows () < 2 || A.Cols () < 2)
		{
		
		ThrowMatrixMath ();
						 
		}
	
	if (A.Rows () == A.Cols ())
		{
		
		if (A.Rows () == 3)
			{
			
			return Invert3by3 (A);
			
			}
			
		return InvertNbyN (A);
		
		}
		
	else
		{
		
		// Compute the pseudo inverse.
	
		dng_matrix B = Transpose (A);
	
		return Invert (B * A) * B;
		
		}
		
	}