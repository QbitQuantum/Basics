uint32 TRanrotWGenerator::BRandom() {
  // generate next random number
  uint32 y, z;
  // generate next number
  z = _lrotl(randbuffer[p1][0], R1) + randbuffer[p2][0];
  y = _lrotl(randbuffer[p1][1], R2) + randbuffer[p2][1];
  randbuffer[p1][0] = y; randbuffer[p1][1] = z;
  // rotate list pointers
  if (--p1 < 0) p1 = KK - 1;
  if (--p2 < 0) p2 = KK - 1;
  // perform self-test
  if (randbuffer[p1][0] == randbufcopy[0][0] &&
    memcmp(randbuffer, randbufcopy[KK-p1], 2*KK*sizeof(uint32)) == 0) {
      // self-test failed
      if ((p2 + KK - p1) % KK != JJ) {
        // note: the way of printing error messages depends on system
        // In Windows you may use FatalAppExit
        printf("Random number generator not initialized");}
      else {
        printf("Random number generator returned to initial state");}
      exit(1);}
  randbits[0] = y;
  randbits[1] = z;
  return y;}