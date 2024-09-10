UErrorCode convsample_06()
{
  printf("\n\n==============================================\n"
         "Sample 06: C: frequency distribution of letters in a UTF-8 document\n");

  FILE *f;
  int32_t count;
  char inBuf[BUFFERSIZE];
  const char *source;
  const char *sourceLimit;
  UChar *uBuf;
  int32_t uBufSize = 0;
  UConverter *conv;
  UErrorCode status = U_ZERO_ERROR;
  uint32_t letters=0, total=0;

  CharFreqInfo   *info;
  UChar32   charCount = 0x10000;  /* increase this if you want to handle non bmp.. todo: automatically bump it.. */
  UChar32   p;

  uint32_t ie = 0;
  uint32_t gh = 0;
  UChar32 l = 0;

  f = fopen("data06.txt", "r");
  if(!f)
  {
    fprintf(stderr, "Couldn't open file 'data06.txt' (UTF-8 data file).\n");
    return U_FILE_ACCESS_ERROR;
  }

  info = (CharFreqInfo*)malloc(sizeof(CharFreqInfo) * charCount);
  if(!info)
  {
    fprintf(stderr, " Couldn't allocate %d bytes for freq counter\n", sizeof(CharFreqInfo)*charCount);
  }

  /* reset frequencies */
  for(p=0;p<charCount;p++)
  {
    info[p].codepoint = p;
    info[p].frequency = 0;
  }

  // **************************** START SAMPLE *******************
  conv = ucnv_open("utf-8", &status);
  assert(U_SUCCESS(status));

  uBufSize = (BUFFERSIZE/ucnv_getMinCharSize(conv));
  printf("input bytes %d / min chars %d = %d UChars\n",
         BUFFERSIZE, ucnv_getMinCharSize(conv), uBufSize);
  uBuf = (UChar*)malloc(uBufSize * sizeof(UChar));
  assert(uBuf!=NULL);

  // grab another buffer's worth
  while((!feof(f)) && 
        ((count=fread(inBuf, 1, BUFFERSIZE , f)) > 0) )
  {
    // Convert bytes to unicode
    source = inBuf;
    sourceLimit = inBuf + count;
    
    while(source < sourceLimit)
    {
      p = ucnv_getNextUChar(conv, &source, sourceLimit, &status);
      if(U_FAILURE(status))
      {
        fprintf(stderr, "%s @ %d\n", u_errorName(status), total);
        status = U_ZERO_ERROR;
        continue;
      }
      U_ASSERT(status);
      total++;

      if(u_isalpha(p))
        letters++;

      if((u_tolower(l) == 'i') && (u_tolower(p) == 'e'))
        ie++;

      if((u_tolower(l) == 'g') && (u_tolower(p) == 0x0127))
        gh++;

      if(p>charCount)
      {
        fprintf(stderr, "U+%06X: oh.., we only handle BMP characters so far.. redesign!\n", p);
        return U_UNSUPPORTED_ERROR;
      }
      info[p].frequency++;
      l = p;
    }
  }

  fclose(f);
  ucnv_close(conv);

  printf("%d letters out of %d total UChars.\n", letters, total);
  printf("%d ie digraphs, %d gh digraphs.\n", ie, gh);

  // now, we could sort it..

  //  qsort(info, charCount, sizeof(info[0]), charfreq_compare);

  for(p=0;p<charCount;p++)
  {
    if(info[p].frequency)
    {
      printf("% 5d U+%06X ", info[p].frequency, p);
      if(p <= 0xFFFF)
      {
        prettyPrintUChar((UChar)p);
      }
      printf("\n");
    }
  }
  free(info);
  // ***************************** END SAMPLE ********************

  printf("\n");

  return U_ZERO_ERROR;
}