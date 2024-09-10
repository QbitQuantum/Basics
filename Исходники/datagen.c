uint64_t linearize(uint32_t x, uint32_t y) {
  uint64_t result;
  result =  _pdep_u64(x, 0x5555555555555555);
  result ^= _pdep_u64(y, 0xAAAAAAAAAAAAAAAA);
  return result;
}