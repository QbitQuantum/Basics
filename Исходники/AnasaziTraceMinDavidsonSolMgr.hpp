bool TraceMinDavidsonSolMgr<ScalarType,MV,OP>::performRestart(int &numRestarts, Teuchos::RCP< TraceMinBase<ScalarType,MV,OP> > solver)
{
#ifdef ANASAZI_TEUCHOS_TIME_MONITOR
  Teuchos::TimeMonitor restimer(*this->_timerRestarting);
#endif

  if ( numRestarts >= maxRestarts_ ) {
    return false; // break from while(1){tm_solver->iterate()}
  }
  numRestarts++;

  this->printer_->stream(IterationDetails) << " Performing restart number " << numRestarts << " of " << maxRestarts_ << std::endl << std::endl;

  TraceMinBaseState<ScalarType,MV> oldstate = solver->getState();
  TraceMinBaseState<ScalarType,MV> newstate;
  int newdim = this->numRestartBlocks_*this->blockSize_;
  std::vector<int> indToCopy(newdim);
  for(int i=0; i<newdim; i++) indToCopy[i] = i;

  // Copy the relevant parts of the old state to the new one
  // This may involve computing parts of X
  if(this->useHarmonic_)
  {
    newstate.V = MVT::CloneView(*solver->getRitzVectors(),indToCopy);
    newstate.curDim = newdim;

  }
  else
  {
    this->copyPartOfState (oldstate, newstate, indToCopy);
  }

  // send the new state to the solver
  newstate.NEV = oldstate.NEV;
  solver->initialize(newstate);

  return true;
}