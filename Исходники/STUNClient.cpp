bool STUNClient::createSingleSocket(
  const std::string& stunServer,
  boost::asio::ip::udp::socket& socket,
  const OSS::IPAddress& lAddr,
  OSS::IPAddress& externalAddress)
{
  OSS::mutex_critic_sec_lock globalLock(_csGlobal);

  _test1Responded = false;
  _test2Responded = false;
  _test3Responded = false;
  _test10Responded = false;
  _test1ChangedAddr = OSS::IPAddress();
  _test1MappedAddr = OSS::IPAddress();
  _test10MappedAddr = OSS::IPAddress();
  _sendCount = 0;

  OSS::IPAddress localAddress = lAddr;
  OSS::IPAddress targetAddress = OSS::IPAddress::fromV4IPPort(stunServer.c_str());
  if (!targetAddress.isValid() || !localAddress.isValid())
    return false;

  if (!targetAddress.getPort())
    targetAddress.setPort(STUN_PORT);

  if (!socket.is_open())
  {
    socket.open(boost::asio::ip::udp::v4());
    boost::asio::ip::udp::endpoint ep;

    ep = boost::asio::ip::udp::endpoint(localAddress.address(), localAddress.getPort());
    boost::system::error_code ec;
    socket.bind(ep, ec);
    if (ec)
      return false;
  }

  while (_sendCount < 15)
  {
    _sendCount++;
    if (!_test1Responded)
      sendTestRequest(socket,  targetAddress, 1);
    else
      break;
  }

  if (_test1Responded)
  {
    externalAddress = _test1MappedAddr;
    return externalAddress.isValid();
  }

  return false;
}