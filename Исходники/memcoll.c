/* Compare S1 (with length S1LEN) and S2 (with length S2LEN) according
   to the LC_COLLATE locale.  S1 and S2 do not overlap, and are not
   adjacent.  Perhaps temporarily modify the bytes after S1 and S2,
   but restore their original contents before returning.  Set errno to an
   error number if there is an error, and to zero otherwise.  */
int
memcoll (char *s1, size_t s1len, char *s2, size_t s2len)
{
  int diff;

#if HAVE_STRCOLL

  /* strcoll is slow on many platforms, so check for the common case
     where the arguments are bytewise equal.  Otherwise, walk through
     the buffers using strcoll on each substring.  */

  if (s1len == s2len && memcmp (s1, s2, s1len) == 0)
    {
      errno = 0;
      diff = 0;
    }
  else
    {
      char n1 = s1[s1len];
      char n2 = s2[s2len];

      s1[s1len++] = '\0';
      s2[s2len++] = '\0';

      while (! (errno = 0, (diff = strcoll (s1, s2)) || errno))
	{
	  /* strcoll found no difference, but perhaps it was fooled by NUL
	     characters in the data.  Work around this problem by advancing
	     past the NUL chars.  */
	  size_t size1 = strlen (s1) + 1;
	  size_t size2 = strlen (s2) + 1;
	  s1 += size1;
	  s2 += size2;
	  s1len -= size1;
	  s2len -= size2;

	  if (s1len == 0)
	    {
	      if (s2len != 0)
		diff = -1;
	      break;
	    }
	  else if (s2len == 0)
	    {
	      diff = 1;
	      break;
	    }
	}

      s1[s1len - 1] = n1;
      s2[s2len - 1] = n2;
    }

#else

  diff = memcmp (s1, s2, s1len < s2len ? s1len : s2len);
  if (! diff)
    diff = s1len < s2len ? -1 : s1len != s2len;
  errno = 0;

#endif

  return diff;
}