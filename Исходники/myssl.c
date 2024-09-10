/** Generate 128 bits of random noise for seeding RNGs. Attempts to
 * use various OS-specific sources of random bits, with a fallback
 * based on time and pid. */
void
generate_seed(uint64_t seeds[])
{
  bool seed_generated = false;
  static int stream_count = 0;
  int len = sizeof(uint64_t) * 2;

#ifdef HAVE_GETENTROPY
  /* On OpenBSD and up to date Linux, use getentropy() to avoid the
     open/read/close sequence with /dev/urandom */
  if (!seed_generated && getentropy(seeds, len) == 0) {
    fprintf(stderr, "Seeded RNG with getentropy()\n");
    seed_generated = true;
  }
#endif

#ifdef HAVE_ARC4RANDOM_BUF
  /* Most (all?) of the BSDs have this seeder. Use it for the reasons
     above. Also available on Linux with libbsd, but we don't check
     for that. */
  if (!seed_generated) {
    arc4random_buf(seeds, len);
    fprintf(stderr, "Seeded RNG with arc4random\n");
    seed_generated = true;
  }
#endif

#ifdef WIN32
  if (!seed_generated) {
    /* Use the Win32 bcrypto RNG interface */
    if (BCryptGenRandom(NULL, (PUCHAR) seeds, len,
                        BCRYPT_USE_SYSTEM_PREFERRED_RNG) == STATUS_SUCCESS) {
      fprintf(stderr, "Seeding RNG with BCryptGenRandom()\n");
      seed_generated = true;
    }
  }
#endif

#ifdef HAVE_DEV_URANDOM
  if (!seed_generated) {
    /* Seed from /dev/urandom if available */
    int fd;

    fd = open("/dev/urandom", O_RDONLY);
    if (fd >= 0) {
      int r = read(fd, (void *) seeds, len);
      close(fd);
      if (r != len) {
        fprintf(stderr, "Couldn't read from /dev/urandom! Resorting to normal "
                        "seeding method.\n");
      } else {
        fprintf(stderr, "Seeding RNG with /dev/urandom\n");
        seed_generated = true;
      }
    } else {
      fprintf(stderr, "Couldn't open /dev/urandom to seed random number "
                      "generator. Resorting to normal seeding method.\n");
    }
  }
#endif

  if (!seed_generated) {
    /* Default seeder. Pick a seed that's slightly random */
#ifdef WIN32
    seeds[0] = (uint64_t) time(NULL);
    seeds[1] = (uint64_t) GetCurrentProcessId() + stream_count;
#else
    seeds[0] = (uint64_t) time(NULL);
    seeds[1] = (uint64_t) getpid() + stream_count;
#endif
    stream_count += 1;
  }
}