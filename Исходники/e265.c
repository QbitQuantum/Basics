int main(int argc, char* argv[]) {
  llu sum = 0;
  uint low = 1 << 4;
  uint up = 1 << 25;
  int subseq[TWOPOW];
  for (uint i = low; i < up; i++) {
    for (int j = 0; j < TWOPOW; j++) subseq[j] = 0;
    uint ii = 2 * (up + i) + 1;
    uint jj = ii;
    for (int j = 0; j < TWOPOW; j++) {
      ii = _rotr(ii, 1);
      subseq[ii % TWOPOW]++;
    }
    int j;
    for (j = 0; j < TWOPOW; j++) if (subseq[j] != 1) break;
    if (j == TWOPOW) {
      sum += jj;
    }
  }
  printf("%llu\n", sum);
  return 0;
}