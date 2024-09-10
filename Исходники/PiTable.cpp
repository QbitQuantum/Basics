PiTable::PiTable(uint64_t max) :
  max_(max)
{
  pi_.resize(max / 64 + 1);
  primesieve::iterator it(0, max);

  uint64_t pix = 0;
  uint64_t prime = 0;

  while ((prime = it.next_prime()) <= max)
    pi_[prime / 64].bits |= 1ull << (prime % 64);

  for (auto& i : pi_)
  {
    i.prime_count = pix;
    pix += popcnt64(i.bits);
  }
}