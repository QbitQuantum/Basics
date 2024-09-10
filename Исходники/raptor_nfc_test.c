int
main (int argc, char *argv[]) 
{
  const char *program = raptor_basename(argv[0]);
  const char *filename;
  FILE *fh;
  int rc = 0;
  unsigned int line = 1;
  size_t max_c2_len = 0;
  size_t max_c4_len = 0;
  int passes = 0;
  int fails = 0;

  if(argc != 2) {
    fprintf(stderr,
            "USAGE %s [path to NormalizationTest.txt]\n"
            "Get it at http://unicode.org/Public/UNIDATA/NormalizationTest.txt\n",
            program);
    return 1;
  }
  
  filename = argv[1];
  fh = fopen(filename, "r");
  if(!fh) {
    fprintf(stderr, "%s: file '%s' open failed - %s\n",
            program, filename, strerror(errno));
    return 1;
  }

#define LINE_BUFFER_SIZE 1024

/* FIXME big enough for Unicode 4 (c2 max 16; c4 max 33) */
#define UNISTR_SIZE 40

  for(;!feof(fh); line++) {
    char buffer[LINE_BUFFER_SIZE];
    char *p, *start;
    unsigned char column2[UNISTR_SIZE];
    unsigned char column4[UNISTR_SIZE];
    size_t column2_len, column4_len;
    int nfc_rc;
    int error;
    
    p = fgets(buffer, LINE_BUFFER_SIZE, fh);
    if(!p) {
      if(ferror(fh)) {
        fprintf(stderr, "%s: file '%s' read failed - %s\n",
                program, filename, strerror(errno));
        rc = 1;
        break;
      }
      /* assume feof */
      break;
    };

#if 0
    fprintf(stderr, "%s:%d: line '%s'\n", program, line, buffer);
#endif

    /* skip lines */
    if(*p == '@' || *p == '#')
      continue;

    if(line != 56)
      continue;
    

    /* skip column 1 */
    while(*p++ != ';')
      ;

    /* read column 2 into column2, column2_len */
    start = p;
    /* find end column 2 */
    while(*p++ != ';')
      ;

    column2_len = decode_to_utf8(column2, UNISTR_SIZE, start, p-1);
    if(column2_len > max_c2_len)
      max_c2_len = column2_len;
    
    /* skip column 3 */
    while(*p++ != ';')
      ;

    /* read column 4 into column4, column4_len */
    start = p;
    /* find end column 4 */
    while(*p++ != ';')
      ;

    column4_len = decode_to_utf8(column4, UNISTR_SIZE, start, p-1);
    if(column4_len > max_c4_len)
      max_c4_len = column4_len;

    if(!raptor_unicode_check_utf8_string(column2, column2_len)) {
      fprintf(stderr, "%s:%d: UTF8 column 2 failed on: '", filename, line);
      utf8_print(column2, column2_len, stderr);
      fputs("'\n", stderr);
      fails++;
    } else
      passes++;

    /* Column 2 must be NFC */
    nfc_rc = raptor_nfc_check(column2, column2_len, &error);
    if(!nfc_rc) {
      fprintf(stderr, "%s:%d: NFC column 2 failed on: '", filename, line);
      utf8_print(column2, column2_len, stderr);
      fprintf(stderr, "' at byte %d of %d\n", error, (int)column2_len);
      fails++;
    } else
      passes++;

    if(column2_len == column4_len && !memcmp(column2, column4, column2_len))
      continue;

    if(!raptor_unicode_check_utf8_string(column4, column4_len)) {
      fprintf(stderr, "%s:%d: UTF8 column 4 failed on: '", filename, line);
      utf8_print(column4, column4_len, stderr);
      fputs("'\n", stderr);
      fails++;
    } else
      passes++;

    /* Column 4 must be in NFC */
    nfc_rc = raptor_nfc_check(column4, column4_len, &error);
    if(!nfc_rc) {
      fprintf(stderr, "%s:%d: NFC column 4 failed on: '", filename, line);
      utf8_print(column4, column4_len, stderr);
      fprintf(stderr, "' at byte %d of %d\n", error, (int)column4_len);
      fails++;
    } else
      passes++;
  }

  fclose(fh);

  fprintf(stderr, "%s: max column 2 len: %d,  max column 4 len: %d\n", program,
          (int)max_c2_len, (int)max_c4_len);
  fprintf(stderr, "%s: passes: %d fails: %d\n", program,
          passes, fails);

  return rc;
}