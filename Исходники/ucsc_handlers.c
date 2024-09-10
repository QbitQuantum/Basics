static void R_warnHandler(char *format, va_list args) {
  char warn_buf[WARN_BUF_SIZE];
  vsnprintf(warn_buf, WARN_BUF_SIZE, format, args);
  warning(warn_buf);
}