/* unserialize a selector */
U_CAPI UConverterSelector* U_EXPORT2
ucnvsel_openFromSerialized(const void* buffer, int32_t length, UErrorCode* status) {
  // check if already failed
  if (U_FAILURE(*status)) {
    return NULL;
  }
  // ensure args make sense!
  const uint8_t *p = (const uint8_t *)buffer;
  if (length <= 0 ||
      (length > 0 && (p == NULL || (U_POINTER_MASK_LSB(p, 3) != 0)))
  ) {
    *status = U_ILLEGAL_ARGUMENT_ERROR;
    return NULL;
  }
  // header
  if (length < 32) {
    // not even enough space for a minimal header
    *status = U_INDEX_OUTOFBOUNDS_ERROR;
    return NULL;
  }
  const DataHeader *pHeader = (const DataHeader *)p;
  if (!(
    pHeader->dataHeader.magic1==0xda &&
    pHeader->dataHeader.magic2==0x27 &&
    pHeader->info.dataFormat[0] == 0x43 &&
    pHeader->info.dataFormat[1] == 0x53 &&
    pHeader->info.dataFormat[2] == 0x65 &&
    pHeader->info.dataFormat[3] == 0x6c
  )) {
    /* header not valid or dataFormat not recognized */
    *status = U_INVALID_FORMAT_ERROR;
    return NULL;
  }
  if (pHeader->info.formatVersion[0] != 1) {
    *status = U_UNSUPPORTED_ERROR;
    return NULL;
  }
  uint8_t* swapped = NULL;
  if (pHeader->info.isBigEndian != U_IS_BIG_ENDIAN ||
      pHeader->info.charsetFamily != U_CHARSET_FAMILY
  ) {
    // swap the data
    UDataSwapper *ds =
      udata_openSwapperForInputData(p, length, U_IS_BIG_ENDIAN, U_CHARSET_FAMILY, status);
    int32_t totalSize = ucnvsel_swap(ds, p, -1, NULL, status);
    if (U_FAILURE(*status)) {
      udata_closeSwapper(ds);
      return NULL;
    }
    if (length < totalSize) {
      udata_closeSwapper(ds);
      *status = U_INDEX_OUTOFBOUNDS_ERROR;
      return NULL;
    }
    swapped = (uint8_t*)uprv_malloc(totalSize);
    if (swapped == NULL) {
      udata_closeSwapper(ds);
      *status = U_MEMORY_ALLOCATION_ERROR;
      return NULL;
    }
    ucnvsel_swap(ds, p, length, swapped, status);
    udata_closeSwapper(ds);
    if (U_FAILURE(*status)) {
      uprv_free(swapped);
      return NULL;
    }
    p = swapped;
    pHeader = (const DataHeader *)p;
  }
  if (length < (pHeader->dataHeader.headerSize + 16 * 4)) {
    // not even enough space for the header and the indexes
    uprv_free(swapped);
    *status = U_INDEX_OUTOFBOUNDS_ERROR;
    return NULL;
  }
  p += pHeader->dataHeader.headerSize;
  length -= pHeader->dataHeader.headerSize;
  // indexes
  const int32_t *indexes = (const int32_t *)p;
  if (length < indexes[UCNVSEL_INDEX_SIZE]) {
    uprv_free(swapped);
    *status = U_INDEX_OUTOFBOUNDS_ERROR;
    return NULL;
  }
  p += UCNVSEL_INDEX_COUNT * 4;
  // create and populate the selector object
  UConverterSelector* sel = (UConverterSelector*)uprv_malloc(sizeof(UConverterSelector));
  char **encodings =
    (char **)uprv_malloc(
      indexes[UCNVSEL_INDEX_NAMES_COUNT] * sizeof(char *));
  if (sel == NULL || encodings == NULL) {
    uprv_free(swapped);
    uprv_free(sel);
    uprv_free(encodings);
    *status = U_MEMORY_ALLOCATION_ERROR;
    return NULL;
  }
  uprv_memset(sel, 0, sizeof(UConverterSelector));
  sel->pvCount = indexes[UCNVSEL_INDEX_PV_COUNT];
  sel->encodings = encodings;
  sel->encodingsCount = indexes[UCNVSEL_INDEX_NAMES_COUNT];
  sel->encodingStrLength = indexes[UCNVSEL_INDEX_NAMES_LENGTH];
  sel->swapped = swapped;
  // trie
  sel->trie = utrie2_openFromSerialized(UTRIE2_16_VALUE_BITS,
                                        p, indexes[UCNVSEL_INDEX_TRIE_SIZE], NULL,
                                        status);
  p += indexes[UCNVSEL_INDEX_TRIE_SIZE];
  if (U_FAILURE(*status)) {
    ucnvsel_close(sel);
    return NULL;
  }
  // bit vectors
  sel->pv = (uint32_t *)p;
  p += sel->pvCount * 4;
  // encoding names
  char* s = (char*)p;
  for (int32_t i = 0; i < sel->encodingsCount; ++i) {
    sel->encodings[i] = s;
    s += uprv_strlen(s) + 1;
  }
  p += sel->encodingStrLength;

  return sel;
}