/**
* Load the character map table from a file.
*
* @param cm     Character Map to load the table into.
* @param path   The path of the file to load.
* @return       Zero if the file is loaded fine, nonzero otherwise.
*/
static int charmap_load(CHARMAP* cm, const char* path)
{
  FILE* is = NULL;
  int section = 0;
  int error_code = 0;

  /* Open */
  is = fopen(path, "rt");
  if(!is) {
    perror("path");
    return 1;
  }

  /* Load */
  while(!feof(is)) {
    wchar_t unicode[MAX_UNICODE_SEQ];
    int ulen = 0;

    char buf[256];
    char flag[256];

    int scanned = 0;

    /* Scan a single token first */
    scanned = fscanf(is, "%255s", buf);
    if(scanned < 0) break;
    if(scanned == 0) {
      fprintf(stderr, "%s: Character map syntax error\n", path);
      return 1;
    }

    /* Handle the first argument */
    if(strcmp(buf, "section") == 0) {    /* Section division */
      section++;
      continue;
    }
    else if(buf[0] == '#') {             /* Comment */
      fscanf(is, "%*[^\n]");
      continue;
    }
    else {
      char* bp = buf;
      int u;

      do {
        if(sscanf(bp, "%x", &u) == 1) {   /* Unicode */
          unicode[ulen++] = u;
        }
        else {
          fprintf(stderr, "%s: Syntax error at '%s'\n", path, buf);
          return 1;
        }

        bp = strchr(bp, ':');
        if(bp) bp++;
      } while(bp && ulen < MAX_UNICODE_SEQ-1);
      unicode[ulen] = L'\0';
    }

    /* Scan some more */
    scanned = fscanf(is, "%255s\t%255s", buf, flag);
    if(scanned < 0) break;

    /* Input count checking */
    switch(scanned) {
      case 0: case 1:
        fprintf(stderr, "%s: Character map syntax error\n", path);
        return 1;

      default:
        if(charmap_add(cm, section, buf, unicode, flag)) {
          size_t i = 0;

#ifndef __BEOS__
#if defined __GLIBC__ && __GLIBC__ == 2 && __GLIBC_MINOR__ >=2 || __GLIBC__ > 2 || __APPLE__
          fwprintf(stderr, L"Unable to add sequence '%ls', unicode ", buf);
          for(i = 0; i < wcslen(unicode); i++) fwprintf(stderr, L"%04X ", (int)unicode[i]);
          fwprintf(stderr, L"in section %d\n", section);
#endif
#endif

          error_code = 1;
        }
    }
  }

  /* Close */
  fclose(is);

  return error_code;
}