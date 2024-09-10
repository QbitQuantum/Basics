    bool EulerUpstreamImplicit<GI, RP, BC>::transportSolve(std::vector<double>& saturation,
                                                           const double time,
                                                           const typename GI::Vector& /* gravity */,
                                                           const PressureSolution& pressure_sol,
                                                           const Opm::SparseVector<double>& /* injection_rates */) const
    {

        Opm::ReservoirState<2> state(mygrid_.c_grid());
        {
            std::vector<double>& sat = state.saturation();
            for (int i=0; i < mygrid_.numCells(); ++i){
                sat[2*i] = saturation[i];
                sat[2*i+1] = 1-saturation[i];
            }
        }

        //int count=0;
        const UnstructuredGrid* cgrid = mygrid_.c_grid();
        int numhf = cgrid->cell_facepos[cgrid->number_of_cells];

        std::vector<double>     faceflux(numhf);

        for (int c = 0, i = 0; c < cgrid->number_of_cells; ++c){
            for (; i < cgrid->cell_facepos[c + 1]; ++i) {
                int f= cgrid->cell_faces[i];
                double outflux = pressure_sol.outflux(i);
                double sgn = 2.0*(cgrid->face_cells[2*f + 0] == c) - 1;
                faceflux[f] = sgn * outflux;
            }
        }
        int num_db=direclet_hfaces_.size();
        std::vector<double> sflux(num_db);
        for (int i=0; i < num_db;++i){
            sflux[i]=-pressure_sol.outflux(direclet_hfaces_[i]);
        }
        state.faceflux()=faceflux;

        double dt_transport = time;
        int nr_transport_steps = 1;
	Opm::time::StopWatch clock;
        int repeats = 0;
        bool finished = false;
        clock.start();

        TwophaseFluid myfluid(myrp_);
        double* tmp_grav=0;
        const UnstructuredGrid& c_grid=*mygrid_.c_grid();
        TransportModel model(myfluid,c_grid,porevol_,tmp_grav);
        model.makefhfQPeriodic(periodic_faces_,periodic_hfaces_, periodic_nbfaces_);
        model.initGravityTrans(*mygrid_.c_grid(),htrans_);
        TransportSolver tsolver(model);
        LinearSolver linsolve_;
        Opm::ImplicitTransportDetails::NRReport  rpt_;

        Opm::TransportSource tsrc;//create_transport_source(0, 2);
        // the input flux is assumed to be the saturation times the flux in the transport solver

        tsrc.nsrc =direclet_cells_.size();
        tsrc.saturation = direclet_sat_;
        tsrc.cell = direclet_cells_;
        tsrc.flux = sflux;

        while (!finished) {
            for (int q = 0; q < nr_transport_steps; ++q) {
                tsolver.solve(*mygrid_.c_grid(), &tsrc, dt_transport, ctrl_, state, linsolve_, rpt_);
                if(rpt_.flag<0){
                    break;
                }
            }
            if(!(rpt_.flag<0) ){
                finished =true;
            }else{
                if(repeats >max_repeats_){
                    finished=true;
                }else{
                    OPM_MESSAGE("Warning: Transport failed, retrying with more steps.");
                    nr_transport_steps *= 2;
                    dt_transport = time/nr_transport_steps;
                    if (ctrl_.verbosity){
                        std::cout << "Warning: Transport failed, retrying with more steps. dt = "
                                  << dt_transport/Opm::unit::year << " year.\n";
                    }

                    std::vector<double>& sat = state.saturation();
                    for (int i=0; i < mygrid_.numCells(); ++i){
                        sat[2*i] = saturation[i];
                        sat[2*i+1] = 1-saturation[i];
                    }
                }
            }
            repeats +=1;
        }
        clock.stop();
        std::cout << "EulerUpstreamImplicite used  " << repeats
                  << " repeats and " << nr_transport_steps <<" steps"<< std::endl;
#ifdef VERBOSE
        std::cout << "Seconds taken by transport solver: " << clock.secsSinceStart() << std::endl;
#endif // VERBOSE
        {
            std::vector<double>& sat = state.saturation();
            for (int i=0; i < mygrid_.numCells(); ++i){
                saturation[i] = sat[2*i];
            }
        }
        if((rpt_.flag<0)){
            std::cerr << "EulerUpstreamImplicit did not converge" << std::endl;
            return false;
        }else{
            return true;
        }
    }