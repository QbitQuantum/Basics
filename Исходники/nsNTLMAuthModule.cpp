/**
 * NTLM_Hash computes the NTLM hash of the given password.
 *
 * @param password
 *        null-terminated unicode password.
 * @param hash
 *        16-byte result buffer
 */
static void
NTLM_Hash(const nsString &password, unsigned char *hash)
{
  uint32_t len = password.Length();
  uint8_t *passbuf;
  
#ifdef IS_BIG_ENDIAN
  passbuf = (uint8_t *) malloc(len * 2);
  WriteUnicodeLE(passbuf, password.get(), len);
#else
  passbuf = (uint8_t *) password.get();
#endif

  md4sum(passbuf, len * 2, hash);

#ifdef IS_BIG_ENDIAN
  ZapBuf(passbuf, len * 2);
  free(passbuf);
#endif
}