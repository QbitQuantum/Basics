static void slave(mpi::communicator world) {

  int work;
  int result;

  while (1) {

    mpi::status status = world.recv(mpi::any_source,mpi::any_tag,work);
    if (status.tag() == DIETAG) {
      return;
    }
      do_work(work,result);
      world.send(0,0,result);
  }
}