static enum numbered_backup_result
numbered_backup (char **buffer, size_t buffer_size, size_t filelen)
{
  enum numbered_backup_result result = BACKUP_IS_NEW;
  DIR *dirp;
  struct dirent *dp;
  char *buf = *buffer;
  size_t versionlenmax = 1;
  char *base = last_component (buf);
  size_t base_offset = base - buf;
  size_t baselen = base_len (base);

  /* Temporarily modify the buffer into its parent directory name,
     open the directory, and then restore the buffer.  */
  char tmp[sizeof "."];
  memcpy (tmp, base, sizeof ".");
  strcpy (base, ".");
  dirp = opendir (buf);
  memcpy (base, tmp, sizeof ".");
  strcpy (base + baselen, ".~1~");

  if (!dirp)
    return result;

  while ((dp = readdir (dirp)) != NULL)
    {
      char const *p;
      char *q;
      bool all_9s;
      size_t versionlen;
      size_t new_buflen;

      if (! REAL_DIR_ENTRY (dp) || _D_EXACT_NAMLEN (dp) < baselen + 4)
        continue;

      if (memcmp (buf + base_offset, dp->d_name, baselen + 2) != 0)
        continue;

      p = dp->d_name + baselen + 2;

      /* Check whether this file has a version number and if so,
         whether it is larger.  Use string operations rather than
         integer arithmetic, to avoid problems with integer overflow.  */

      if (! ('1' <= *p && *p <= '9'))
        continue;
      all_9s = (*p == '9');
      for (versionlen = 1; ISDIGIT (p[versionlen]); versionlen++)
        all_9s &= (p[versionlen] == '9');

      if (! (p[versionlen] == '~' && !p[versionlen + 1]
             && (versionlenmax < versionlen
                 || (versionlenmax == versionlen
                     && memcmp (buf + filelen + 2, p, versionlen) <= 0))))
        continue;

      /* This directory has the largest version number seen so far.
         Append this highest numbered extension to the file name,
         prepending '0' to the number if it is all 9s.  */

      versionlenmax = all_9s + versionlen;
      result = (all_9s ? BACKUP_IS_LONGER : BACKUP_IS_SAME_LENGTH);
      new_buflen = filelen + 2 + versionlenmax + 1;
      if (buffer_size <= new_buflen)
        {
          buf = xnrealloc (buf, 2, new_buflen);
          buffer_size = new_buflen * 2;
        }
      q = buf + filelen;
      *q++ = '.';
      *q++ = '~';
      *q = '0';
      q += all_9s;
      memcpy (q, p, versionlen + 2);

      /* Add 1 to the version number.  */

      q += versionlen;
      while (*--q == '9')
        *q = '0';
      ++*q;
    }

  closedir (dirp);
  *buffer = buf;
  return result;
}