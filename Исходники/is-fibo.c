int IsFib(long long T)
{
    double root5 = sqrt(5);	
    double phi = (1 + root5) / 2;
		long long u;
  	long long idx;

    idx    = (long) floorl( logl(T*root5) / logl(phi) + 0.5 );
    u = (long) floorl( powl(phi, idx)/root5 + 0.5);
    return (u == T);
}