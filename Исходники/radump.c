/*
 * Print out a null-terminated filename (or other ascii string).
 * If ep is NULL, assume no truncation check is needed.
 * Return true if truncated.
 */
int
fn_print(register const u_char *s, register const u_char *ep, char *buf)
{
   register int ret;
   register u_char c;

   ret = 1;                        /* assume truncated */
   while (ep == NULL || s < ep) {
      c = *s++;
      if (c == '\0') {
         ret = 0;
         break;
      }
      if (!isascii(c)) {
         c = toascii(c);
         sprintf(&buf[strlen(buf)], "%c", 'M');
         sprintf(&buf[strlen(buf)], "%c", '-');
      }
      if (!isprint(c)) {
         c ^= 0x40;      /* DEL to ?, others to alpha */
         sprintf(&buf[strlen(buf)], "%c", '^');
      }
      sprintf(&buf[strlen(buf)], "%c", c);
   }
   return(ret);
}