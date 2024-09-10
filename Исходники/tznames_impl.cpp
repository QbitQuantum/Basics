const UChar *ZNStringPool::get(const UChar *s, UErrorCode &status) {
    const UChar *pooledString;
    if (U_FAILURE(status)) {
        return &EmptyString;
    }

    pooledString = static_cast<UChar *>(uhash_get(fHash, s));
    if (pooledString != NULL) {
        return pooledString;
    }

    int32_t length = u_strlen(s);
    int32_t remainingLength = POOL_CHUNK_SIZE - fChunks->fLimit;
    if (remainingLength <= length) {
        U_ASSERT(length < POOL_CHUNK_SIZE);
        if (length >= POOL_CHUNK_SIZE) {
            status = U_INTERNAL_PROGRAM_ERROR;
            return &EmptyString;
        }
        ZNStringPoolChunk *oldChunk = fChunks;
        fChunks = new ZNStringPoolChunk;
        if (fChunks == NULL) {
            status = U_MEMORY_ALLOCATION_ERROR;
            return &EmptyString;
        }
        fChunks->fNext = oldChunk;
    }
    
    UChar *destString = &fChunks->fStrings[fChunks->fLimit];
    u_strcpy(destString, s);
    fChunks->fLimit += (length + 1);
    uhash_put(fHash, destString, destString, &status);
    return destString;
}        