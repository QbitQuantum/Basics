static inline void
write_wchars(wchar_t buf[], size_t start, size_t end, bool escape,
             bool open_field, bool close_field) {
  size_t j;
  if (escape) {
    if (open_field)
      putwchar(L'"');
    for (j = start; j <= end; ++j) {
      if (buf[IDX(j)] == L'"')
        putwchar(L'"');
      if (putwchar(buf[IDX(j)]) == WEOF) {
        fprintf(stderr, "putwchar error");
        exit(1);
      }
    }
    if (close_field)
      putwchar(L'"');
  } else {
    for (j = start; j <= end; ++j) {
      if (putwchar(buf[IDX(j)]) == WEOF) {
        fprintf(stderr, "putwchar error");
        exit(1);
      }
    }
  }
}