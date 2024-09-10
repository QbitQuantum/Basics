void bi::MarginalSISHandler<B,A,S>::handleStopperLogWeights(
    boost::mpi::communicator child, boost::mpi::status status) {
  typedef typename temp_host_vector<real>::type vector_type;

  double maxlw = BI_INF;

  /* add weights */
  boost::optional<int> n = status.template count<real>();
  if (n) {
    vector_type lws(*n);
    child.recv(status.source(), status.tag(), lws.buf(), *n);
    stopper.add(lws, maxlw);
  }

  /* signal stop if necessary */
  if (stopper.stop()) {
    BOOST_AUTO(iter, node.children.begin());
    for (; iter != node.children.end(); ++iter) {
      node.requests.push_front(iter->isend(0, MPI_TAG_STOPPER_STOP));
    }
  }
}