void gesture_maker_multipart_timings(t_gesture_multipart *x, long argc, t_atom *argv)
{
	long num_splits;
	double *split_points = x->split_points;
	
	if (argc > MAX_NUM_SPLITS)
		argc = MAX_NUM_SPLITS;
	
	num_splits = argc;
	
	while (argc--)
		*split_points++ = nextafterf(atom_getfloat(argv++), -1.);		// There may be a better way to do this that brings us closer to the desired value

	x->num_splits = num_splits;
	x->force_output = true;
}