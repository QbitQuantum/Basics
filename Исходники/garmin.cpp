 void send_control_ushort(unsigned int type, unsigned short data) {
     frame_control_ushort frame;
     frame.frame_type = type;
     frame.len1 = 2;
     frame.data = data;
     m_control_socket.send(boost::asio::buffer(&frame, sizeof(frame)));
 }