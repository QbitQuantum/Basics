  /** Advance the walkers nblocks*nsteps timesteps. 
   * @param nblocks number of blocks
   * @param nsteps number of steps
   * @param tau the timestep
   *
   * For each timestep:
   * <ul>
   * <li> Move all the particles of a walker.
   * <li> Calculate the properties for the new walker configuration.
   * <li> Accept/reject the new configuration.
   * <li> Accumulate the estimators.
   * <li> Update the trial energy \f$ E_T. \f$
   * <li> Branch the population of walkers (birth/death algorithm).
   * </ul>
   * For each block:
   * <ul>
   * <li> Flush the estimators and print to file.
   * <li> Update the estimate of the local energy.
   * <li> (Optional) Print the ensemble of walker configurations.
   * </ul>
   * Default mode: Print the ensemble of walker configurations 
   * at the end of the run.
   */
  bool DMCWOS::run() { 
    
   //create a distance table for one walker
    //DistanceTable::create(1);
    //deltaR.resize(W.getTotalNum());
    //drift.resize(W.getTotalNum());

    //if(put(qmc_node)){
      // extract the WOS potential and reset the parameters for DMC
      wos_ref = dynamic_cast<WOSPotential*>(H.getHamiltonian("wos"));
      if(wos_ref) {
         cout << wos_ref->m_runs << '\t' << wos_ref->m_norm << endl;
         wos_ref->set_mrun(wos_ref->dmc_runs);
         cout << "Using " << wos_ref->m_runs << " runners/walker for DMC" << endl;
         H.setTau(Tau);
	 Tau_var = Tau;
      } else {
         H.setTau(0.0);
	 Tau_var = 0.0;
      }

      MolecuFixedNodeBranch<RealType> brancher(Tau,W.getActiveWalkers());
      brancher.put(qmc_node,LogOut);

      if(BranchInfo != "default")  brancher.read(BranchInfo);

      //set the data members to start a new run
      //    getReady();
      int PopIndex, E_TIndex;
      Estimators.resetReportSettings(RootName);
      AcceptIndex = Estimators.addColumn("AcceptRatio");
      PopIndex = Estimators.addColumn("Population");
      E_TIndex = Estimators.addColumn("E_T");
      Estimators.reportHeader();
      MCWalkerConfiguration::iterator it = W.begin(); 
      MCWalkerConfiguration::iterator it_end = W.end(); 
      while(it != it_end) {
	(*it)->Properties(WEIGHT) = 1.0;
	(*it)->Properties(MULTIPLICITY) = 1.0;
        ++it;
      }
      
      /*if VMC/DMC directly preceded DMC (Counter > 0) then
	use the average value of the energy estimator for
	the reference energy of the brancher*/
      if(Counter) {
	RealType e_ref = W.getLocalEnergy();
	LOGMSG("Overwriting the reference energy by the local energy " << e_ref)  
	brancher.setEguess(e_ref);
      }
      
      IndexType block = 0;
      
      Pooma::Clock timer;
      int Population = W.getActiveWalkers();
      int tPopulation = W.getActiveWalkers();
      RealType Eest = brancher.E_T;
      IndexType nAcceptTot = 0;
      IndexType nRejectTot = 0;
      
      do {
	IndexType step = 0;
	timer.start();
	do {
	  Population = W.getActiveWalkers();
	  advanceWalkerByWalker(brancher);
	  step++; CurrentStep++;
	  Estimators.accumulate(W);
	  //E_T = brancher.update(Population,Eest);
	  Eest = brancher.update(Population,Eest);
	  brancher.branch(CurrentStep,W);
	} while(step<nSteps);
	timer.stop();
	
	nAcceptTot += nAccept;
	nRejectTot += nReject;
	Estimators.flush();
	
	Estimators.setColumn(PopIndex,static_cast<double>(Population));
	Estimators.setColumn(E_TIndex,Eest);
	Estimators.setColumn(AcceptIndex,
			     static_cast<double>(nAccept)/static_cast<double>(nAccept+nReject));
	Estimators.report(CurrentStep);
	LogOut->getStream() << "Block " << block << " " << timer.cpu_time()
			    << " " << Population << endl;
	Eest = Estimators.average(0);
	
	nAccept = 0; nReject = 0;
	block++;
	if(pStride) {
	  //create an output engine: could accumulate the configurations
	  HDFWalkerOutput WO(RootName);
	  WO.get(W);
          brancher.write(WO.getGroupID());
	}
	W.reset();
      } while(block<nBlocks);
      
      LogOut->getStream() 
	<< "ratio = " << static_cast<double>(nAcceptTot)/static_cast<double>(nAcceptTot+nRejectTot)
	<< endl;
      
      if(!pStride) {
	//create an output engine: could accumulate the configurations
	HDFWalkerOutput WO(RootName);
	WO.get(W);
        brancher.write(WO.getGroupID());
      }
      Estimators.finalize();
      return true;
    //} else 
    //  return false;
  }