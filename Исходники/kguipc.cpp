long kGUISystemWin::FileTime(const char *fn)
{
   struct __stat64 buf;
   int result;

   result = _stat64( fn, &buf );

   /* Check if statistics are valid: */
   if( result != 0 )
		return(0);
   else
		return((long)buf.st_mtime);
}