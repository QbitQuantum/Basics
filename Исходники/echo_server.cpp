 void start()
 {
     fprintf(stderr, "session::handle_read()\n");
     socket_.async_read_some(boost::asio::buffer(data_, max_length),
             boost::bind(&session::handle_read, this,
                 boost::asio::placeholders::error,
                 boost::asio::placeholders::bytes_transferred));
 }