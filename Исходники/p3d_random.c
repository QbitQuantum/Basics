double p3d_random(double a, double b)
{double v;
	
	// C library implementation
	// v =  rand()/((double)RAND_MAX+1); /* nombre aleatoire [0.,1.] */
	v = mersenne_twister_rng.rand();
	v = (b-a)*v + a;
	return(v);
}