static int gen_sha2(
    uchar * inbufp,
    int bsize,
    uchar * outbufp)
{
    CRYPT_CONTEXT hashContext;
    uchar hash[40];
    int ansr;

    memset(hash, 0, 40);
    if (cryptInit() != CRYPT_OK)
    {
        FATAL(MSG_ERROR, "initializing cryptlib");
    }
    if (cryptCreateContext(&hashContext, CRYPT_UNUSED, CRYPT_ALGO_SHA2) != CRYPT_OK)
    {
        FATAL(MSG_ERROR, "creating cryptlib hash context");
    }
    cryptEncrypt(hashContext, inbufp, bsize);
    cryptEncrypt(hashContext, inbufp, 0);
    cryptGetAttributeString(hashContext, CRYPT_CTXINFO_HASHVALUE, hash, &ansr);
    cryptDestroyContext(hashContext);
    cryptEnd();
    memcpy(outbufp, hash, ansr);
    return ansr;
}