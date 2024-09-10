int main(int argc, char **argv) {
    /* expect the first argument to be the dump file */
    if (argc <= 1) {
        printf("Usage: %s <dump.rdb>\n", argv[0]);
        exit(0);
    }

    int fd;
    off_t size;
    struct stat stat;
    void *data;

    fd = open(argv[1], O_RDONLY);
    if (fd < 1) {
        ERROR("Cannot open file: %s\n", argv[1]);
    }
    if (fstat(fd, &stat) == -1) {
        ERROR("Cannot stat: %s\n", argv[1]);
    } else {
        size = stat.st_size;
    }

    if (sizeof(size_t) == sizeof(int32_t) && size >= INT_MAX) {
        ERROR("Cannot check dump files >2GB on a 32-bit platform\n");
    }

    data = mmap(NULL, size, PROT_READ, MAP_SHARED, fd, 0);
    if (data == MAP_FAILED) {
        ERROR("Cannot mmap: %s\n", argv[1]);
    }

    /* Initialize static vars */
    positions[0].data = data;
    positions[0].size = size;
    positions[0].offset = 0;
    errors.level = 0;

    /* Object types */
    sprintf(types[REDIS_STRING], "STRING");
    sprintf(types[REDIS_LIST], "LIST");
    sprintf(types[REDIS_SET], "SET");
    sprintf(types[REDIS_ZSET], "ZSET");
    sprintf(types[REDIS_HASH], "HASH");

    /* Object types only used for dumping to disk */
    sprintf(types[REDIS_EXPIRETIME], "EXPIRETIME");
    sprintf(types[REDIS_SELECTDB], "SELECTDB");
    sprintf(types[REDIS_EOF], "EOF");

    /* Double constants initialization */
    R_Zero = 0.0;
    R_PosInf = 1.0/R_Zero;
    R_NegInf = -1.0/R_Zero;
    R_Nan = R_Zero/R_Zero;

    process();

    munmap(data, size);
    close(fd);
    return 0;
}