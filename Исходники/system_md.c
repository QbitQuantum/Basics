/*  Returns a tempoary filename. The string returned must be
 *  freed by the caller
 */
char* sysTempnam() {
  char* argFileName = _tempnam(NULL, "javaws");
  int fd = -1;
  while (argFileName != NULL) {
      fd = _open(argFileName, _O_CREAT|_O_EXCL, _S_IREAD|_S_IWRITE);
      if (fd != -1 || errno != EEXIST) { 
          break;
      } 
      argFileName = _tempnam(NULL, "javaws");
   }
  if (fd != -1 ) _close(fd);
  argFileName = strdup(argFileName);
  return argFileName;
}