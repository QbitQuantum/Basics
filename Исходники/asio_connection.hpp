 void do_read_some()
 {
     socket_.async_read_some(boost::asio::buffer(data_, packet_size_),
         [this](const boost::system::error_code & ec, std::size_t received_bytes)
         {
             if ((uint32_t)received_bytes != packet_size_) {
                 std::cout << "asio_connection::do_read_some(): async_read(), received_bytes = "
                           << received_bytes << " bytes." << std::endl;
             }
             if (!ec) {
                 // A successful request, can be used to statistic qps
                 do_write_some();
             }
             else {
                 // Write error log
                 std::cout << "asio_connection::do_read_some() - Error: (code = " << ec.value() << ") "
                           << ec.message().c_str() << std::endl;
                 stop(true);
             }
         }
     );
 }