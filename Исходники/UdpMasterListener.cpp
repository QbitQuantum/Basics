//*******************************************************************************
void UdpMasterListener::bindUdpSocket(QUdpSocket& udpsocket, int port) throw(std::runtime_error)
{
  // QHostAddress::Any : let the kernel decide the active address
  if ( !udpsocket.bind(QHostAddress::Any,
                       port, QUdpSocket::DefaultForPlatform) ) {
    //std::cerr << "ERROR: could not bind UDP socket" << endl;
    //std::exit(1);
    throw std::runtime_error("Could not bind UDP socket. It may be already binded.");
  }
  else {
    cout << "UDP Socket Receiving in Port: " << port << endl;
  }
}