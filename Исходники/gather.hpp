  void
  gather_impl(const communicator& comm, const T* in_values, int n, 
              T* out_values, int root, mpl::false_)
  {
    int tag = environment::collectives_tag();
    int size = comm.size();

    for (int src = 0; src < size; ++src) {
      if (src == root)
        std::copy(in_values, in_values + n, out_values + n * src);
      else
        comm.recv(src, tag, out_values + n * src, n);
    }
  }