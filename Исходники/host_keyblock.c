VbKeyBlockHeader* KeyBlockCreate(const VbPublicKey* data_key,
                                 const VbPrivateKey* signing_key,
                                 uint64_t flags) {

  VbKeyBlockHeader* h;
  uint64_t signed_size = sizeof(VbKeyBlockHeader) + data_key->key_size;
  uint64_t block_size = (signed_size + SHA512_DIGEST_SIZE +
                         (signing_key ?
                          siglen_map[signing_key->algorithm] : 0));
  uint8_t* data_key_dest;
  uint8_t* block_sig_dest;
  uint8_t* block_chk_dest;
  VbSignature *sigtmp;

  /* Allocate key block */
  h = (VbKeyBlockHeader*)malloc(block_size);
  if (!h)
    return NULL;
  data_key_dest = (uint8_t*)(h + 1);
  block_chk_dest = data_key_dest + data_key->key_size;
  block_sig_dest = block_chk_dest + SHA512_DIGEST_SIZE;

  Memcpy(h->magic, KEY_BLOCK_MAGIC, KEY_BLOCK_MAGIC_SIZE);
  h->header_version_major = KEY_BLOCK_HEADER_VERSION_MAJOR;
  h->header_version_minor = KEY_BLOCK_HEADER_VERSION_MINOR;
  h->key_block_size = block_size;
  h->key_block_flags = flags;

  /* Copy data key */
  PublicKeyInit(&h->data_key, data_key_dest, data_key->key_size);
  PublicKeyCopy(&h->data_key, data_key);

  /* Set up signature structs so we can calculate the signatures */
  SignatureInit(&h->key_block_checksum, block_chk_dest,
                SHA512_DIGEST_SIZE, signed_size);
  if (signing_key)
    SignatureInit(&h->key_block_signature, block_sig_dest,
                  siglen_map[signing_key->algorithm], signed_size);
  else
    Memset(&h->key_block_signature, 0, sizeof(VbSignature));

  /* Calculate checksum */
  sigtmp = CalculateChecksum((uint8_t*)h, signed_size);
  SignatureCopy(&h->key_block_checksum, sigtmp);
  free(sigtmp);

  /* Calculate signature */
  if (signing_key) {
    sigtmp = CalculateSignature((uint8_t*)h, signed_size, signing_key);
    SignatureCopy(&h->key_block_signature, sigtmp);
    free(sigtmp);
  }

  /* Return the header */
  return h;
}