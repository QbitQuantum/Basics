/**
 * path_mkdir:
 * @dir                : directory
 *
 * Create directory on filesystem.
 *
 * Returns: true (1) if directory could be created, otherwise false (0).
 **/
bool path_mkdir(const char *dir)
{
   /* Use heap. Real chance of stack overflow if we recurse too hard. */
   const char *target = NULL;
   bool         sret  = false;
   bool norecurse     = false;
   char     *basedir  = NULL;

   if (dir && *dir)
      basedir         = strdup(dir);

   if (!basedir)
      return false;

   path_parent_dir(basedir);
   if (!*basedir || !strcmp(basedir, dir))
      goto end;

   if (path_is_directory(basedir))
   {
      target    = dir;
      norecurse = true;
   }
   else
   {
      target    = basedir;
      sret      = path_mkdir(basedir);

      if (sret)
      {
         target    = dir;
         norecurse = true;
      }
   }

   if (norecurse)
   {
#if defined(_WIN32)
#ifdef LEGACY_WIN32
      int ret = _mkdir(dir);
#else
      wchar_t *dirW = utf8_to_utf16_string_alloc(dir);
      int ret = -1;

      if (dirW)
      {
         ret = _wmkdir(dirW);
         free(dirW);
      }
#endif
#elif defined(IOS)
      int ret = mkdir(dir, 0755);
#elif defined(VITA) || defined(PSP)
      int ret = sceIoMkdir(dir, 0777);
#elif defined(__QNX__)
      int ret = mkdir(dir, 0777);
#else
      int ret = mkdir(dir, 0750);
#endif

      /* Don't treat this as an error. */
      if (path_mkdir_error(ret) && path_is_directory(dir))
         ret = 0;

      if (ret < 0)
         printf("mkdir(%s) error: %s.\n", dir, strerror(errno));
      sret = (ret == 0);
   }

end:
   if (target && !sret)
      printf("Failed to create directory: \"%s\".\n", target);
   free(basedir);
   return sret;
}