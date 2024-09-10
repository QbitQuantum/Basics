void
ring_test(const communicator& comm, const T& pass_value, const char* kind,
          int root = 0)
{
  T transferred_value;

  int rank = comm.rank();
  int size = comm.size();

  if (rank == root) {
    std::cout << "Passing " << kind << " around a ring from root " << root
              << "...";
    comm.send((rank + 1) % size, 0, pass_value);
    comm.recv((rank + size - 1) % size, 0, transferred_value);
    BOOST_CHECK(transferred_value == pass_value);
    if (transferred_value == pass_value) std::cout << " OK." << std::endl;
  } else {
    comm.recv((rank + size - 1) % size, 0, transferred_value);
    BOOST_CHECK(transferred_value == pass_value);
    comm.send((rank + 1) % size, 0, transferred_value);
  }

  (comm.barrier)();
}