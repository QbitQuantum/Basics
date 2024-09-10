// return the objective value
CUDFcoefficient cplex_solver::objective_value() { 
	double objval;
	int  status = CPXgetobjval (env, lp, &objval);
	if (status) {
		fprintf (stderr,"No MIP objective value available.  Exiting...\n");
		exit(-1);
	}
	//  printf("Objective value = % 24.24e\n", objval);
	return (CUDFcoefficient)nearbyint(objval);
}