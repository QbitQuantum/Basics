dng_matrix_3by3 MapWhiteMatrix (const dng_xy_coord &white1,
						        const dng_xy_coord &white2)
	{
	
	// Use the linearized Bradford adaptation matrix.
	
	dng_matrix_3by3 Mb ( 0.8951,  0.2664, -0.1614,
		 		        -0.7502,  1.7135,  0.0367,
		  			     0.0389, -0.0685,  1.0296);
	
	dng_vector_3 w1 = Mb * XYtoXYZ (white1);
	dng_vector_3 w2 = Mb * XYtoXYZ (white2);
	
	// Negative white coordinates are kind of meaningless.
	
	w1 [0] = Max_real64 (w1 [0], 0.0);
	w1 [1] = Max_real64 (w1 [1], 0.0);
	w1 [2] = Max_real64 (w1 [2], 0.0);
	
	w2 [0] = Max_real64 (w2 [0], 0.0);
	w2 [1] = Max_real64 (w2 [1], 0.0);
	w2 [2] = Max_real64 (w2 [2], 0.0);

	// Limit scaling to something reasonable.
	
	dng_matrix_3by3 A;
	
	A [0] [0] = Pin_real64 (0.1, w1 [0] > 0.0 ? w2 [0] / w1 [0] : 10.0, 10.0);
	A [1] [1] = Pin_real64 (0.1, w1 [1] > 0.0 ? w2 [1] / w1 [1] : 10.0, 10.0);
	A [2] [2] = Pin_real64 (0.1, w1 [2] > 0.0 ? w2 [2] / w1 [2] : 10.0, 10.0);
		
	dng_matrix_3by3 B = Invert (Mb) * A * Mb;
	
	return B;
	
	}