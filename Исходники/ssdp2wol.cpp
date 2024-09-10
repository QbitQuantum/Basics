static void wol(Socket::ptr socket, const std::string &macAddress) {
  MORDOR_ASSERT(macAddress.size() == 6u);
  std::string message;
  message.append(6u, (char)0xff);
  for(size_t i = 0; i < 16; ++i)
      message.append(macAddress);
  socket->send(message.c_str(), message.size());
}