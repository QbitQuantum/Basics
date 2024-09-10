void matrix::pivot(matrix &a, vector &b, vector &x, int h){
	int n = a.getrows();
	int g = h;
	double t = 0;
	for (int k = h; k<n; ++k)
	{
		double elm = fabs(a[k][h]);  //finds the largest value in the column, the "pivot".
		if (elm > t) { t = elm; g = k; }
	}
	if (g > h)
	{
		a.swap(h, g);
		b.swap(h, g);
		x.swap(h, g);  //this is to swap the entries of the X vector, so that we can keep track of the solution properly.  This may not be useful in this example because x2 to xN are all zero, but in general it would be useful.  
	}
}