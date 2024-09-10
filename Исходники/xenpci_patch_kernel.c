/* called with interrupts disabled (via CLI) from an arbitrary location inside HAL.DLL */
static __inline LONG
ApicHighestVector(PULONG bitmap) {
  int i;
  ULONG bit;
  ULONG value;
  for (i = 0; i < 8; i++) {
    value = bitmap[(7 - i) * 4];
    if (value) {
      _BitScanReverse(&bit, value);
      return ((7 - i) << 5) | bit;
    }
  }
  return -1;
}