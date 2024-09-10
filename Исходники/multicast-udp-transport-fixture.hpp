 void
 sendToGroup(udp::socket& sock, const std::vector<uint8_t>& buf, bool needToCheck = true) const
 {
   sock.async_send_to(boost::asio::buffer(buf), remoteMcastEp,
     [needToCheck] (const auto& error, size_t) {
       if (needToCheck) {
         BOOST_REQUIRE_EQUAL(error, boost::system::errc::success);
       }
     });
 }