void OUTPUT_FORMATTER::rewrap(POOL_MEM &string, int wrap)
{
   char *p, *q;
   int open = 0;
   int charsinline = 0;
   POOL_MEM rewrap_string(PM_MESSAGE);

   /*
    * wrap < 0: no modification
    * wrap = 0: single line
    * wrap > 0: wrap line after x characters (if api==0)
    */
   if (wrap < 0) {
      return;
   }

   /*
    * Allocate a wrap buffer that is big enough to hold the original
    * string + WRAP_EXTRA_BYTES. This means we can accommodate enough
    * line breaks and spaces to wrap the original string.
    */
   rewrap_string.check_size(string.max_size() + WRAP_EXTRA_BYTES);

   /*
    * Walk the input buffer and copy the data to the wrap buffer
    * inserting line breaks as needed.
    */
   q = rewrap_string.c_str();
   p = string.c_str();
   while (*p) {
      charsinline++;
      switch (*p) {
      case ' ':
         if (api == 0 && wrap > 0 && charsinline >= wrap && open <= 0 && *(p + 1) != '|') {
            *q++ = '\n';
            *q++ = '\t';
            charsinline = 0;
         } else {
            if (charsinline > 1) {
               *q++ = ' ';
            }
         }
         break;
      case '|':
         *q++ = '|';
         if (api == 0 && wrap > 0 && open <= 0) {
            *q++ = '\n';
            *q++ = '\t';
            charsinline = 0;
         }
         break;
      case '[':
      case '<':
         open++;
         *q++ = *p;
         break;
      case ']':
      case '>':
         open--;
         *q++ = *p;
         break;
      case '\n':
      case '\t':
         if (charsinline > 1) {
            if (*(p + 1) != '\n' && *(p + 1) != '\t' && *(p + 1) != ' ') {
               *q++ = ' ';
            }
         }
         break;
      default:
         *q++ = *p;
         break;
      }
      p++;
   }
   *q = '\0';

   string.strcpy(rewrap_string);
}