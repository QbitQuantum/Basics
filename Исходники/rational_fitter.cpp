/**
 * Take as input the full constraint matrix CI for a dimension ny, and
 * the associated ci vector with the 2-norm of each row scaled by delta.
 * Apply the quadratic program and test against all the constraints.
 * Return true if all constraints match, false otherwise.
 */
int rational_fitter_parsec_multi::solve_wrapper( const gesvdm2_args_t *args, subproblem_t *pb, int M, int ny,
						 double *CIptr, double *ciptr )
{
    const vertical_segment *d    = (const vertical_segment*)(args->dataptr);
    rational_function      *rf   = (rational_function*)(pb->rfptr);
    rational_function_1d   *rf1d = rf->get(ny);
    const int np = pb->np;
    const int nq = pb->nq;
    const int N  = np + nq;

    // Compute the solution
    Eigen::MatrixXd CE(N, 0);
    Eigen::VectorXd ce(0);
    Eigen::MatrixXd G (N, N); G.setIdentity();
    Eigen::VectorXd g (N); g.setZero();
    Eigen::VectorXd x (0.0, N);

    Eigen::MatrixXd CI = Eigen::Matrix<double,Eigen::Dynamic,Eigen::Dynamic,Eigen::RowMajor>::Map(CIptr, N, M);
    Eigen::Map<Eigen::VectorXd> ci(ciptr, M);

    // Select the size of the result vector to
    // be equal to the dimension of p + q
    double cost = QuadProgPP::solve_quadprog(G, g, CE, ce, CI, ci, x);
    bool solves_qp = !(cost == std::numeric_limits<double>::infinity());

    if(solves_qp) {
	std::cout << "<<INFO>> got solution for pb with np=" << pb->np << ", nq=" << pb->nq << std::endl;

	// Recopy the vector d
	vec p(np), q(nq);
	double norm = 0.0;

	for(int i=0; (i<N) & solves_qp; ++i) {
	    const double v = x[i];

	    solves_qp = solves_qp && !isnan(v)
		&& (v != std::numeric_limits<double>::infinity());

	    norm += v*v;
	    if(i < np) {
		p[i] = v;
	    }
	    else {
		q[i - np] = v;
	    }
	}

	if (solves_qp) {
	    std::cout << "<<INFO>> got solution to second step for pb with np=" << pb->np << ", nq=" << pb->nq << std::endl;

	    // Rq: doesn't need protection in // since it should be working on independant vectors
	    rf1d->update(p, q);
	    solves_qp = (test_all_constraint( d, rf1d, ny ) == 1);
	}
    }
    else {
	std::cerr << "<<DEBUG>> Didn't get solution to the pb with np=" << pb->np << ", nq=" << pb->nq << std::endl;
    }

    return solves_qp;
}