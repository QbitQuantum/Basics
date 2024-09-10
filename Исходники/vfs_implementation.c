int retro_vfs_file_rename_impl(const char *old_path, const char *new_path)
{
   char *old_path_local    = NULL;
   char *new_path_local    = NULL;
   wchar_t *old_path_wide  = NULL;
   wchar_t *new_path_wide  = NULL;

   if (!old_path || !*old_path || !new_path || !*new_path)
      return -1;

   (void)old_path_local;
   (void)new_path_local;
   (void)old_path_wide;
   (void)new_path_wide;

#if defined(_WIN32) && !defined(_XBOX)
#if defined(_WIN32_WINNT) && _WIN32_WINNT < 0x0500
   old_path_local = utf8_to_local_string_alloc(old_path);
   new_path_local = utf8_to_local_string_alloc(new_path);

   if (old_path_local)
   {
      if (new_path_local)
      {
         int ret = rename(old_path_local, new_path_local);
         free(old_path_local);
         free(new_path_local);
         return ret==0 ? 0 : -1;
      }

      free(old_path_local);
   }

   if (new_path_local)
      free(new_path_local);
#else
   old_path_wide = utf8_to_utf16_string_alloc(old_path);
   new_path_wide = utf8_to_utf16_string_alloc(new_path);

   if (old_path_wide)
   {
      if (new_path_wide)
      {
         int ret = _wrename(old_path_wide, new_path_wide);
         free(old_path_wide);
         free(new_path_wide);
         return ret==0 ? 0 : -1;
      }

      free(old_path_wide);
   }

   if (new_path_wide)
      free(new_path_wide);
#endif
   return -1;
#else
   return rename(old_path, new_path)==0 ? 0 : -1;
#endif
}