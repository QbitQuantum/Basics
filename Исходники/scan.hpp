  void
  upper_lower_scan(const communicator& comm, const T* in_values, int n,
                   T* out_values, Op& op, int lower, int upper)
  {
    int tag = environment::collectives_tag();
    int rank = comm.rank();

    if (lower + 1 == upper) {
      std::copy(in_values, in_values + n, out_values);
    } else {
      int middle = (lower + upper) / 2;
      
      if (rank < middle) {
        // Lower half
        upper_lower_scan(comm, in_values, n, out_values, op, lower, middle);

        // If we're the last process in the lower half, send our values
        // to everyone in the upper half.
        if (rank == middle - 1) {
          packed_oarchive oa(comm);
          for (int i = 0; i < n; ++i)
            oa << out_values[i];

          for (int p = middle; p < upper; ++p)
            comm.send(p, tag, oa);
        }
      } else {
        // Upper half
        upper_lower_scan(comm, in_values, n, out_values, op, middle, upper);

        // Receive value from the last process in the lower half.
        packed_iarchive ia(comm);
        comm.recv(middle - 1, tag, ia);

        // Combine value that came from the left with our value
        T left_value;
        for (int i = 0; i < n; ++i)
          {
            ia >> left_value;
            out_values[i] = op(left_value, out_values[i]);
          }
      }
    }
  }