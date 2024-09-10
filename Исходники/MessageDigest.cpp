void MessageDigest::digest(const char *key, const int key_len,
                           const char *data, const int data_len,
                           unsigned char *md, unsigned int *mdLen)
               throw (SecurityException) 
{
   if (!key)
      throw SecurityException(INPUT_PARAMETER_IS_NULL, " - key.");
   if (!data)
      throw SecurityException(INPUT_PARAMETER_IS_NULL, " - data.");
   if (!md)
      throw SecurityException(INPUT_PARAMETER_IS_NULL, " - md.");


   getMutex();
   const EVP_MD *evp_md = EVP_sha256();
   HMAC(evp_md, (const void *) key, key_len,
                          (const unsigned char *) data, data_len,
                          (unsigned char *) &md[0], mdLen);
   releaseMutex();
}