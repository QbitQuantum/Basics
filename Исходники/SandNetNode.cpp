/*
 * Send a packet
 */
bool SandNetNode::SendPacket(const sandnet_packet &packet,
                             unsigned int size,
                             bool is_control) {
  UDPSocket *socket;
  if (is_control)
    socket = &m_control_socket;
  else
    socket = &m_data_socket;

  ssize_t bytes_sent = socket->SendTo(
      reinterpret_cast<const uint8_t*>(&packet),
      size,
      is_control ? m_control_addr : m_data_addr,
      is_control ? CONTROL_PORT : DATA_PORT);

  if (bytes_sent != static_cast<ssize_t>(size)) {
    OLA_INFO << "Only sent " << bytes_sent << " of " << size;
    return false;
  }
  return true;
}