uint32_t TBinaryProtocol::writeDouble(const double dub) {
  BOOST_STATIC_ASSERT(sizeof(double) == sizeof(uint64_t));
  BOOST_STATIC_ASSERT(std::numeric_limits<double>::is_iec559);

  uint64_t bits = bitwise_cast<uint64_t>(dub);
  bits = htonll(bits);
  trans_->write((uint8_t*)&bits, 8);
  return 8;
}