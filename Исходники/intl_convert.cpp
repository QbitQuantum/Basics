void intl_convert_utf16_to_utf8(char** target, int* target_len,
                                const UChar* src, int  src_len,
                                UErrorCode*  status) {
  char* dst_buf = NULL;
  int32_t dst_len;

  /* Determine required destination buffer size (pre-flighting). */
  *status = U_ZERO_ERROR;
  u_strToUTF8(NULL, 0, &dst_len, src, src_len, status);

  /* Bail out if an unexpected error occured.
   * (U_BUFFER_OVERFLOW_ERROR means that *target buffer is not large enough).
   * (U_STRING_NOT_TERMINATED_WARNING usually means that the input string
   * is empty).
   */
  if (*status != U_BUFFER_OVERFLOW_ERROR &&
      *status != U_STRING_NOT_TERMINATED_WARNING) {
    return;
  }

  // Allocate memory for the destination buffer (it will be zero-terminated).
  dst_buf = (char *)malloc(dst_len + 1);

  /* Convert source string from UTF-16 to UTF-8. */
  *status = U_ZERO_ERROR;
  u_strToUTF8(dst_buf, dst_len, NULL, src, src_len, status);
  if (U_FAILURE(*status)) {
    free(dst_buf);
    return;
  }

  /* U_STRING_NOT_TERMINATED_WARNING is OK for us => reset 'status'. */
  *status = U_ZERO_ERROR;

  dst_buf[dst_len] = 0;
  *target = dst_buf;
  *target_len = dst_len;
}