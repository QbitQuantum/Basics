void Packet::read(socket& socket) {
  std::uint32_t bytes_read = 0;

  if (ext_len > 0) {
    std::vector<char> extras(ext_len);
    while (bytes_read < static_cast<std::uint32_t>(ext_len)) {
      bytes_read += socket.receive(boost::asio::buffer(extras));
    }
    bytes_read = 0;

    if (extras.size() > 4) {
      char flags_buf[4] = { extras[0], extras[1], extras[2], extras[3] };
      flags = readUInt32LE(flags_buf, 0);
    }
  }

  if (key_len > 0) {
    key.resize(key_len);
    while (bytes_read < key_len) {
      bytes_read += socket.receive(boost::asio::buffer(key));
    }
    bytes_read = 0;
  }

  if (bod_len > key_len) {
    std::uint32_t val_len = bod_len - key_len - ext_len;
    val.resize(val_len);
    while (bytes_read < val_len) {
      bytes_read += socket.receive(boost::asio::buffer(val));
    }
  }
}