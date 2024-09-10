  void benchmark_connect_disconnect()
{
  static const unsigned num_connections = 1000000;
  std::vector<typename connection_type<Signal>::type> connections(num_connections);

  Signal signal;
  std::cout << "connecting " << num_connections << " connections then disconnecting: ";
  unsigned n;
  {
    boost::progress_timer timer;
    for(n = 0; n < num_connections; ++n)
    {
      connections.at(n) = signal.connect(myslot());
    }
    for(n = 0; n < num_connections; ++n)
    {
      connections.at(n).disconnect();
    }
  }
}