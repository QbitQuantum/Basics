    void ImplicitCapillarity<GI, RP, BC, IP>::transportSolve(std::vector<double>& saturation,
                                                             const double /*time*/,
                                                             const typename GI::Vector& gravity,
                                                             const PressureSolution& pressure_sol,
                                                             const Opm::SparseVector<double>& injection_rates) const
    {
        // Start a timer.
	Opm::time::StopWatch clock;
        clock.start();

        // Compute capillary mobilities.
        typedef typename RP::Mobility Mob;
        int num_cells = saturation.size();
        std::vector<Mob> cap_mob(num_cells);
        for (int c = 0; c < num_cells; ++c) {
            Mob& m = cap_mob[c];
            residual_.reservoirProperties().phaseMobility(0, c, saturation[c], m.mob);
            Mob mob2;
            residual_.reservoirProperties().phaseMobility(1, c, saturation[c], mob2.mob);
            Mob mob_tot;
            mob_tot.setToSum(m, mob2);
            Mob mob_totinv;
            mob_totinv.setToInverse(mob_tot);
            m *= mob_totinv;
            m *= mob2;
            ImplicitCapillarityDetails::thresholdMobility(m.mob, 1e-10); // @@TODO: User-set limit.
            // std::cout << m.mob(0,0) << '\n';
        }
        ReservoirPropertyFixedMobility<Mob> capillary_mobilities(cap_mob);

        // Set up boundary conditions.
        BC cap_press_bcs(residual_.boundaryConditions());
        for (int i = 0; i < cap_press_bcs.size(); ++i) {
            if (cap_press_bcs.flowCond(i).isPeriodic()) {
                cap_press_bcs.flowCond(i) = FlowBC(FlowBC::Periodic, 0.0);
            }
        }

        // Compute injection rates from residual.
        std::vector<double> injection_rates_residual(num_cells);
	residual_.computeResidual(saturation, gravity, pressure_sol, injection_rates,
                                  method_viscous_, method_gravity_, false,
                                  injection_rates_residual);
        for (int i = 0; i < num_cells; ++i) {
            injection_rates_residual[i] = -injection_rates_residual[i];
        }

        // Compute capillary pressure.
        // Note that the saturation is just a dummy for this call, since the mobilities are fixed.
        psolver_.solve(capillary_mobilities, saturation, cap_press_bcs, injection_rates_residual,
                       residual_tolerance_, linsolver_verbosity_, linsolver_type_);

        // Solve for constant to change capillary pressure solution by.
        std::vector<double> cap_press(num_cells);
        const PressureSolution& pcapsol = psolver_.getSolution();
        for (CIt c = residual_.grid().cellbegin(); c != residual_.grid().cellend(); ++c) {
            cap_press[c->index()] = pcapsol.pressure(c);
        }
        MatchSaturatedVolumeFunctor<GI, RP> functor(residual_.grid(),
                                                    residual_.reservoirProperties(),
                                                    saturation,
                                                    cap_press);
        double min_cap_press = *std::min_element(cap_press.begin(), cap_press.end());
        double max_cap_press = *std::max_element(cap_press.begin(), cap_press.end());
        double cap_press_range = max_cap_press - min_cap_press;
        double mod_low = 1e100;
        double mod_high = -1e100;
	Opm::bracketZero(functor, 0.0, cap_press_range, mod_low, mod_high);
        const int max_iter = 40;
        const double nonlinear_tolerance = 1e-12;
        int iterations_used = -1;
        typedef Opm::RegulaFalsi<Opm::ThrowOnError> RootFinder;
        double mod_correct = RootFinder::solve(functor, mod_low, mod_high, max_iter, nonlinear_tolerance, iterations_used);
        std::cout << "Moved capillary pressure solution by " << mod_correct << " after "
                  << iterations_used << " iterations." << std::endl;
        // saturation = functor.lastSaturations();
        const std::vector<double>& sat_new = functor.lastSaturations();
        for (int i = 0; i < num_cells; ++i) {
            saturation[i] = (1.0 - update_relaxation_)*saturation[i] + update_relaxation_*sat_new[i];
        }

        // Optionally check and/or clamp results.
	if (check_sat_ || clamp_sat_) {
	    checkAndPossiblyClampSat(saturation);
	}

        // Stop timer and optionally print seconds taken.
        clock.stop();
#ifdef VERBOSE
        std::cout << "Seconds taken by transport solver: " << clock.secsSinceStart() << std::endl;
#endif // VERBOSE
    }