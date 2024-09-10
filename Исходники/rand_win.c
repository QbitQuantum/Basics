int RAND_poll(void)
{
    MEMORYSTATUS mst;
# ifndef RAND_WINDOWS_USE_BCRYPT
    HCRYPTPROV hProvider;
# endif
    DWORD w;
    BYTE buf[64];

# ifdef RAND_WINDOWS_USE_BCRYPT
    if (BCryptGenRandom(NULL, buf, (ULONG)sizeof(buf), BCRYPT_USE_SYSTEM_PREFERRED_RNG) == STATUS_SUCCESS) {
        RAND_add(buf, sizeof(buf), sizeof(buf));
    }
# else
    /* poll the CryptoAPI PRNG */
    /* The CryptoAPI returns sizeof(buf) bytes of randomness */
    if (CryptAcquireContextW(&hProvider, NULL, NULL, PROV_RSA_FULL, CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) {
        if (CryptGenRandom(hProvider, (DWORD)sizeof(buf), buf) != 0) {
            RAND_add(buf, sizeof(buf), sizeof(buf));
        }
        CryptReleaseContext(hProvider, 0);
    }

    /* poll the Pentium PRG with CryptoAPI */
    if (CryptAcquireContextW(&hProvider, NULL, INTEL_DEF_PROV, PROV_INTEL_SEC, CRYPT_VERIFYCONTEXT | CRYPT_SILENT)) {
        if (CryptGenRandom(hProvider, (DWORD)sizeof(buf), buf) != 0) {
            RAND_add(buf, sizeof(buf), sizeof(buf));
        }
        CryptReleaseContext(hProvider, 0);
    }
# endif

    /* timer data */
    readtimer();

    /* memory usage statistics */
    GlobalMemoryStatus(&mst);
    RAND_add(&mst, sizeof(mst), 1);

    /* process ID */
    w = GetCurrentProcessId();
    RAND_add(&w, sizeof(w), 1);

    return (1);
}