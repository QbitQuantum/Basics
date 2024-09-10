void runSlave(mpi::communicator world)
{
  // Recieve
  MatrixCrossSection cs;
  world.recv(0, 0, cs);

  Matrix subMatrix(Size(cs.row_data.size(), cs.row_data.size()));
  cs.calculateVectorProduct(subMatrix);

  world.send(0, 0, subMatrix);
}