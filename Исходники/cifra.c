 static void read_entropy(uint8_t *entropy, size_t size)
 {
    NTSTATUS nts = 0;
    BCRYPT_ALG_HANDLE hAlgorithm = 0;

    nts = BCryptOpenAlgorithmProvider(&hAlgorithm, BCRYPT_RNG_ALGORITHM, NULL, 0);

    if (BCRYPT_SUCCESS(nts)) {
        nts = BCryptGenRandom(hAlgorithm, (PUCHAR)entropy, (ULONG)size, 0);

        (void)BCryptCloseAlgorithmProvider(hAlgorithm, 0); 
    } 

    if (!BCRYPT_SUCCESS(nts)) {
        perror("ptls_minicrypto_random_bytes: could not open BCrypt RNG Algorithm");
        abort();
    }
}