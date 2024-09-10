int PMPI_Startall(int count, MPI_Request * requests)
{
  int retval;
  smpi_bench_end();
  if (requests == nullptr) {
    retval = MPI_ERR_ARG;
  } else {
    retval = MPI_SUCCESS;
    for (int i = 0; i < count; i++) {
      if(requests[i] == MPI_REQUEST_NULL) {
        retval = MPI_ERR_REQUEST;
      }
    }
    if(retval != MPI_ERR_REQUEST) {
      int my_proc_id = simgrid::s4u::this_actor::get_pid();
      TRACE_smpi_comm_in(my_proc_id, __func__, new simgrid::instr::NoOpTIData("Startall"));
      MPI_Request req = MPI_REQUEST_NULL;
      if (not TRACE_smpi_view_internals())
        for (int i = 0; i < count; i++) {
          req = requests[i];
          if (req->flags() & MPI_REQ_SEND)
            TRACE_smpi_send(my_proc_id, my_proc_id, getPid(req->comm(), req->dst()), req->tag(), req->size());
        }

      simgrid::smpi::Request::startall(count, requests);

      if (not TRACE_smpi_view_internals())
        for (int i = 0; i < count; i++) {
          req = requests[i];
          if (req->flags() & MPI_REQ_RECV)
            TRACE_smpi_recv(getPid(req->comm(), req->src()), my_proc_id, req->tag());
        }
      TRACE_smpi_comm_out(my_proc_id);
    }
  }
  smpi_bench_begin();
  return retval;
}