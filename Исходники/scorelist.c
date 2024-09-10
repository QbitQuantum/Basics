void scorelist_load() {
  int i, j;
  wchar_t chunk[1024];
  wchar_t delim[2] = L" ";
  wchar_t *ptr;
  wchar_t *token;

  FILE *fp = fopen(scorelist_file, "r, ccs=UTF-8");
  if (fp != NULL) {
    i = 0;
    while (fgetws(chunk, 1024, fp) != NULL) {
      chunk[wcslen(chunk) - 1] = L'\0';
      if (wcslen(chunk) > 0) {
        j = 0;
        token = wcstok(chunk, delim, &ptr);
        while (token != NULL) {
          switch (j) {
            case 0:
              wcsncpy(scorelist[i].name, token, 255);
              break;
            case 1:
              scorelist[i].points = (unsigned int)wcstoul(token, NULL, 0);
              break;
            case 2:
              scorelist[i].chars = (unsigned int)wcstoul(token, NULL, 0);
              break;
            case 3:
              scorelist[i].seconds = (unsigned int)wcstoul(token, NULL, 0);
              break;
          }
          token = wcstok(ptr, delim, &ptr);
          j++;
        }
        i++;
      }
    }
    fclose(fp);
    scorelist_length = i;
  }

  free(ptr);
  free(token);
}