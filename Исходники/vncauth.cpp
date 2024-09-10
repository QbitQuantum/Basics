/*
 *   Generate a set of random bytes for use in challenge-response authentication.
 */
void
vncRandomBytes(unsigned char *where) {
  int i;
  static unsigned int seed;
#ifdef WIN32
  seed += (unsigned int) time(0) + _getpid() + _getpid() * 987654;
#else
  seed += (unsigned int) time(0) + getpid() + getpid() * 987654;
#endif

  srand(seed);
  for (i=0; i < CHALLENGESIZE; i++) {
    where[i] = (unsigned char)(rand() & 255);    
  }
}