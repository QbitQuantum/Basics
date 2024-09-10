// generates SHA-1 hash of input
BOOL open_hash(void)
{
    BOOL bStatus = FALSE;

    // create hash object
    if (CryptCreateHash(hProv, CALG_SHA, 0, 0, &hHash)) {
        // hash input
        bStatus = CryptHashData(hHash, input, lstrlen(input), 0);
    }

    return bStatus;
}