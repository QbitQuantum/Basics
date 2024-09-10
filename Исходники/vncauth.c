void
vncRandomBytesMs(unsigned char *where) {
  int i;
  static unsigned int seed;
  seed += (unsigned int) time(0) + _getpid() + _getpid() * 987654;

  srand(seed);
  for (i=0; i < CHALLENGESIZEMS; i++) {
    where[i] = (unsigned char)(rand() & 255);    
  }
}