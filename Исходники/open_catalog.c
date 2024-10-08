int
__open_catalog (const char *cat_name, const char *nlspath, const char *env_var,
		__nl_catd catalog)
{
  int fd = -1;
  struct stat64 st;
  int swapping;
  size_t cnt;
  size_t max_offset;
  size_t tab_size;
  const char *lastp;
  int result = -1;

  if (strchr (cat_name, '/') != NULL || nlspath == NULL)
    fd = open_not_cancel_2 (cat_name, O_RDONLY);
  else
    {
      const char *run_nlspath = nlspath;
#define ENOUGH(n)							      \
  if (__builtin_expect (bufact + (n) >= bufmax, 0))			      \
    {									      \
      char *old_buf = buf;						      \
      bufmax += 256 + (n);						      \
      buf = (char *) alloca (bufmax);					      \
      memcpy (buf, old_buf, bufact);					      \
    }

      /* The RUN_NLSPATH variable contains a colon separated list of
	 descriptions where we expect to find catalogs.  We have to
	 recognize certain % substitutions and stop when we found the
	 first existing file.  */
      char *buf;
      size_t bufact;
      size_t bufmax;
      size_t len;

      buf = NULL;
      bufmax = 0;

      fd = -1;
      while (*run_nlspath != '\0')
	{
	  bufact = 0;

	  if (*run_nlspath == ':')
	    {
	      /* Leading colon or adjacent colons - treat same as %N.  */
	      len = strlen (cat_name);
	      ENOUGH (len);
	      memcpy (&buf[bufact], cat_name, len);
	      bufact += len;
	    }
	  else
	    while (*run_nlspath != ':' && *run_nlspath != '\0')
	      if (*run_nlspath == '%')
		{
		  const char *tmp;

		  ++run_nlspath;	/* We have seen the `%'.  */
		  switch (*run_nlspath++)
		    {
		    case 'N':
		      /* Use the catalog name.  */
		      len = strlen (cat_name);
		      ENOUGH (len);
		      memcpy (&buf[bufact], cat_name, len);
		      bufact += len;
		      break;
		    case 'L':
		      /* Use the current locale category value.  */
		      len = strlen (env_var);
		      ENOUGH (len);
		      memcpy (&buf[bufact], env_var, len);
		      bufact += len;
		      break;
		    case 'l':
		      /* Use language element of locale category value.  */
		      tmp = env_var;
		      do
			{
			  ENOUGH (1);
			  buf[bufact++] = *tmp++;
			}
		      while (*tmp != '\0' && *tmp != '_' && *tmp != '.');
		      break;
		    case 't':
		      /* Use territory element of locale category value.  */
		      tmp = env_var;
		      do
			++tmp;
		      while (*tmp != '\0' && *tmp != '_' && *tmp != '.');
		      if (*tmp == '_')
			{
			  ++tmp;
			  do
			    {
			      ENOUGH (1);
			      buf[bufact++] = *tmp++;
			    }
			  while (*tmp != '\0' && *tmp != '.');
			}
		      break;
		    case 'c':
		      /* Use code set element of locale category value.  */
		      tmp = env_var;
		      do
			++tmp;
		      while (*tmp != '\0' && *tmp != '.');
		      if (*tmp == '.')
			{
			  ++tmp;
			  do
			    {
			      ENOUGH (1);
			      buf[bufact++] = *tmp++;
			    }
			  while (*tmp != '\0');
			}
		      break;
		    case '%':
		      ENOUGH (1);
		      buf[bufact++] = '%';
		      break;
		    default:
		      /* Unknown variable: ignore this path element.  */
		      bufact = 0;
		      while (*run_nlspath != '\0' && *run_nlspath != ':')
			++run_nlspath;
		      break;
		    }
		}
	      else
		{
		  ENOUGH (1);
		  buf[bufact++] = *run_nlspath++;
		}

	  ENOUGH (1);
	  buf[bufact] = '\0';

	  if (bufact != 0)
	    {
	      fd = open_not_cancel_2 (buf, O_RDONLY);
	      if (fd >= 0)
		break;
	    }

	  ++run_nlspath;
	}
    }

  /* Avoid dealing with directories and block devices */
  if (__builtin_expect (fd, 0) < 0)
    return -1;

  if (__builtin_expect (__fxstat64 (_STAT_VER, fd, &st), 0) < 0)
    goto close_unlock_return;

  if (__builtin_expect (!S_ISREG (st.st_mode), 0)
      || (size_t) st.st_size < sizeof (struct catalog_obj))
    {
      /* `errno' is not set correctly but the file is not usable.
	 Use an reasonable error value.  */
      __set_errno (EINVAL);
      goto close_unlock_return;
    }

  catalog->file_size = st.st_size;
#ifdef _POSIX_MAPPED_FILES
# ifndef MAP_COPY
    /* Linux seems to lack read-only copy-on-write.  */
#  define MAP_COPY MAP_PRIVATE
# endif
# ifndef MAP_FILE
    /* Some systems do not have this flag; it is superfluous.  */
#  define MAP_FILE 0
# endif
  catalog->file_ptr =
    (struct catalog_obj *) __mmap (NULL, st.st_size, PROT_READ,
				   MAP_FILE|MAP_COPY, fd, 0);
  if (__builtin_expect (catalog->file_ptr != (struct catalog_obj *) MAP_FAILED,
			1))
    /* Tell the world we managed to mmap the file.  */
    catalog->status = mmapped;
  else
#endif /* _POSIX_MAPPED_FILES */
    {
      /* mmap failed perhaps because the system call is not
	 implemented.  Try to load the file.  */
      size_t todo;
      catalog->file_ptr = malloc (st.st_size);
      if (catalog->file_ptr == NULL)
	goto close_unlock_return;

      todo = st.st_size;
      /* Save read, handle partial reads.  */
      do
	{
	  size_t now = read_not_cancel (fd, (((char *) catalog->file_ptr)
					     + (st.st_size - todo)), todo);
	  if (now == 0 || now == (size_t) -1)
	    {
#ifdef EINTR
	      if (now == (size_t) -1 && errno == EINTR)
		continue;
#endif
	      free ((void *) catalog->file_ptr);
	      goto close_unlock_return;
	    }
	  todo -= now;
	}
      while (todo > 0);
      catalog->status = malloced;
    }

  /* Determine whether the file is a catalog file and if yes whether
     it is written using the correct byte order.  Else we have to swap
     the values.  */
  if (__builtin_expect (catalog->file_ptr->magic == CATGETS_MAGIC, 1))
    swapping = 0;
  else if (catalog->file_ptr->magic == SWAPU32 (CATGETS_MAGIC))
    swapping = 1;
  else
    {
    invalid_file:
      /* Invalid file.  Free the resources and mark catalog as not
	 usable.  */
#ifdef _POSIX_MAPPED_FILES
      if (catalog->status == mmapped)
	__munmap ((void *) catalog->file_ptr, catalog->file_size);
      else
#endif	/* _POSIX_MAPPED_FILES */
	free (catalog->file_ptr);
      goto close_unlock_return;
    }

#define SWAP(x) (swapping ? SWAPU32 (x) : (x))

  /* Get dimensions of the used hashing table.  */
  catalog->plane_size = SWAP (catalog->file_ptr->plane_size);
  catalog->plane_depth = SWAP (catalog->file_ptr->plane_depth);

  /* The file contains two versions of the pointer tables.  Pick the
     right one for the local byte order.  */
#if __BYTE_ORDER == __LITTLE_ENDIAN
  catalog->name_ptr = &catalog->file_ptr->name_ptr[0];
#elif __BYTE_ORDER == __BIG_ENDIAN
  catalog->name_ptr = &catalog->file_ptr->name_ptr[catalog->plane_size
						  * catalog->plane_depth
						  * 3];
#else
# error Cannot handle __BYTE_ORDER byte order
#endif

  /* The rest of the file contains all the strings.  They are
     addressed relative to the position of the first string.  */
  catalog->strings =
    (const char *) &catalog->file_ptr->name_ptr[catalog->plane_size
					       * catalog->plane_depth * 3 * 2];

  /* Determine the largest string offset mentioned in the table.  */
  max_offset = 0;
  tab_size = 3 * catalog->plane_size * catalog->plane_depth;
  for (cnt = 2; cnt < tab_size; cnt += 3)
    if (catalog->name_ptr[cnt] > max_offset)
      max_offset = catalog->name_ptr[cnt];

  /* Now we can check whether the file is large enough to contain the
     tables it says it contains.  */
  if ((size_t) st.st_size
      <= (sizeof (struct catalog_obj) + 2 * tab_size + max_offset))
    /* The last string is not contained in the file.  */
    goto invalid_file;

  lastp = catalog->strings + max_offset;
  max_offset = (st.st_size
		- sizeof (struct catalog_obj) + 2 * tab_size + max_offset);
  while (*lastp != '\0')
    {
      if (--max_offset == 0)
	goto invalid_file;
      ++lastp;
    }

  /* We succeeded.  */
  result = 0;

  /* Release the lock again.  */
 close_unlock_return:
  close_not_cancel_no_status (fd);

  return result;
}