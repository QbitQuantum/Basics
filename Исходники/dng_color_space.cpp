void dng_color_space::SetMatrixToPCS (const dng_matrix_3by3 &M)
	{
	
	// The matrix values are often rounded, so adjust to
	// get them to convert device white exactly to the PCS.
	
	dng_vector_3 W1 = M * dng_vector_3 (1.0, 1.0, 1.0);
	dng_vector_3 W2 = PCStoXYZ ();
	
	real64 s0 = W2 [0] / W1 [0];
	real64 s1 = W2 [1] / W1 [1];
	real64 s2 = W2 [2] / W1 [2];
	
	dng_matrix_3by3 S (s0,  0,  0,
				   		0, s1,  0,
				   		0,  0, s2);
	
	fMatrixToPCS = S * M;
	
	// Find reverse matrix.
	
	fMatrixFromPCS = Invert (fMatrixToPCS);
	
	}