WOLFSSL_API void wc_Md5Final(Md5* md5, byte* hash)
{
    hashFinal((wolfssl_TI_Hash *)md5, hash, SHAMD5_ALGO_MD5, MD5_DIGEST_SIZE) ;
}