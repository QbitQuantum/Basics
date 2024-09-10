 bool
 startRecvThread(std::shared_ptr<TunDevice> &tun,
                 std::shared_ptr<typename WsServer::Connection> &connection) {
   tun->setRecvThread(new std::thread([tun, connection, this]() {
     do {
       tun->getFromTun().pop([&connection, this](Packet *pkt) {
         auto send_stream = std::make_shared<typename WsServer::SendStream>();
         *send_stream << "PAKT";
         send_stream->write((const char *)pkt->buf, pkt->size);
         wsServer->send(
             connection, send_stream, [](const boost::system::error_code &ec) {
               if (ec != 0) {
                 LOG(ERROR) << "Server: Error Recv-sending message:" << ec
                            << ", error message: " << ec.message();
               }
               return 0;
             }, 130); // switch binary
         return 1;
       });
     } while (tun->getRunning());
   }));
   return true;
 }