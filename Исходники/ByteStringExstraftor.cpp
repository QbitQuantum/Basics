void ByteStringExtractor::extractStrings(const TCHAR *fname) {
  FILE *f = FOPEN(fname, _T("rb"));
  setvbuf(f, NULL, _IOFBF, 0x10000);

  int ch;
  m_strLength = 0;
  while((ch = fgetc(f)) != EOF) {
    if(ISALPHA(ch)) {
      appendChar(ch);
    } else {
      outputString();
    }
  }
  outputString();
  fclose(f);
}