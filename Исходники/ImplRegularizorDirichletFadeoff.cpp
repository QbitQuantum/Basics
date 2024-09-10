//-------------------------------------------------------------------------------------------------------
// calculate the logarithm of the beta-function for sum of two vectors. In Kimmens script |x| is
// defined as sum_xi, so |x| + |y| = | x + y | !!
// the first vector is an int
static double lBetaSum ( const Count * vector1, 
			 const Count length1, 
			 const double *vector2, 
			 const Count length2) {
    double result = 0;
    int i;
    
    for (i = 0; i < ALPHABET_SIZE; i++)
	result += lgamma( vector1[i] + vector2[i]);
    
    return (result - lgamma( length1 + length2 ));
}