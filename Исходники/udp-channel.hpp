inline bool
UdpChannel::isListening() const
{
  return m_socket.is_open();
}