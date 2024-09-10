bool SecureStorage_RemoveItem(const SecureStorageS *storage, const unsigned char *sKey, int16_t keyLen) {
  int16_t saltLen = 0;
  bool ret = false, ret1 = false;
  unsigned char *caEncKey = NULL, *rKey = NULL, *caKey = NULL;
  unsigned char cahKey[SHA256_LEN + UTILS_STR_LEN_SIZE + 1];

  if (storage == NULL || sKey == NULL) {
    snprintf(errStr, sizeof(errStr), "SecureStorage_RemoveItem: Storage and key must not be NULL");
    return false;
  }
  if (keyLen <= 0) {
    snprintf(errStr, sizeof(errStr), "SecureStorage_RemoveItem: key len %d must be positives\n", keyLen);
    return false;
  }
  if (READABLE_STORAGE == true)
    saltLen = 0;
  else if (Utils_GetCharArrayLen(storage->caSalt, &saltLen, KEY_VAL_MIN_STR_LEN, KEY_VAL_MAX_STR_LEN) == false)
    return false;
  if (generateAlignedCharAray(sKey, keyLen, storage->caSalt, saltLen, &caKey) == false) return false;
  if (isLengthValid(caKey, KEY_VAL_MIN_STR_LEN, KEY_VAL_MAX_STR_LEN - 1) == false || getRandomFromKey(storage, caKey, cahKey, &rKey) == false) {
    Utils_Free(caKey);
    return false;
  }
  ret1 = clearKey(storage, cahKey);
  if (ret1 == false) { // continue to try to remove the "real" key value
    snprintf(errStr, sizeof(errStr), "Error: key for random '%s' was not found", cahKey);
  }
  ret = encrypt(caKey, rKey, storage->caSecret, &caEncKey);
  Utils_Free(rKey);
  if (ret == false) {
    Utils_Free(caKey);
    return false;
  }
  if (clearKey(storage, caEncKey) == false) {
    Utils_Free(caEncKey);
    snprintf(errStr, sizeof(errStr), "Error: key '%s' was not found", caKey);
    return false;
  }
  Utils_Free(caKey);
  Utils_Free(caEncKey);
  return ret1;
}