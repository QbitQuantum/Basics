future<void> session(ip::tcp::socket s, size_t block_size) {
  vector<char> buf(block_size);
  s.set_option(ip::tcp::no_delay(true));
  for (;;) {
    auto n = co_await async_read_some(s, buffer(buf.data(), block_size));
    n = co_await async_write(s, buffer(buf.data(), n));
  }
}