 void SendCmd()
 {
     socket_.send(boost::asio::buffer(boost::str(boost::format("s,%1%,%2%,%3%,%4%") % Pitch_ % Roll_ % Yaw_ % H_)));
 }