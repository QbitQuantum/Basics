void
rng_gen_seed(rust_kernel* kernel, uint8_t* dest, size_t size) {
#ifdef __WIN32__
    HCRYPTPROV hProv;
    kernel->win32_require
    (_T("CryptAcquireContext"),
     CryptAcquireContext(&hProv, NULL, NULL, PROV_RSA_FULL,
                         CRYPT_VERIFYCONTEXT|CRYPT_SILENT));
    kernel->win32_require
    (_T("CryptGenRandom"), CryptGenRandom(hProv, size, (BYTE*) dest));
    kernel->win32_require
    (_T("CryptReleaseContext"), CryptReleaseContext(hProv, 0));
#else
    int fd = open("/dev/urandom", O_RDONLY);
    if (fd == -1)
        kernel->fatal("error opening /dev/urandom: %s", strerror(errno));
    size_t amount = 0;
    do {
        ssize_t ret = read(fd, dest+amount, size-amount);
        if (ret < 0)
            kernel->fatal("error reading /dev/urandom: %s", strerror(errno));
        else if (ret == 0)
            kernel->fatal("somehow hit eof reading from /dev/urandom");
        amount += (size_t)ret;
    } while (amount < size);
    int ret = close(fd);
    // FIXME #3697: Why does this fail sometimes?
    if (ret != 0)
        kernel->log(log_warn, "error closing /dev/urandom: %s",
                    strerror(errno));
#endif
}