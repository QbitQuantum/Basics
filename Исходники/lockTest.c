static void
testLocking(
    const char* const   pathname,       /* pathname of file */
    const size_t        len,            /* length of memory-mapped portion */
    useconds_t          maxInterval)    /* maximum sleep interval */
{
    const int   fd = open(pathname, O_RDWR, 0);

    log_assert(len >= 0);

    if (fd == -1) {
        (void)fprintf(stderr, "%ld: Couldn't open file \"%s\": %s\n",
            (long)getpid(), pathname, strerror(errno));
    }
    else {
        /*
         * Memory-map the file.
         */
        void*   addr = mmap(0, len, PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);

        if (addr == MAP_FAILED) {
            (void)fprintf(stderr, "%ld: Couldn't memory-map file \"%s\": %s\n",
                (long)getpid(), pathname, strerror(errno));
        }
        else {
            log_assert(addr != NULL);

            while (!done) {
                randomSleep(maxInterval);

                /*
                 * Lock the file.
                 */
                if (!lockFile(fd, len))
                    break;
                lockCount++;

                /*
                 * Change the file.
                 */
                (void)memset(addr, 1+*(char*)addr, len);

                randomSleep(maxInterval);

                /*
                 * Unlock the file.
                 */
                if (!unlockFile(fd, len))
                    break;
            }                           /* while not done */

            (void)munmap(addr, len);
        }                               /* "addr" is mapped */

        (void)close(fd);
    }                                   /* "fd" is open */
}