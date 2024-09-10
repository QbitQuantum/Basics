size32_t aesEncryptWithRSAEncryptedKey(MemoryBuffer &out, size32_t inSz, const void *inBytes, const CLoadedKey &publicKey)
{
    // create random AES key and IV
    char randomAesKey[aesMaxKeySize];
    char randomIV[aesBlockSize];
    fillRandomData(aesMaxKeySize, randomAesKey);
    fillRandomData(aesBlockSize, randomIV);

    size32_t startSz = out.length();
    DelayedSizeMarker mark(out);
    publicKeyEncrypt(out, aesMaxKeySize, randomAesKey, publicKey);
    mark.write();
    out.append(aesBlockSize, randomIV);

    DelayedSizeMarker aesSz(out);
    aesEncrypt(out, inSz, inBytes, aesMaxKeySize, randomAesKey, randomIV);
    aesSz.write();
    return out.length()-startSz;
}