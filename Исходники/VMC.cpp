  /** Run the VMC algorithm.
   * \param nblocks number of blocks
   * \param nsteps number of steps
   * \param tau the timestep
   *
   * Advance the walkers nblocks*nsteps timesteps. 
   * For each timestep:
   * <ul>
   * <li> Move all the particles of a walker.
   * <li> Calculate the properties for the new walker configuration.
   * <li> Accept/reject the new configuration.
   * <li> Accumulate the estimators.
   * </ul>
   * For each block:
   * <ul>
   * <li> Flush the estimators and print to file.
   * <li> (Optional) Print the ensemble of walker configurations.
   * </ul>
   *
   * Default mode: Print the ensemble of walker configurations 
   * at the end of the run.
   */
  bool VMC::run() { 
    
#ifdef MOVE_ONE
    DistanceTable::create(1);
#else
    DistanceTable::create(W.getActiveWalkers());
    Psi.resizeByWalkers(W.getActiveWalkers());
#endif

    if(put(qmc_node)){
      
      //set the data members to start a new run
      getReady();
      
      //probably unnecessary
      for(MCWalkerConfiguration::iterator it = W.begin(); 
	  it != W.end(); ++it) {
	(*it)->Properties(Weight) = 1.0;
      }
      
      Estimators.reset();

      //create an output engine
      HDFWalkerOutput WO(RootName);
      
      IndexType block = 0;
      
      Pooma::Clock timer;
      
      double wh=0.0;
      IndexType accstep=0;
      IndexType nAcceptTot = 0;
      IndexType nRejectTot = 0;
      do {
	IndexType step = 0;
	timer.start();
	nAccept = 0; nReject=0;
	do {
#ifdef MOVE_ONE
	  advanceWalkerByWalker();
#else
	  advanceAllWalkers();
#endif
	  step++;accstep++;
	  Estimators.accumulate(W);
	} while(step<nSteps);
	
	timer.stop();
	nAcceptTot += nAccept;
	nRejectTot += nReject;
	
	Estimators.flush();
	Estimators.setColumn(AcceptIndex,
			     static_cast<double>(nAccept)/static_cast<double>(nAccept+nReject));
	Estimators.report(accstep);
	
	LogOut->getStream() << "Block " << block << " " << timer.cpu_time() << endl;
	if(pStride) WO.get(W);
	nAccept = 0; nReject = 0;
	block++;
      } while(block<nBlocks);
      
      LogOut->getStream() 
	<< "Ratio = " 
	<< static_cast<double>(nAcceptTot)/static_cast<double>(nAcceptTot+nRejectTot)
	<< endl;
      
      if(!pStride) WO.get(W);
      
      Estimators.finalize();
      
      return true;
    } else {
      ERRORMSG("Error with Input")
      return false;
    }
  }