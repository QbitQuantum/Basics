 /** Check that local endpoint is loopback
  *
  *  @throws Face::Error if validation failed
  */
 static void
 validateSocket(boost::asio::ip::tcp::socket& socket)
 {
   if (!socket.local_endpoint().address().is_loopback() ||
       !socket.remote_endpoint().address().is_loopback())
     {
       throw Face::Error("TcpLocalFace can be created only on loopback interface");
     }
 }