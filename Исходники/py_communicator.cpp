object 
communicator_recv(const communicator& comm, int source, int tag,
                  bool return_status)
{
  using pdalboost::python::make_tuple;

  object result;
  status stat = comm.recv(source, tag, result);
  if (return_status)
    return make_tuple(result, stat);
  else
    return result;
}