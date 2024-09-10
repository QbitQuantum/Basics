int
main (int argc, char **argv)
{
	struct experiment_params params;
	double dx, dy;
	double speed, angle;
	gsl_vector *solution;
	int c;
	double compute_start, delta;

	while ((c = getopt (argc, argv, "v")) != EOF) {
		switch (c) {
		case 'v':
			vflag = 1;
			break;
		default:
			usage ();
		}
	}


	memset (&params, 0, sizeof params);
	params.observed_hit[0] = 0;
	params.observed_hit[1] = 0;
	params.observed_hit[2] = 1;
	params.observed_bounce[0] = 25;
	params.observed_bounce[1] = 0;
	params.observed_bounce[2] = 0;
	params.observed_secs = 1.359;

	dx = params.observed_bounce[0] - params.observed_hit[0];
	dy = params.observed_bounce[1] - params.observed_hit[1];
	params.observed_dist = hypot (dy, dx);

	params.simulator_dimen = 4;

	params.odesys.function = sim_func;
	params.odesys.dimension = params.simulator_dimen;
	params.odesys.params = &params;

	params.stepper = gsl_odeiv_step_alloc (gsl_odeiv_step_rk8pd,
					       params.simulator_dimen);
	params.controller = gsl_odeiv_control_y_new (1e-6, 0.0);
	params.evolver = gsl_odeiv_evolve_alloc (params.simulator_dimen);
	
	params.minimizer_dimen = 2;
	params.starting_point = gsl_vector_alloc (params.minimizer_dimen);

	params.minimizer_step_sizes = gsl_vector_alloc (params.minimizer_dimen);
	params.minimizer = gsl_multimin_fminimizer_alloc
		(gsl_multimin_fminimizer_nmsimplex2, params.minimizer_dimen);

       gsl_vector_set_all (params.starting_point, 0);
       gsl_vector_set_all (params.minimizer_step_sizes, 1.0);
     
	if (0) {
		graph_error_func (&params);
	}

	compute_start = get_secs ();
	solve_by_simulation (&params);
	delta = get_secs () - compute_start;

	solution = gsl_multimin_fminimizer_x (params.minimizer);

	speed = gsl_vector_get (solution, 0);
	angle = gsl_vector_get (solution, 1);

	printf ("speed = %8.3f angle = %8.3f; compute time %.3fms\n",
		speed * METERS_PER_SEC_TO_MPH,
		RTOD (angle),
		delta * 1000);

	return (0);
}