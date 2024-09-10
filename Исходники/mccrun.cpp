void mccrun_slave(
  const Options& opts, const Eigen::VectorXd& vpar,
  const set<observables_t>& obs, const mpi::communicator& mpicomm )
{
  // prepare the simulation

  HubbardModelVMC model = prepare_model( opts, vpar, mpicomm );
  vector< unique_ptr<Observable> > obscalc = prepare_obscalcs( obs, opts );
  ObservableCache obscache;

  // equilibrate the system

  for (
    unsigned int mcs = 0;
    mcs < opts["calc.num-mcs-equil"].as<unsigned int>();
    ++mcs )
  {
    model.mcs();
  }

  // run this slaves part of the Monte Carlo cycle

  unsigned int completed_bins_thisslave = 0;
  bool master_out_of_work = false;
  unsigned int scheduled_bins_thisslave;
  mpicomm.send( 0, MSGTAG_S_M_REQUEST_BINS );
  mpicomm.recv( 0, MSGTAG_M_S_DISPATCHED_BINS, scheduled_bins_thisslave );
  master_out_of_work = ( scheduled_bins_thisslave == 0 );

  while ( scheduled_bins_thisslave > 0 ) {

    unsigned int new_scheduled_bins_thisslave;
    mpi::request master_answer;
    if ( !master_out_of_work ) {
      // ask the master for more work
      mpicomm.send( 0, MSGTAG_S_M_REQUEST_BINS );
      master_answer = mpicomm.irecv(
        0, MSGTAG_M_S_DISPATCHED_BINS,
        new_scheduled_bins_thisslave
      );
    }

    for (
      unsigned int mcs = 0;
      mcs < opts["calc.num-binmcs"].as<unsigned int>();
      ++mcs )
    {
      // perform a Monte Carlo step
      model.mcs();

     // measure observables
      for ( const unique_ptr<Observable>& o : obscalc ) {
        o->measure( model, obscache );
      }
      obscache.clear();
    }

    // tell the observables that a bin has been completed
    for ( const unique_ptr<Observable>& o : obscalc ) {
      o->completebin();
    }

    // report completion of the work
    mpicomm.send( 0, 2 );
    ++completed_bins_thisslave;
    --scheduled_bins_thisslave;

    if ( !master_out_of_work ) {
      // wait for answer from master concerning the next bin
      master_answer.wait();
      if ( new_scheduled_bins_thisslave == 1 ) {
        ++scheduled_bins_thisslave;
      } else {
        master_out_of_work = true;
      }
    }
  }

  // send floating point precision control data to master
  mpi::gather( mpicomm, model.get_W_devstat(), 0 );
  mpi::gather( mpicomm, model.get_T_devstat(), 0 );

  // send observables to master
  for ( const unique_ptr<Observable>& o : obscalc ) {
    o->send_results_to_master( mpicomm );
  }
}