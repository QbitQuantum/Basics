//-----------------------------------------------------------------------------
std::set<uint64_t> ProperDivisors::divisors_set() const { // NOLINT(build/include_what_you_use)
  std::set<uint64_t> divs = {1};  // NOLINT(build/include_what_you_use)
  uint64_t ubound = ceil(sqrt(value));
  for (uint64_t x = 2; x <= ubound; ++x) {
    // get quotient and remainder in one step - actually optimized?
    std::lldiv_t result = lldiv(value, x);
    if (result.rem == 0) {
      divs.insert(x);
      divs.insert(result.quot);
    }
  }
  return divs;
}