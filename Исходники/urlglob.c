char *glob_match_url(char *filename, URLGlob *glob)
{
  char *target;
  size_t allocsize;
  size_t stringlen=0;
  char numbuf[18];
  char *appendthis = NULL;
  size_t appendlen = 0;

  /* We cannot use the glob_buffer for storage here since the filename may
   * be longer than the URL we use. We allocate a good start size, then
   * we need to realloc in case of need.
   */
  allocsize=strlen(filename)+1; /* make it at least one byte to store the
                                   trailing zero */
  target = malloc(allocsize);
  if(NULL == target)
    return NULL; /* major failure */

  while(*filename) {
    if(*filename == '#' && ISDIGIT(filename[1])) {
      unsigned long i;
      char *ptr = filename;
      unsigned long num = strtoul(&filename[1], &filename, 10);
      i = num-1;

      if(num && (i <= glob->size / 2)) {
        URLPattern pat = glob->pattern[i];
        switch (pat.type) {
        case UPTSet:
          if(pat.content.Set.elements) {
            appendthis = pat.content.Set.elements[pat.content.Set.ptr_s];
            appendlen =
              strlen(pat.content.Set.elements[pat.content.Set.ptr_s]);
          }
          break;
        case UPTCharRange:
          numbuf[0]=pat.content.CharRange.ptr_c;
          numbuf[1]=0;
          appendthis=numbuf;
          appendlen=1;
          break;
        case UPTNumRange:
          snprintf(numbuf, sizeof(numbuf), "%0*d",
                   pat.content.NumRange.padlength,
                   pat.content.NumRange.ptr_n);
          appendthis = numbuf;
          appendlen = strlen(numbuf);
          break;
        default:
          printf("internal error: invalid pattern type (%d)\n",
                 (int)pat.type);
          free(target);
          return NULL;
        }
      }
      else {
        /* #[num] out of range, use the #[num] in the output */
        filename = ptr;
        appendthis=filename++;
        appendlen=1;
      }
    }
    else {
      appendthis=filename++;
      appendlen=1;
    }
    if(appendlen + stringlen >= allocsize) {
      char *newstr;
      /* we append a single byte to allow for the trailing byte to be appended
         at the end of this function outside the while() loop */
      allocsize = (appendlen + stringlen)*2;
      newstr=realloc(target, allocsize + 1);
      if(NULL ==newstr) {
        free(target);
        return NULL;
      }
      target=newstr;
    }
    memcpy(&target[stringlen], appendthis, appendlen);
    stringlen += appendlen;
  }
  target[stringlen]= '\0';
  return target;
}