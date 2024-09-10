int
main(int argc, char *argv[])
{
    START(argc, argv, "pmem_map");

    if (argc != 2)
        FATAL("usage: %s file", argv[0]);

    int fd;
    void *addr;

    fd = OPEN(argv[1], O_RDWR);

    struct stat stbuf;
    FSTAT(fd, &stbuf);

    char pat[CHECK_BYTES];
    char buf[CHECK_BYTES];

    addr = pmem_map(fd);
    if (addr == NULL) {
        OUT("!pmem_map");
        goto err;
    }

    /* write some pattern to the file */
    memset(pat, 0x5A, CHECK_BYTES);
    WRITE(fd, pat, CHECK_BYTES);


    if (memcmp(pat, addr, CHECK_BYTES))
        OUT("%s: first %d bytes do not match",
            argv[1], CHECK_BYTES);

    /* fill up mapped region with new pattern */
    memset(pat, 0xA5, CHECK_BYTES);
    memcpy(addr, pat, CHECK_BYTES);

    MUNMAP(addr, stbuf.st_size);

    LSEEK(fd, (off_t)0, SEEK_SET);
    if (READ(fd, buf, CHECK_BYTES) == CHECK_BYTES) {
        if (memcmp(pat, buf, CHECK_BYTES))
            OUT("%s: first %d bytes do not match",
                argv[1], CHECK_BYTES);
    }

    CLOSE(fd);

    /* re-open the file with read-only access */
    fd = OPEN(argv[1], O_RDONLY);

    addr = pmem_map(fd);
    if (addr != NULL) {
        MUNMAP(addr, stbuf.st_size);
        OUT("expected pmem_map failure");
    }

err:
    CLOSE(fd);

    DONE(NULL);
}