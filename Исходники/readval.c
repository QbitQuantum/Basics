extern void
read_date(int *py, int *pm, int *pd)
{
   int y = 0, m = 0, d = 0;
   filepos fp;

   skipblanks();

   get_pos(&fp);
   y = read_uint_internal(/*Expecting date, found “%s”*/198, &fp);
   /* Two digit year is 19xx. */
   if (y < 100) y += 1900;
   if (y < 1900 || y > 2078) {
      compile_warning(/*Invalid year (< 1900 or > 2078)*/58);
      LONGJMP(file.jbSkipLine);
      return; /* for brain-fried compilers */
   }
   if (ch == '.') {
      nextch();
      m = read_uint_internal(/*Expecting date, found “%s”*/198, &fp);
      if (m < 1 || m > 12) {
	 compile_warning(/*Invalid month*/86);
	 LONGJMP(file.jbSkipLine);
	 return; /* for brain-fried compilers */
      }
      if (ch == '.') {
	 nextch();
	 d = read_uint_internal(/*Expecting date, found “%s”*/198, &fp);
	 if (d < 1 || d > last_day(y, m)) {
	    compile_warning(/*Invalid day of the month*/87);
	    LONGJMP(file.jbSkipLine);
	    return; /* for brain-fried compilers */
	 }
      }
   }
   if (py) *py = y;
   if (pm) *pm = m;
   if (pd) *pd = d;
}