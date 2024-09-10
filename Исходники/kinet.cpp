/**
 * Handle a KiNet poll packet
 */
void HandlePoll(const struct sockaddr_in &source,
                const kinet_packet &packet,
                unsigned int size) {
  ssize_t r = udp_socket.SendTo(peer0_0, sizeof(peer0_0), source);
  OLA_INFO << "sent " << r << " bytes";
}