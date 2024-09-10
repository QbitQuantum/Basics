FRESULT f_unlink (
   const XCHAR *path    /* Pointer to the file or directory path */
)
{
   FRESULT ret = FR_OK;
   const char* target= createFullPath(path);

   if (-1 == stat(target, &stats))
   {
      return cvtERRNO();
   }

   if (stats.st_mode & S_IFDIR)
   {
      if (_rmdir(target) == -1)
      {
         ret = FR_DENIED;
      }
   }
   else
   {
      // a concatenation of the mmc dir & the requested path
      if (_unlink(target) == -1)
      {
         ret = cvtERRNO();
      }
   }

   return ret;
}