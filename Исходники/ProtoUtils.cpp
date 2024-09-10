void 
CRegProtocol::DecryptData(BufferObj &cipherText, 
                          BufferObj &iv,
                          BufferObj &encrKey, 
                          BufferObj &authKey, 
                          BufferObj &plainText)
{
    EVP_CIPHER_CTX ctx;
    if(0 == EVP_DecryptInit(&ctx, EVP_aes_128_cbc(), encrKey.GetBuf(), iv.GetBuf()))
    {
        TUTRACE((TUTRACE_ERR, "RPROTO: DecryptInit failed\n"));
        throw RPROT_ERR_CRYPTO;
    }

    BufferObj buf;

    int bufLen = 1024;
    uint8 outBuf[1024];
    int outLen, currentLength;
    //block size = 1024 bytes - 128 bits, 
    //leave 128 bits at the end to accommodate any possible padding 
    //and avoid a buffer overflow
    int blockSize = bufLen - SIZE_128_BITS; 
    int length = cipherText.Length();

    uint8 *bufPtr = cipherText.GetBuf();
 
    while(length)
    {
        if(length > blockSize)
            currentLength = blockSize;
        else
            currentLength = length;

        if(0 == EVP_DecryptUpdate(&ctx, outBuf, &outLen, bufPtr, currentLength))
        {
            TUTRACE((TUTRACE_ERR, "RPROTO: DecryptUpdate failed\n"));
            throw RPROT_ERR_CRYPTO;
        }

        buf.Append(outLen, outBuf);
        bufPtr += currentLength;
        length -= currentLength;
    }

    if(0 == EVP_DecryptFinal(&ctx, outBuf, &outLen))
    {
        TUTRACE((TUTRACE_ERR, "RPROTO: DecryptFinal failed\n"));
        throw RPROT_ERR_CRYPTO;
    }

    buf.Append(outLen, outBuf);

    //Validate the mac at the end of the decrypted buffer
    //uint8 *mac = buf.GetBuf()+(buf.Length()-SIZE_256_BITS);//get the last 256 bits
    //if(0 == ValidateMac(BufferObj(buf.GetBuf(), buf.Length()-SIZE_256_BITS), mac, authKey))
    //{
    //    TUTRACE((TUTRACE_ERR, "RPROTO: Mac validation failed\n"));
    //    throw RPROT_ERR_INVALID_VALUE;
    //}
    //plainText.Append(buf.Length()-SIZE_256_BITS, buf.GetBuf());
    plainText.Append(buf.Length(), buf.GetBuf());
    plainText.Rewind(plainText.Length());
}