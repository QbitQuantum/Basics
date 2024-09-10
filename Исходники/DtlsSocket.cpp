SrtpSessionKeys* DtlsSocket::getSrtpSessionKeys() {
  // TODO(pedro): probably an exception candidate
  assert(mHandshakeCompleted);

  SrtpSessionKeys* keys = new SrtpSessionKeys();

  unsigned char material[SRTP_MASTER_KEY_LEN << 1];
  if (!SSL_export_keying_material(mSsl, material, sizeof(material), "EXTRACTOR-dtls_srtp", 19, NULL, 0, 0)) {
    return keys;
  }

  size_t offset = 0;

  memcpy(keys->clientMasterKey, &material[offset], SRTP_MASTER_KEY_KEY_LEN);
  offset += SRTP_MASTER_KEY_KEY_LEN;
  memcpy(keys->serverMasterKey, &material[offset], SRTP_MASTER_KEY_KEY_LEN);
  offset += SRTP_MASTER_KEY_KEY_LEN;
  memcpy(keys->clientMasterSalt, &material[offset], SRTP_MASTER_KEY_SALT_LEN);
  offset += SRTP_MASTER_KEY_SALT_LEN;
  memcpy(keys->serverMasterSalt, &material[offset], SRTP_MASTER_KEY_SALT_LEN);
  offset += SRTP_MASTER_KEY_SALT_LEN;
  keys->clientMasterKeyLen = SRTP_MASTER_KEY_KEY_LEN;
  keys->serverMasterKeyLen = SRTP_MASTER_KEY_KEY_LEN;
  keys->clientMasterSaltLen = SRTP_MASTER_KEY_SALT_LEN;
  keys->serverMasterSaltLen = SRTP_MASTER_KEY_SALT_LEN;

  return keys;
}