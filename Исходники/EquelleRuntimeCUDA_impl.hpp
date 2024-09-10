CollOfScalar EquelleRuntimeCUDA::newtonSolve(const ResidualFunctor& rescomp,
                                            const CollOfScalar& u_initialguess)
{
    Opm::time::StopWatch clock;
    clock.start();

    // Set up Newton loop.
 
    // Define the primary variable
    CollOfScalar u = CollOfScalar(u_initialguess, true);
 
    if (verbose_ > 2) {
        output("Initial u", u);
        output("    newtonSolve: norm (initial u)", twoNorm(u));
    }
    CollOfScalar residual = rescomp(u);   
    if (verbose_ > 2) {
        output("Initial residual", residual);
        output("    newtonSolve: norm (initial residual)", twoNorm(residual));
    }

    int iter = 0;

    // Debugging output not specified in Equelle.
    if (verbose_ > 1) {
        std::cout << "    newtonSolve: iter = " << iter << " (max = " << max_iter_
		  << "), norm(residual) = " << twoNorm(residual)
                  << " (tol = " << abs_res_tol_ << ")" << std::endl;
    }

    CollOfScalar du;

    // Execute newton loop until residual is small or we have used too many iterations.
    while ( (twoNorm(residual) > abs_res_tol_) && (iter < max_iter_) ) {
	
	if ( solver_.getSolver() == CPU ) {
	    du = serialSolveForUpdate(residual);
	}
	else {
	    // Solve linear equations for du, apply update.
	    du = solver_.solve(residual.derivative(),
			       residual.value(),
			       verbose_);
	}

	// du is a constant, hence, u is still a primary variable with an identity
	// matrix as its derivative.
	u = u - du;

        // Recompute residual.
        residual = rescomp(u);

        if (verbose_ > 2) {
            // Debugging output not specified in Equelle.
            output("u", u);
            output("    newtonSolve: norm(u)", twoNorm(u));
            output("residual", residual);
            output("    newtonSolve: norm(residual)", twoNorm(residual));
        }

        ++iter;

        // Debugging output not specified in Equelle.
        if (verbose_ > 1) {
            std::cout << "    newtonSolve: iter = " << iter << " (max = " << max_iter_
		      << "), norm(residual) = " << twoNorm(residual)
                      << " (tol = " << abs_res_tol_ << ")" << std::endl;
        }

    }
    if (verbose_ > 0) {
        if (twoNorm(residual) > abs_res_tol_) {
            std::cout << "Newton solver failed to converge in " << max_iter_ << " iterations" << std::endl;
        } else {
            std::cout << "Newton solver converged in " << iter << " iterations" << std::endl;
        }
    }

    if (verbose_ > 1) {
        std::cout << "Newton solver took: " << clock.secsSinceLast() << " seconds." << std::endl;
    }

    return CollOfScalar(u.value());
}