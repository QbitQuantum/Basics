  void run() {
    using namespace boost::posix_time;
    boost::system::error_code error;
    ptime now;
    udp::endpoint endpoint;
    while(!this->checked_ || this->alive_) {
      socket->receive_from(asio::buffer(buf), endpoint, 0, error);

      if(error == boost::system::errc::success) {
        last = microsec_clock::local_time();
      }
    }
  }