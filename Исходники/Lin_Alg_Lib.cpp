void lin_alg::row_reduce(double **A, double *b, double **Aug, int *nrow, int rows, bool pivoting)
{
	// This function takes a square matrix A, rhs vector b and performs
	// a row reduction on the augmented matrix Aug = [A:b]
	// The augmented matrix should be in upper triangular form at the end of the function

	// Use these variables to determine the max pivot element
	int piv_indx;
	double pivot,pivcomp;
	double m; // row multiplier 

	// 1. Use Aug to store the elements of A and b
	for(int i=1; i<=rows; i++){
		for(int j=1; j<=rows; j++){
			Aug[i][j] = A[i][j]; 
		}
	}
	
	// 2. Add the rhs vector to the last column
	for(int i=1; i<=rows; i++){
		Aug[i][rows+1] = b[i]; 
	}

	// 3. Store the index of each of the rows as they are entered in the matrix
	// This will be used to keep track of the row interchanges
	for(int i=1; i<=rows; i++){
		nrow[i] = i; 
	}

	// Main loop	
	for(int i=1; i<=rows-1; i++){	

		// Choose the pivot element
		// Search column i for the largest value by absolute value
		pivot = 0.0; 

		for(int k=i; k <= rows; k++){

			pivcomp = fabs(Aug[ nrow[k] ][i]); 
			
			// This is the search portion
			if(pivcomp > fabs(pivot)){
				pivot = pivcomp; // store the pivot element
				piv_indx = k; 
			}

		}
		
		// simulate a row interchange if required
		if(pivoting && !(nrow[i] == nrow[piv_indx])){
			SWAP(nrow[i], nrow[piv_indx]);
		}

		// Perform the ERO 
		for(int j=i+1; j<=rows; j++){

			m = (Aug[ nrow[j] ][i] / Aug[ nrow[i] ][i]); // Compute the row multiplier, the computer accesses the pivot numer via nrow

			for(int c = 1; c<= rows+1; c++){
				Aug[ nrow[j] ][c] = Aug[ nrow[j] ][c] -( m * Aug[ nrow[i] ][c] ); // perform the ERO
			}
		}

	}
}