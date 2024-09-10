static void gentab(int bits, uint64 poly, int reflected)
{
  int i;
  uint64 topbit = 1ULL << (bits-1);
  uint64 mask = ~0ULL >> (64-bits);
  for (i = 0; i < 256; ++i) {
    uint64 crc = i;
    int j;
    if (reflected) crc = reflect(crc, 8);
    crc <<= bits - 8;
    for (j = 0; j < 8; ++j)
      crc = (crc << 1) ^ ((crc & topbit) ? poly : 0);
    if (reflected) crc = reflect(crc, bits);
    crctab[i] = crc & mask;
  }
}