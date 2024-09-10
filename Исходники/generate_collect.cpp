void generate_data(mpi::communicator local, mpi::communicator world)
{
  using std::srand;
  using std::rand;

  // The rank of the collector within the world communicator
  int master_collector = local.size();

  srand(time(0) + world.rank());

  // Send out several blocks of random data to the collectors.
  int num_data_blocks = rand() % 3 + 1;
  for (int block = 0; block < num_data_blocks; ++block) {
    // Generate some random data
    int num_samples = rand() % 1000;
    std::vector<int> data;
    for (int i = 0; i < num_samples; ++i) {
      data.push_back(rand());
    }

    // Send our data to the master collector process.
    std::cout << "Generator #" << local.rank() << " sends some data..."
              << std::endl;
    world.send(master_collector, msg_data_packet, data);
  }

  // Wait for all of the generators to complete
  (local.barrier)();

  // The first generator will send the message to the master collector
  // indicating that we're done.
  if (local.rank() == 0)
    world.send(master_collector, msg_finished);
}