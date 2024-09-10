Term Yap_StringToNumberTerm(char *s, encoding_t *encp) {
  CACHE_REGS
  int sno;
  Term t;

  sno = Yap_open_buf_read_stream(s, strlen(s), encp, MEM_BUF_USER);
  if (sno < 0)
    return FALSE;
  if (encp)
    GLOBAL_Stream[sno].encoding = *encp;
  else
    GLOBAL_Stream[sno].encoding = LOCAL_encoding;
#ifdef __ANDROID__
  while (*s && isblank(*s) && Yap_wide_chtype(*s) == BS)
    s++;
#else
  while (*s && iswblank(*s++))
    ;
#endif
  t = Yap_scan_num(GLOBAL_Stream + sno);
  if (LOCAL_Error_TYPE == SYNTAX_ERROR)
    LOCAL_Error_TYPE = YAP_NO_ERROR;
  Yap_CloseStream(sno);
  UNLOCK(GLOBAL_Stream[sno].streamlock);
  return t;
}