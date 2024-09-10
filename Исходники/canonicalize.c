char *
canonicalize_filename_mode (const char *name, canonicalize_mode_t can_mode)
{
  char *rname, *dest, *extra_buf = NULL;
  char const *start;
  char const *end;
  char const *rname_limit;
  size_t extra_len = 0;
  Hash_table *ht = NULL;
  int saved_errno;
  int can_flags = can_mode & ~CAN_MODE_MASK;
  bool logical = can_flags & CAN_NOLINKS;
  size_t prefix_len;

  can_mode &= CAN_MODE_MASK;

  if (MULTIPLE_BITS_SET (can_mode))
    {
      errno = EINVAL;
      return NULL;
    }

  if (name == NULL)
    {
      errno = EINVAL;
      return NULL;
    }

  if (name[0] == '\0')
    {
      errno = ENOENT;
      return NULL;
    }

  /* This is always zero for Posix hosts, but can be 2 for MS-Windows
     and MS-DOS X:/foo/bar file names.  */
  prefix_len = FILE_SYSTEM_PREFIX_LEN (name);

  if (!IS_ABSOLUTE_FILE_NAME (name))
    {
      rname = xgetcwd ();
      if (!rname)
        return NULL;
      dest = strchr (rname, '\0');
      if (dest - rname < PATH_MAX)
        {
          char *p = xrealloc (rname, PATH_MAX);
          dest = p + (dest - rname);
          rname = p;
          rname_limit = rname + PATH_MAX;
        }
      else
        {
          rname_limit = dest;
        }
      start = name;
      prefix_len = FILE_SYSTEM_PREFIX_LEN (rname);
    }
  else
    {
      rname = xmalloc (PATH_MAX);
      rname_limit = rname + PATH_MAX;
      dest = rname;
      if (prefix_len)
        {
          memcpy (rname, name, prefix_len);
          dest += prefix_len;
        }
      *dest++ = '/';
      if (DOUBLE_SLASH_IS_DISTINCT_ROOT)
        {
          if (ISSLASH (name[1]) && !ISSLASH (name[2]) && !prefix_len)
            *dest++ = '/';
          *dest = '\0';
        }
      start = name + prefix_len;
    }

  for ( ; *start; start = end)
    {
      /* Skip sequence of multiple file name separators.  */
      while (ISSLASH (*start))
        ++start;

      /* Find end of component.  */
      for (end = start; *end && !ISSLASH (*end); ++end)
        /* Nothing.  */;

      if (end - start == 0)
        break;
      else if (end - start == 1 && start[0] == '.')
        /* nothing */;
      else if (end - start == 2 && start[0] == '.' && start[1] == '.')
        {
          /* Back up to previous component, ignore if at root already.  */
          if (dest > rname + prefix_len + 1)
            for (--dest; dest > rname && !ISSLASH (dest[-1]); --dest)
              continue;
          if (DOUBLE_SLASH_IS_DISTINCT_ROOT && dest == rname + 1
              && !prefix_len && ISSLASH (*dest) && !ISSLASH (dest[1]))
            dest++;
        }
      else
        {
          struct stat st;

          if (!ISSLASH (dest[-1]))
            *dest++ = '/';

          if (dest + (end - start) >= rname_limit)
            {
              ptrdiff_t dest_offset = dest - rname;
              size_t new_size = rname_limit - rname;

              if (end - start + 1 > PATH_MAX)
                new_size += end - start + 1;
              else
                new_size += PATH_MAX;
              rname = xrealloc (rname, new_size);
              rname_limit = rname + new_size;

              dest = rname + dest_offset;
            }

          dest = memcpy (dest, start, end - start);
          dest += end - start;
          *dest = '\0';

          if (logical && (can_mode == CAN_MISSING))
            {
              /* Avoid the stat in this case as it's inconsequential.
                 i.e. we're neither resolving symlinks or testing
                 component existence.  */
              st.st_mode = 0;
            }
          else if ((logical ? stat (rname, &st) : lstat (rname, &st)) != 0)
            {
              saved_errno = errno;
              if (can_mode == CAN_EXISTING)
                goto error;
              if (can_mode == CAN_ALL_BUT_LAST)
                {
                  if (end[strspn (end, SLASHES)] || saved_errno != ENOENT)
                    goto error;
                  continue;
                }
              st.st_mode = 0;
            }

          if (S_ISLNK (st.st_mode))
            {
              char *buf;
              size_t n, len;

              /* Detect loops.  We cannot use the cycle-check module here,
                 since it's actually possible to encounter the same symlink
                 more than once in a given traversal.  However, encountering
                 the same symlink,NAME pair twice does indicate a loop.  */
              if (seen_triple (&ht, name, &st))
                {
                  if (can_mode == CAN_MISSING)
                    continue;
                  saved_errno = ELOOP;
                  goto error;
                }

              buf = areadlink_with_size (rname, st.st_size);
              if (!buf)
                {
                  if (can_mode == CAN_MISSING && errno != ENOMEM)
                    continue;
                  saved_errno = errno;
                  goto error;
                }

              n = strlen (buf);
              len = strlen (end);

              if (!extra_len)
                {
                  extra_len =
                    ((n + len + 1) > PATH_MAX) ? (n + len + 1) : PATH_MAX;
                  extra_buf = xmalloc (extra_len);
                }
              else if ((n + len + 1) > extra_len)
                {
                  extra_len = n + len + 1;
                  extra_buf = xrealloc (extra_buf, extra_len);
                }

              /* Careful here, end may be a pointer into extra_buf... */
              memmove (&extra_buf[n], end, len + 1);
              name = end = memcpy (extra_buf, buf, n);

              if (IS_ABSOLUTE_FILE_NAME (buf))
                {
                  size_t pfxlen = FILE_SYSTEM_PREFIX_LEN (buf);

                  if (pfxlen)
                    memcpy (rname, buf, pfxlen);
                  dest = rname + pfxlen;
                  *dest++ = '/'; /* It's an absolute symlink */
                  if (DOUBLE_SLASH_IS_DISTINCT_ROOT)
                    {
                      if (ISSLASH (buf[1]) && !ISSLASH (buf[2]) && !pfxlen)
                        *dest++ = '/';
                      *dest = '\0';
                    }
                  /* Install the new prefix to be in effect hereafter.  */
                  prefix_len = pfxlen;
                }
              else
                {
                  /* Back up to previous component, ignore if at root
                     already: */
                  if (dest > rname + prefix_len + 1)
                    for (--dest; dest > rname && !ISSLASH (dest[-1]); --dest)
                      continue;
                  if (DOUBLE_SLASH_IS_DISTINCT_ROOT && dest == rname + 1
                      && ISSLASH (*dest) && !ISSLASH (dest[1]) && !prefix_len)
                    dest++;
                }

              free (buf);
            }
          else
            {
              if (!S_ISDIR (st.st_mode) && *end && (can_mode != CAN_MISSING))
                {
                  saved_errno = ENOTDIR;
                  goto error;
                }
            }
        }
    }
  if (dest > rname + prefix_len + 1 && ISSLASH (dest[-1]))
    --dest;
  if (DOUBLE_SLASH_IS_DISTINCT_ROOT && dest == rname + 1 && !prefix_len
      && ISSLASH (*dest) && !ISSLASH (dest[1]))
    dest++;
  *dest = '\0';
  if (rname_limit != dest + 1)
    rname = xrealloc (rname, dest - rname + 1);

  free (extra_buf);
  if (ht)
    hash_free (ht);
  return rname;

error:
  free (extra_buf);
  free (rname);
  if (ht)
    hash_free (ht);
  errno = saved_errno;
  return NULL;
}