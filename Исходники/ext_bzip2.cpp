Variant f_bzdecompress(CStrRef source, int small /* = 0 */) {
  char *dest;
  int source_len = source.length();
  int error;
  uint64 size = 0;
  bz_stream bzs;

  bzs.bzalloc = NULL;
  bzs.bzfree = NULL;

  if (BZ2_bzDecompressInit(&bzs, 0, small) != BZ_OK) {
    return false;
  }

  bzs.next_in = (char *) source.c_str();
  bzs.avail_in = source_len;

  /* in most cases bz2 offers at least 2:1 compression, so we use that as our base */
  bzs.avail_out = source_len * 2;
  bzs.next_out = dest = (char *) malloc(bzs.avail_out + 1);
  if (!dest) {
    return BZ_MEM_ERROR;
  }

  while ((error = BZ2_bzDecompress(&bzs)) == BZ_OK && bzs.avail_in > 0) {
    /* compression is better then 2:1, need to allocate more memory */
    bzs.avail_out = source_len;
    size = (bzs.total_out_hi32 * (unsigned int) -1) + bzs.total_out_lo32;
    dest = (char *) Util::safe_realloc(dest, bzs.avail_out + 1);
    bzs.next_out = dest + size;
  }

  if (error == BZ_STREAM_END || error == BZ_OK) {
    size = (bzs.total_out_hi32 * (unsigned int) -1) + bzs.total_out_lo32;
    dest = (char *)Util::safe_realloc(dest, size + 1);
    dest[size] = '\0';
    String ret = String(dest, size, AttachString);
    BZ2_bzDecompressEnd(&bzs);
    return ret;
  } else {
    free(dest);
    BZ2_bzDecompressEnd(&bzs);
    return error;
  }
}