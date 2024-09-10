void SFVDomain::doInitialize(){

    // Initialize the solver:
    solver->initialize();

    // write the headers of the output files:
    qOutput->writeHeader();

    // Insert the phase functions which are to be called every timestep
    if (solver->get_dimension()==1){

        // Phase-0: timestep initialization
        insertPhase([this](unsigned int ts){
            if (isChild()){
                solver->adjustPatches(ts);
                solver->imposePatchBCs(0);
            }
            solver->imposeGridBC(ts);
        });

        // Phase-1: Riemann solver
        insertPhase([this](unsigned int ts){
            solver->riemann(0);
        });

        // Phase-2: Calculate new Q values
        insertPhase([this](unsigned int ts){
            solver->calculateQ();
            solver->applyBottomFriction();
            if (isChild()){
                solver->getQfromParent();
            }
        });

        // Phase-3: Post-processing
        insertPhase([this](unsigned int ts){
            qOutput->writeOutput(ts);
        });

    }
    else if (solver->get_dimension()==2){
        Report::error("SFVDomain","2d solver not yet supported!");
    }

}