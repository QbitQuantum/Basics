    void EulerUpstream<GI, RP, BC>::transportSolve(std::vector<double>& saturation,
						   const double time,
						   const typename GI::Vector& gravity,
						   const PressureSolution& pressure_sol,
						   const Opm::SparseVector<double>& injection_rates) const
    {
	// Compute the cfl time-step.
	double cfl_dt = computeCflTime(saturation, time, gravity, pressure_sol);

	// Compute the number of small steps to take, and the actual small timestep.
	int nr_transport_steps;
	if (cfl_dt > time){
	    nr_transport_steps = minimum_small_steps_;
	} else {
            double steps = std::min<double>(std::ceil(time/cfl_dt), std::numeric_limits<int>::max());
            nr_transport_steps = int(steps);
	    nr_transport_steps = std::max(nr_transport_steps, minimum_small_steps_);
            nr_transport_steps = std::min(nr_transport_steps, maximum_small_steps_);
	}
	double dt_transport = time/nr_transport_steps;

	// Do the timestepping. The try-catch blocks are there to handle
	// the situation that smallTimeStep throws, which may happen due
	// to saturation out of bounds (if check_sat_ is true).
	// We cannot guarantee that this does not happen, since we do not
	// (yet) compute a capillary cfl condition.
	// Using exception for "alternate control flow" like this is bad
	// design, should rather use error return values for this.
	std::vector<double> saturation_initial(saturation);
	bool finished = false;
	int repeats = 0;
	const int max_repeats = 10;
	Opm::time::StopWatch clock;
        clock.start();
	while (!finished) {
	    try {
#ifdef VERBOSE
		std::cout << "Doing " << nr_transport_steps
			  << " steps for saturation equation with stepsize "
			  << dt_transport << " in seconds." << std::endl;
#endif // VERBOSE
		for (int q = 0; q < nr_transport_steps; ++q) {
		    smallTimeStep(saturation,
				  dt_transport,
				  gravity,
				  pressure_sol,
                                  injection_rates);
		}
		finished = true;
	    }
	    catch (...) {
		++repeats;
		if (repeats > max_repeats) {
		    throw;
		}
		OPM_MESSAGE("Warning: Transport failed, retrying with more steps.");
		nr_transport_steps *= 2;
		dt_transport = time/nr_transport_steps;
		saturation = saturation_initial;
	    }
	}
        clock.stop();
#ifdef VERBOSE
        std::cout << "Seconds taken by transport solver: " << clock.secsSinceStart() << std::endl;
#endif // VERBOSE
    }