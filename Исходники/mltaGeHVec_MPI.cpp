void mltaGeHVec_MPI(double d, mblock<double>** A, double* x, double* y,
                   unsigned p, unsigned *seq_part, blcluster** blList)
{
  unsigned rank = COMM_AHMED.Get_rank();
  unsigned info[3];  // nblcks, beg2, n2

  if (rank == 0)
  {

    for (unsigned j=1; j<p; j++)
    {
      info[0] = seq_part[j+1] - seq_part[j];
      dimsx_(blList+seq_part[j], info[0], info[1], info[2]);
      COMM_AHMED.Send(info, 3, MPI::UNSIGNED, j, 1);
      COMM_AHMED.Send(x+info[1], info[2], MPI::DOUBLE, j, 2);
    }

    // compute for processor 0
    for (unsigned i=seq_part[0]; i<seq_part[1]; ++i)
    {
      unsigned idx = i-seq_part[0];
      A[idx]->mltaVec(d, x+blList[i]->getb2(), y+blList[i]->getb1());
    }

    for (unsigned j=1; j<p; ++j)
    {
      unsigned dimsy[2];
      COMM_AHMED.Recv(dimsy, 2, MPI::UNSIGNED, j, 3);

      double* tmp = new double[dimsy[1]];
      COMM_AHMED.Recv(tmp, dimsy[1], MPI::DOUBLE, j, 4);

      blas::add(dimsy[1], tmp, y+dimsy[0]);

      delete [] tmp;
    }
  }
  else
  {

    COMM_AHMED.Recv(info, 3, MPI::UNSIGNED, 0, 1);

    // receive required part of x
    double* xp = new double[info[2]];
    COMM_AHMED.Recv(xp, info[2], MPI::DOUBLE, 0, 2);

    unsigned dimsy[2];
    dimsy_(blList+seq_part[rank], info[0], dimsy[0], dimsy[1]);
    double* tmp = new double[dimsy[1]];
    blas::setzero(dimsy[1], tmp);

    for (unsigned i=seq_part[rank]; i<seq_part[rank+1]; ++i)
    {
      unsigned idx = i-seq_part[rank];
      A[idx]->mltaVec(d, xp+blList[i]->getb2()-info[1],
			tmp+blList[i]->getb1()-dimsy[0]);
    }

    COMM_AHMED.Send(dimsy, 2, MPI::UNSIGNED, 0, 3);
    COMM_AHMED.Send(tmp, dimsy[1], MPI::DOUBLE, 0, 4);

    delete [] tmp;
    delete [] xp;
  }
}