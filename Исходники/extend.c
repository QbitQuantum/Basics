/* lifted from img.c Should be put somewhere common? JPNP*/
static char *
getline_alloc(FILE *fh, size_t ilen)
{
   int ch;
   size_t i = 0;
   size_t len = ilen;
   char *buf = xosmalloc(len);
   if (!buf) return NULL;

   ch = GETC(fh);
   while (ch != '\n' && ch != '\r' && ch != EOF) {
      buf[i++] = ch;
      if (i == len - 1) {
	 char *p;
	 len += len;
	 p = xosrealloc(buf, len);
	 if (!p) {
	    osfree(buf);
	    return NULL;
	 }
	 buf = p;
      }
      ch = GETC(fh);
   }
   if (ch == '\n' || ch == '\r') {
      int otherone = ch ^ ('\n' ^ '\r');
      ch = GETC(fh);
      /* if it's not the other eol character, put it back */
      if (ch != otherone) ungetc(ch, fh);
   }
   buf[i++] = '\0';
   return buf;
}